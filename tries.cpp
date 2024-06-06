// Tries
// N es cnt de palabras
const int N = 1e6 + 10;
int cnt = 1; // numero de nodos actual
vector<vector<int>> trie(N, vector<int>(26, -1));
void insert(string s){
    int u = 0;
    for(auto c : s){
        if(trie[u][c - 'a']== -1){
            trie[u][c - 'a'] = cnt++; //nueva ramificacion
        }
        u = trie[u][c - 'a']; // u ahora es hijo 
    } 
}
