#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define FORN(i,m,n) for(int i=(m); i<int(n); i++)
#define PRINTVEC(v) FORN(i,0,v.size()) cout<<v[i]<<" "; cout<<endl
#define PRINTMAT(m) FORN(j,0,m.size()) {PRINTVEC(m[j]);}
#define pb push_back
#define endl "\n"
#define sec second
#define fir first
using namespace std;
typedef long long ll; 
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<pii> vpi;

template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

const int N= 1e5 + 5;
int n, q;
vi tree(N*2);

void build(){
  for(int i = n - 1; i>= 0; i--) tree[i] = tree[i*2]+tree[i*2+1];
}

void update(int p, int value){
  for(tree[p += n] = value; p > 1; p/= 2) tree[p/2] = tree[p]+tree[p^1]; // setea, no aumenta
}

int query(int l, int r){
  int res = 0; //max->res=-1
  for (l += n, r += n; l <= r; l/= 2, r/= 2) {
    if (l%2) res = res+tree[l++];
    if (r%2==0) res = res+tree[r--];
  }
  return res;
}

void solve(){
  cin>>n>>q;
  FORN(i,0,n) cin>>tree[n+i];
  build();
  FORN(i,0,q){
    int a, b;
    cin>>a>>b;
    a--,b--;
    cout<<query(a,b)<<endl; //query: [a,b]
  }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setprecision(10);
    cout<<fixed;
    solve();
    return 0;
}
 