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

// Floyd’s algorithm
// Complejidad temporal O(n), espacial O(1)
void solve(){	
    // Ejemplo
    vi succ(7);
    for(int i = 0; i < 6; i++){
        succ[i] = i + 1;
    }
    succ[6] = 2; 
    
    // Primero, ambos pteros a y b empiezan en el nodo x
    int x = 0;
    int a = succ[x];
    int b = succ[succ[x]];
    while (a != b) {
        a = succ[a];
        b = succ[succ[b]];
    }
    // Segundo, calculamos el inicio dle ciclo en first
    a = x;
    while (a != b) {
        a = succ[a];
        b = succ[b];
    }
    int first = a;
    // Tercero, calculamos la longitud del ciclo
    b = succ[a];
    int length = 1;
    while (a != b) {
        b = succ[b];
        length++;
    }
    cout << length << endl;
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
 