// Link: https://atcoder.jp/contests/dp/tasks/dp_r
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

const ll mod = 1e9 + 7;
ll n;
struct Matrix{
    vvll M;
    Matrix(){
        M.assign(n, vll(n));
    }
    Matrix operator *(const Matrix& B){
        Matrix aux = Matrix();
        FORN(i, 0, n){
            FORN(j, 0, n){
                FORN(k, 0, n){
                    aux.M[i][j] =   (aux.M[i][j] + 
                                    ((M[i][k] * B.M[k][j]) % mod)
                                    ) % mod;
                }
            }
        }
        return aux;
    }
};
void solve(){
    ll k;
    cin >> n >> k;
    vvll grid(n, vll(n));
    FORN(i, 0, n) FORN(j, 0, n) cin >> grid[i][j];
    Matrix A = Matrix(), ans = Matrix();
    FORN(i, 0, n) ans.M[i][i] = 1;
    A.M = grid;
    // ans[i][j] = es el número de formas de llegar al nodo i
    // tal que la ruta tiene exactamente k aristas
    // Por cada multiplicación se agrega 1 arista más 
    // A[i][k] * A[k][j] para k = {0, ..., n-1}
    // significa 1 conexion entre i - > k -> j (van 2 aristas)
    // y si hacemos eso de nuevo 
    // new_A[i][k] * A[k][j] significa 1 conexion entre
    // i -> node -> k y k -> i, es deci r (van 3 aristas)
    // y así sucesivamente (4, 5, 6, ... k aristas)
    while(k > 0){
        if(k % 2) ans = ans * A;
        A = A * A;
        k /= 2;
    }
    ll sum = 0;
    FORN(i, 0, n){
        FORN(j, 0, n){
            sum = (sum + ans.M[i][j]) % mod;
        }
    }
    cout << sum << endl;
    /*vll dp(n, 1);
    for(ll i = 0; i < k; i++){
        vll new_dp(n);
        FORN(a, 0, n){
            FORN(b, 0, n){
                if(grid[a][b]){
                    new_dp[b] = (new_dp[b] + dp[a]) % mod;
                }
            }
        }
        dp = new_dp;
    }
    ll ans = 0;
    FORN(i, 0, n){
        ans = (ans + dp[i]) % mod;
    }*/
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
 