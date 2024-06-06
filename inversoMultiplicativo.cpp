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

const ll mod = 998244353;
vll dp(61);
vll fact(61);
ll powMod(ll a, ll b){
    a %= mod;
    if(a == 0) return 0;
    ll product = 1;
    while(b > 0){
        if (b % 2){  
            product *= a;
            product %= mod;
            --b;
        }
        a *= a;
        a %= mod;
        b /= 2;    
    }
    return product;
}

ll inv(ll a){
    return powMod(a, mod - 2);
}

ll nCk(ll n, ll k){
    return ( ((fact[n] * inv(fact[k])) % mod) * 
             (inv(fact[n - k])) ) % mod;
}

void prec(){    
    fact[0] = 1;
    for(int i = 1; i <= 60; i++){
        fact[i] = (fact[i - 1] * i) % mod;
    }
    dp[2] = 1, dp[4] = 3;
    for(int i = 6; i <= 60; i+= 2){
        dp[i] = (nCk(i - 1, i / 2 - 1) + nCk(i - 4, i / 2 - 3)) % mod;
        dp[i] = (dp[i] + dp[i - 4]) % mod;
    }
    /*for(int i = 2; i<= 8; i += 2) cout << dp[i] << " ";
    cout << endl;*/
}
void solve(){
    ll n;
    cin >> n;
    ll tot = nCk(n, n / 2);
    ll x = dp[n];
    ll y = (((tot - dp[n] - 1) % mod) + mod) % mod;
    ll z = 1;
    cout << x << " " << y << " " << z << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    setprecision(9);
    cout<<fixed;
    prec();
    int t; cin>>t;
    // int t= 1;
    while(t--){
        solve();
        // cout<< solve() << endl;
    }
	return 0;
}
 