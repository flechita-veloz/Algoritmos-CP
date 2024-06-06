#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define FORN(i,m,n) for(int i=(m); i<int(n); i++)
#define PRINTVEC(v) FORN(i,0,v.size()) cout<<v[i]<<" "; cout<<endl
#define PRINTMAT(m) FORN(j,0,m.size()) {PRINTVEC(m[j]);}
#define pb push_back
#define endl "\n"
#define sec second
#define fir first
#define print1(x) cout<<x<<endl;
#define print2(x,y) cout<<x<<": "<<y<<endl
using namespace std;

typedef long long ll; 
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<pii> vpi;
typedef vector<vll> vvll;

// Calcula la ruta mas larga para todos los nodos
// tal que comienza desde el nodo x
const int N = 1e6;
vvi tree(N);
vi down(N), up(N); 
void dfs1(int u, int p){
    for(auto v : tree[u]){
        if(v == p) continue;
        dfs1(v, u);
        down[u] = max(down[u], down[v] + 1);
    }
}

void dfs2(int u, int p){
    int mx1 = -1, mx2 = -1;
    for(auto v : tree[u]){
        if(v == p) continue;
        if(down[v] > mx1) mx2 = mx1, mx1 = down[v]; 
        else if(down[v] > mx2) mx2 = down[v]; 
    }
    for(auto v : tree[u]){
        if(v == p) continue;
        int use = mx1;
        if(mx1 == down[v]) use = mx2;
        up[v] = max(up[u] + 1, use + 2); // cuando no hay mx2
        dfs2(v, u);
    }
}

void solve(){
    int n; cin >> n;
    FORN(i, 0, n - 1){
        int u, v;
        cin >> u >> v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    FORN(i, 1, n + 1){
        cout << max(down[i], up[i]) << " ";
    } cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    setprecision(9);
    cout<<fixed;
    // int t; cin>>t;
    int t= 1;
    while(t--){
        solve();
        // cout<< solve() << endl;
    }
	return 0;
}
 