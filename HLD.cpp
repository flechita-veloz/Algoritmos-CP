#include <bits/stdc++.h>
using namespace std;

/*
Heavy Light Decomposition, on a tree:
- Update all nodes along the path from node x to node y.
- Find the sum, maximum, minimum (or any other operation that satisfies
  the associative property) along the path from node $x$ to node $y$.
*/

vector<int> parent, depth, heavy, head, pos;
int cur_pos;

int dfs(int v, vector<vector<int>> const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}

void decompose(int v, int h, vector<vector<int>> const& adj) {
    head[v] = h, pos[v] = cur_pos++; // cur_pos recorre subarboles con root en v
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}

void init(vector<vector<int>> const& adj) {
    int n = adj.size();
    parent = vector<int>(n); // padre del nodo v
    depth = vector<int>(n);
    heavy = vector<int>(n, -1); // almacena el hijo heavy de v
    head = vector<int>(n); // almacena el nodo cabeza (mas cercao al root) del camino heavy de nodos 
    pos = vector<int>(n); // indice en el segment tree
    cur_pos = 0;

    dfs(0, adj);
    decompose(0, 0, adj);
}

/* Example query */

int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        // consulta desde el nodo cabeza hasta un nodo en la parte baja b
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}