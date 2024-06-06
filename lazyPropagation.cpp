#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const ll MAX = 1e6, INF = 1e18;
ll A[MAX], st[MAX], lazy[MAX], N, Q, T, x, y, v;
void build(ll p, ll l, ll r){
	lazy[p] = 0;
	if(l == r)
		st[p] = A[r];
	else{
		ll m = (l + r) >> 1;
		build(p << 1, l, m);
		build(p << 1 | 1, m + 1, r);
		st[p] = st[p << 1] + st[p << 1 | 1]; // cambiar operacion mx, mn
	}
}
void propagate(ll p, ll l, ll r){
	st[p] += (r - l + 1) * lazy[p]; // si es mx o mn, cambiar a st[p] += lazy[p], si es suma st[p] += (r - l + 1) * lazy[p]
	// if there are not leave nodes, propagate them then.
	if(l != r){
		lazy[p << 1] += lazy[p];
		lazy[p << 1 | 1] += lazy[p];
	}
	lazy[p] = 0;
}

// Incrementa los valores de [i, j]
void update(ll p , ll l, ll r, ll i, ll j, ll v){
	if(lazy[p] != 0)
		propagate(p , l , r);
	if(r < i or l > j)
		return;
	if(l >= i and r <= j){
		st[p] += (r - l + 1) * v; // si es mx o mn, cambiar a st[p] += v, si es suma st[p] += (r - l + 1) * v
		if(l != r){
			lazy[p << 1] += v; 
			lazy[p << 1|1] += v; 
		}
		return;
	}
	ll m = l + (r - l) / 2;
	update(p << 1, l, m, i, j, v);
	update(p << 1 | 1, m + 1, r, i, j, v);
	st[p] = st[p << 1] + st[p << 1 | 1]; // cambiar operacion mx, mn
}

// Consulta el max valor entre [i, j]
ll query(ll p, ll l , ll r, ll i, ll j){
	if(lazy[p] != 0)
		propagate(p , l, r);
	if(r < i or l > j)
		return -INF; // Cambiar a -INF para mx, INF para mn, o -1 para sumas
	if(l >= i and r <= j)
		return st[p];
	ll m = (l + r) >> 1;
	ll dx = query( p << 1, l , m , i, j);
	ll dy = query( p << 1 | 1, m + 1 , r , i, j);
	if(dx == -INF) return dy;
	if(dy == -INF) return dx;
	return dx + dy; // cambiar operacion mx, mn
}
int main(){
	cin >> N;
	for(int i = 0; i < N; i++)
		cin >> A[i];
	build(1, 0, N - 1);
	cin >> Q;
	for(int i = 0; i < Q; i ++){
		cin >> T;
		if(T == 1){ // Actualizar
			cin >> x >> y >> v;
			update(1, 0 , N - 1, x, y, v);
		}else{ // Preguntas desde el indice 0 al N - 1
			cin >> x >> y; 
			cout << query(1, 0, N - 1, x, y)<<endl;
		}
	}
	return 0;
}