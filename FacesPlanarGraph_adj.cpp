// Encontrar las caras de un grafo planar teniendo la matriz adj
// Complejidad: O(nlogn) debido al sort, sin sort O(n)
vector<Point<int> > pts;
int from;
bool comp(int i, int j){ // Ordenar todos los vectores de adj en sentido antihorario
    Point<int> pi = pts[i]-pts[from];
    Point<int> pj = pts[j]-pts[from];
    return Angle(pi.x, pi.y) < Angle(pj.x, pj.y);
}
vector<vi> find_faces(vector<vi> adj) {
	vector<vi> used(n); // n num de vertices
	// Ordenar todos los vectores de adj en sentido antihorario
	rep(i,0,n){
		used[i].assign(adj[i].size(), 0);
        from = i;
        sort(all(adj[i]), comp);
    }
    vector<vi> faces;
    rep(i, 0, n) { 
        rep(edge_id, 0, adj[i].size()) {
            if (used[i][edge_id]) {
                continue;
            }
            vi face;
            int v = i;
            int e = edge_id;
            // Recorremos un ciclo en sentido antihorario
            // vamos del vertice v al vertice u
            while (!used[v][e]) {
                used[v][e] = true;
                face.pb(v);
                int u = adj[v][e];
                // Busca el vector de u que apunte al vertice v en O(log(grado(u)))
				from = u;
                int e1 = lower_bound(all(adj[u]), v, [&](int a, int b){
					return comp(a, b);
				}) - adj[u].begin() + 1;
                if (e1 == adj[u].size()) { // si ya no se puede girar mas en sentido antihorario que u->v
                    e1 = 0; 
                }
                v = u;
                e = e1; 
            }
            faces.pb(face); // La cara externa es la que tiene mas area
        }
    }
    return faces;
}