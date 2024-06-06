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

// Algoritmo que dice si un grafo es bipartito o no
void solve(){	
    int n;
    vector<vector<int>> adj;

    vector<int> side(n + 1, -1);
    bool is_bipartite = true;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (side[i] == -1) {
            q.push(i);
            side[i] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (side[v] == -1) {
                        side[v] = side[u] ^ 1;
                        q.push(v);
                    } else {
                        is_bipartite &= side[v] != side[u];
                    }
                }
            }
        }
    }
    cout << (is_bipartite ? "YES" : "NO") << endl;
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
 