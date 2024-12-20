// The graph represented as an adjacency list (0-indexed)
// Para actualizar nodos y encontrar el valor del suarbol de un nodo

// Con el segment tree [l, r] 
// para hacer las queries: 
// 		subarboles: query(inicio[i], fin[i] - 1)
//		root a node: query(0, inicio[i])
// para hacer updates:
// 		update(inicio[i], valor)
//		update(fin[i], -valor)
// para construir:
// for(int i = 0; i < n; i++){
// 	 tree[inicio[i] + n] = a[i]; // subtree 
//   update(inicio[i], a[i]); // path 
//   if(fin[i] < n) update(fin[i], -a[i]); // path
// }

vector<vector<int>> adj; // inciar con n
vector<int> inicio;
vector<int> fin;
int timer = 0;

void euler_tour(int u, int parent) { 
	inicio[u] = timer++;
	for (int v : adj[u]) {
		if (v != parent) { euler_tour(v, u); }
	}
	fin[u] = timer;
}
