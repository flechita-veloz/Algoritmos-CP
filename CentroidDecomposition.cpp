/*  O((N + Queries)log n)
    Centroid Decomposition: 
	Divide el árbol en "centroides" con subárboles disjuntos.
	En un arbol de nodos rojo y azul.
	- Cambiar el color de nodo en log(n)
	- Consulta el nodo rosa mas cercano a un nodo en log(n)
*/

const int N = 1e5 + 10;
vector<vector<int>> adj(N);
vector<bool> is_removed(N);
vector<int> subtree_size(N);

/** DFS to calculate the size of the subtree rooted at `node` */
int get_subtree_size(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		subtree_size[node] += get_subtree_size(child, node);
	}
	return subtree_size[node];
}

/**
 * Returns a centroid (a tree may have two centroids) of the subtree
 * containing node `node` after node removals
 * @param node current node
 * @param tree_size size of current subtree after node removals
 * @param parent parent of u
 * @return first centroid found
 */
int get_centroid(int node, int tree_size, int parent = -1) {
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		if (subtree_size[child] * 2 > tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}

/** Build up the centroid decomposition recursively */
void build_centroid_decomp(int node = 0) {
	int centroid = get_centroid(node, get_subtree_size(node));

	// do something

	is_removed[centroid] = true;

	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}