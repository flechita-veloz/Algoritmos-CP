#include <iostream>
using namespace std;
// PALINDROMIC TREE O(Nlog(sigma))
const int maxn = 1e5 + 5, sigma = 26; // sigma son las letras del abc
char s[maxn]; // aqui guardamos el string 
int len[maxn], link[maxn], to[maxn][sigma];
// len son las longitudes de los nodos
// link es el enlace sufijo mas largo diferente del mismo nodo
// to es el nodo al cual se dirigen, como un arbol normal
int n = 0, last, sz;
// n es el tamanio acutal de la cadena, last el ultimo nodo al que accedimos
void init()
{
    s[n++] = -1; // cadena imaginaria
    link[0] = 1; // link suffix para palindromos pares
    len[1] = -1; // longitud de palindromo imaginario
    sz = 2; // tamanio actual del arbol, se comienza desde el nodo 3
}

// get_link encuentra un s[n - 1] X s[n - 1] sea un palindromo
// donde X es un palindromo
int get_link(int v)
{
    while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}

int add_letter(int c)
{
    s[n++] = char(c + 'a'); // agregamos una nueva letra
    last = get_link(last); // obtenemos el nuevo padre para nuestro nodo
    int r = 0; // si el nodo ya existia
    if(!to[last][c])
    {
        len [sz] = len[last] + 2; // actualizamos su len del nuevo nodo
        link[sz] = to[get_link(link[last])][c]; // obtemos su nuevo link del nodo
        to[last][c] = sz++; // nueva arista al nuevo nodo 
        r = 1; // si el nodo no existe
    }
    last = to[last][c]; // actualizamos el ultimo nodo al q accedimos 
    return r;
}

char ans[maxn];
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    init();
    char c;
    // curr devuelve el numero de palindromos distintos
    int curr = 0;
    while((c = getchar()) != '\n'){
        cout << (curr += add_letter(c - 'a')) << " ";
    } cout << endl;
    return 0;
}