// The graph represented as an adjacency list (0-indexed)
vector<vector<int>> adj; // inciar con n
vector<int> inicio;
vector<int> fin;
int timer = 0;

// para hacer las queries: query(inicio[i], fin[i] - 1)
// para hacer updates: update(inicio[i], valor)
// para construir: tree[i] = inicio[i]
void euler_tour(int at, int prev) { 
	inicio[at] = timer++;
	for (int n : adj[at]) {
		if (n != prev) { euler_tour(n, at); }
	}
	fin[at] = timer;
}
