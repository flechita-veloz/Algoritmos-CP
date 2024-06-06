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
 
const int N = 1e6;
vvi tree(N);
pii bfs(int root){
    queue<array<int, 3>> q;
    q.push({root, root, 0});
    pii mx = {root, 0};
    while(!q.empty()){
        auto arr = q.front();
        int u = arr[0];
        int p = arr[1];
        int l = arr[2];
        if(l > mx.sec) mx.fir = u, mx.sec = l;
        for(auto v : tree[u]){
            if(v != p){
                array<int, 3> arr2 = {v, u, l + 1};
                q.push(arr2);
            }
        }
        q.pop();
    }
    return mx;
}
void solve(){	
    int n;
    cin >> n;
    FORN(i, 0, n - 1){
        int u, v;
        cin >> u >> v;
        tree[u].pb(v);
        tree[v].pb(u);
    }
    pii p1 = bfs(1);
    // print2("farth", p1.fir);
    pii p2 = bfs(p1.fir);
    cout << p2.sec << endl;
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
