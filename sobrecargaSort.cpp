#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define FORN(i,m,n) for(int i=(m); i<int(n); i++)
#define PRINTVEC(v) FORN(i,0,v.size()) cout<<v[i]<<" "; cout<<endl
#define PRINTMAT(m) FORN(j,0,m.size()) {PRINTVEC(m[j]);}
#define pb push_back
#define endl "\n"
#define sec second
#define fir first
#define print(x,y) cout<<x<<": "<<y<<endl
using namespace std;

typedef long long ll; 
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<pii> vpi;

void solve(){
    ll n,m,h;
    cin>>n>>m>>h;
    vector<vll> t(n,vll(m));
    FORN(i,0,n){
        FORN(j,0,m){
            cin>>t[i][j];
        }
        sort(all(t[i]));
    }
    vector<array<ll,3>> res(n);
    FORN(i,0,n){
        ll time= 0;
        ll points= 0;
        ll penalty= 0;
        FORN(j,0,m){
            if(time+t[i][j]<= h){
                time+= t[i][j];
                penalty+= time;
                points++;
            }
            else break;
        }
        res[i]= {points,penalty,i};
    }
    // PRINTMAT(res);
    sort(all(res),[](auto a, auto b){
        if(a[0]> b[0]) return true; // ordenar por mayor puntaje
        else if(a[0]< b[0]) return false; // 
        else{
            if(a[1]< b[1]) return true; // ordenar por menor penalidad
            else if(a[1]> b[1]) return false;
            else return a[2]< b[2]; // ordenar por menor indice
        }
    });
    FORN(i,0,n){
        if(res[i][2]== 0){
            cout<<i+1<<endl;
            return;
        }
    }
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
 