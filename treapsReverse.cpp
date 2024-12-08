// Plantilla TREAPS
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
using ll = long long;

// BeginCodeSnip{ModInt class}
// operations under mod
struct mint {
	const static int M = 998244353;
	ll v = 0;
	mint() {}
	mint(ll v) { this->v = (v % M + M) % M; }
	mint operator+(const mint &o) const { return v + o.v; }
	mint &operator+=(const mint &o) {
		v = (v + o.v) % M;
		return *this;
	}
	mint operator*(const mint &o) const { return v * o.v; }
	mint operator-(const mint &o) const { return v - o.v; }
	mint &operator-=(const mint &o) {
		mint t = v - o.v;
		v = t.v;
		return *this;
	}
	mint operator^(int y) const {
		mint r = 1, x = v;
		for (y <<= 1; y >>= 1; x = x * x)
			if (y & 1) r = r * x;
		return r;
	}
	mint inv() const {
		assert(v);
		return *this ^ M - 2;
	}
	friend istream &operator>>(istream &s, mint &v) {
		return s >> v.v;
		return s;
	}
	friend ostream &operator<<(ostream &s, const mint &v) { return s << v.v; }
	mint operator/(mint o) { return *this * o.inv(); }
};
// EndCodeSnip

struct Line {  // linear function wx + b
	mint w = 1, b = 0;
	mint operator()(mint x) { return w * x + b; }
    // composicion de funciones
	Line operator()(Line f) { return Line{w * f.w, w * f.b + b}; }
	operator bool() const {
		return w.v != 1 || b.v != 0;
	}  // false if this is identity function
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
	Node(mint val) : val(val), sum(val), weight(rng()), size(1) {}
	mint val, sum;  // val -> a[i], sum = sum of all a[i] in subtree
	ll weight, size;
	bool rev = false;  // whether this range is reversed
	Node *l = nullptr, *r = nullptr;
	Line f;  // lazy affine tag
};

int size(Node *treap) { return treap ? treap->size : 0; }

mint sum(Node *treap) { return treap ? treap->sum : 0; }

void push(Node *treap) {
	if (!treap) { return; }
	if (treap->rev) {  // need to reverse this range
		treap->rev = false;
		swap(treap->l, treap->r);
		if (treap->l) { treap->l->rev ^= true; }
		if (treap->r) { treap->r->rev ^= true; }
	}
	if (treap->f) {  // need to affine this range
		treap->val = treap->f(treap->val);
		treap->sum = treap->f.w * treap->sum + treap->f.b * treap->size;
		if (treap->l) { treap->l->f = treap->f(treap->l->f); }
		if (treap->r) { treap->r->f = treap->f(treap->r->f); }
		treap->f = Line{1, 0};
	}
}

void pull(Node *treap) {
	if (!treap) { return; }
	push(treap->l), push(treap->r);
	assert(!treap->f);
	treap->size = size(treap->l) + size(treap->r) + 1;
	treap->sum = sum(treap->l) + sum(treap->r) + treap->val;
}

// merges treaps l and r into treap
void merge(Node *&treap, Node *l, Node *r) {
	push(l), push(r);
	if (!l || !r) {
		treap = l ? l : r;
	} else if (l->weight > r->weight) {
		merge(l->r, l->r, r), treap = l;
	} else {
		merge(r->l, l, r->l), treap = r;
	}
	pull(treap);
}

// splits treap into l, r; l: [0, val), r: [val, )
void split(Node *treap, Node *&l, Node *&r, int val) {
	if (!treap) return void(l = r = nullptr);
	push(treap);
	if (val > size(treap->l)) {
		split(treap->r, treap->r, r, val - size(treap->l) - 1), l = treap;
	} else {
		split(treap->l, l, treap->l, val), r = treap;
	}
	pull(treap);
}

struct Treap {
	Node *root = nullptr;  // root of this treap

	void insert(int i, int x) {
		Node *l, *r;
		split(root, l, r, i);
		auto v = new Node(x);
		merge(l, l, v);
		merge(root, l, r);
	}

	void del(int i) {
		Node *l, *r;
		split(root, l, r, i);
		split(r, root, r, 1);
		merge(root, l, r);
	}

	/**
	 * updates the range [l, r)
	 * @param f the function to apply to the range
	 */
	void upd(int l, int r, function<void(Node *)> f) {
		Node *a, *b, *c;  // a: [0, l); b: [l, r); c: [r, )
		split(root, a, b, l);
		split(b, b, c, r - l);
		if (b) { f(b); }
		// merge all the splits back into the main treap
		merge(root, a, b);
		merge(root, root, c);
	}

	/**
	 * queries the range [l, r)
	 * @param f a query function (see use below)
	 */
	template <typename R> R query(int l, int r, function<R(Node *)> f) {
		Node *a, *b, *c;  // a: [0, l); b: [l, r); c: [r, )
		split(root, a, b, l);
		split(b, b, c, r - l);
		assert(b);
		R x = f(b);
		merge(root, a, b);
		merge(root, root, c);
		return x;
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	Treap treap;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		treap.insert(i, x);
	}

	for (int query = 0; query < q; query++) {
		int t;
		cin >> t;
		int i, x, l, r, w, b;
		switch (t) {
		case 0:
        // insertar en la ith posicion
			cin >> i >> x;
			treap.insert(i, x);
			break;
		case 1:
        // remover ith elemento
			cin >> i;
			treap.del(i);
			break;
		case 2:
        // revertir cadena desde [l, r - 1]
			cin >> l >> r;
			treap.upd(l, r, [](Node *x) { x->rev ^= true; });
			break;
		case 3:
        //  para cada ith [l, r - 1], hacer ai = w * ai + b
			cin >> l >> r >> w >> b;
			treap.upd(l, r, [=](Node *x) { x->f = Line{w, b}(x->f); });
			break;
		case 4:
        // suma de [l, r - 1] mod M
			cin >> l >> r;
			cout << treap.query<mint>(l, r, [](Node *x) { return x->sum; }) << endl;
			break;
		}
	}
}