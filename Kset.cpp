#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) x.begin(), x.end()
#define FORN(i,m,n) for(int i=(m); i<int(n); i++)
#define PRINTVEC(v) FORN(i,0,v.size()) cout<<v[i]<<" "; cout<<endl
#define PRINTMAT(m) FORN(j,0,m.size()) {PRINTVEC(m[j]);}
#define pb push_back
#define endl "\n"
#define sec second
#define fir first

using namespace std;
using namespace __gnu_pbds;

typedef long long ll; 
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<pii> vpi;
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

// El primer parametro int es el tipo de dato del set
// El segundo parametro es null_type para set, u otro tipo para map. Por ejemplo tree<string,int,...> es un map<string,int>
// El tercer parámetro es la función de comparación, por defecto usar less<T>
// Para multiset se usa greater_equal o un pair<int, int>
// Y para eliminar elementos ks.erase(ks.find_by_order(ks.order_of_key(elmto)));
// Para buscar y borrar elementos en multiset, usar lower_bound
// El cuarto y el quinto se ponen como están, rb_tree-> arbol red black -> split mas eficiente
// soportan las operaciones: 
// *x.find_by_order(k); k-th mayor elemento (cuenta el cero)
// x.order_of_key(key); numero de elementos estrictamente mas pequeños que key
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Kset;

void solve(){
  int n;
  cin>>n;
  vpi arr;
  for(auto &p:arr) cin>>p.second>>p.first;
  sort(arr.begin(),arr.end());
  ll ans= 0;
  Kset ks;
  for(auto p:arr){
    ans+= ks.size() - ks.order_of_key(p.second);
    ks.insert(p.second);
  }
  cout<<ans<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
  setprecision(10);
  cout<<fixed;
  int t; cin>>t;
  // int t= 1;
  while(t--){
      solve();
  }
	return 0;
}
 