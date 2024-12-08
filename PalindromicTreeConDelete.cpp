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

// Palindromic Tree con delete
const int maxn = 1e5 + 5, sigma = 26; // sigma son las letras del abc
char s[maxn]; // aqui guardamos el string 
int len[maxn], link[maxn], to[maxn][sigma];
int n = 0, last, sz;
vi ocurr(maxn), depth(maxn); // ocurrencias para saber cuando eliminar un nodo, depth de suffix link 
vpi st; // stacks para los nodos q accedi anteriormente
void init()
{
    s[n++] = -1; // cadena imaginaria
    link[0] = 1; // link suffix para palindromos pares
    len[1] = -1; // longitud de palindromo imaginario
    sz = 2; // tamanio actual del arbol, se comienza desde el nodo 3
}

int get_link(int v)
{
    while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}

ll curr = 0;
void add_letter(int c)
{
    s[n++] = char(c + 'a'); // agregamos una nueva letra
    last = get_link(last); // obtenemos el nuevo padre para nuestro nodo
    pii edge = {last, 0};
    if(!to[last][c])
    {
        len [sz] = len[last] + 2; // actualizamos su len del nuevo nodo
        link[sz] = to[get_link(link[last])][c]; // obtemos su nuevo link del nodo
        to[last][c] = sz++; // nueva arista al nuevo nodo 
    }
    last = to[last][c]; // actualizamos el ultimo nodo al q accedimos 
    edge.sec = last;
    st.pb(edge);
    depth[last] = depth[link[last]] + 1;
    curr += depth[last];
}

void del_letter(){
    int tam = st.size();
    int u = st[tam - 1].fir, v = st[tam - 1].sec; // padre -> last
    if(ocurr[v] == 1){
        to[u][s[n - 1] - 'a'] = 0; 
        sz--;
    }
    curr -= depth[last];
    ocurr[v]--;
    st.pop_back();
    n--;
    last = st[st.size() - 1].sec;
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    init();
    int tam; cin >> tam;
    string str;
    cin >> str;
    FORN(i, 0, tam){
        if(str[i] == '-') del_letter();
        else add_letter(str[i] - 'a');
        cout << curr << " ";
    } cout << endl;
    return 0;
}