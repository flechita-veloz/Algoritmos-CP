#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define FORN(i,m,n) for(int i=(m); i<int(n); i++)
#define PRINTVEC(v) FORN(i,0,v.size()) cout<<v[i]<<" "; cout<<endl
#define PRINTMAT(m) FORN(j,0,m.size()) {PRINTVEC(m[j]);}
#define pb push_back
// #define endl "\n"
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

// subma
const ll N = 1 << 16;
vvll grid(16, vll(16));
ll n;
vll dp(N, -1), vis(N), score(N);
void prec(){
    int m = (1 << n);
    for(int mask = 0; mask < m; mask++){
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                if(mask & (1 << i) && (mask & (1 << j))){
                    score[mask] += grid[i][j];
                }
            }
        }
    }
}

// submask en O(3^n)
ll dfs2(ll mask){
    if(mask == 0) return 0;
    if(vis[mask]) return dp[mask];
    vis[mask] = 1;
    ll mx = -1e18;
    // Calcular todas las submascaras de una mascara en O(3 ^ n)
	for (int sub_mask = mask; sub_mask; sub_mask = (sub_mask - 1) & mask) {
		mx = max(mx, score[sub_mask] + dfs2(mask ^ sub_mask)); // truco para obtener los bits no escogidos de la submask
	}
    dp[mask] = mx;
	return mx;
}

void solve(){
    cin >> n;
    FORN(i, 0, n){
        FORN(j, 0, n){
            cin >> grid[i][j];
        }
    }
    prec();
    ll ans = dfs2((1 << n) - 1);
    cout << ans << endl; 
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
 