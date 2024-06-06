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

const int INF= 1e9;
vector<vpi> adj;
//Complejidad: O(mlogn)
void dijkstra(int s, vi &d, vi &p){ //nodo inicial, distancias, y antecesor
    int n= adj.size();
    d.assign(n+1,INF);
    p.assign(n+1,-1);
    d[s]= 0;
    priority_queue<pii,vpi,greater<pii>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        int v= pq.top().sec;
        int dv= pq.top().fir;
        pq.pop();
        if(dv!= d[v]) continue; //pueden haber varias distancias para un mismo vertice
        for(auto edge:adj[v]){
            int to= edge.fir;
            int len= edge.sec;
            if(d[v]+len< d[to]){
                d[to]= d[v]+len;
                p[to]= v;
                pq.push({d[to],to});
            }
        }
    }
}

vi restore_path(int s, int t, vi &p){
    vi path;
    for(int v= t; v!= s; v= p[v]){
        path.pb(v);
    }
    path.pb(s);
    reverse(all(path));
    return path;
}
void solve(){
    int n;
    cin>>n;
    adj.assign(n+1,vpi(0));
    //Resto del codigo
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setprecision(10);
    cout<<fixed;
    // int t; cin>>t;
    int t= 1;
    while(t--){
        solve();
    }
	return 0;
}
 