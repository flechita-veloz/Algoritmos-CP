// Complejidad O(M log N), M -> aristas, N -> nodos
vector<int> parent, rango;

void make_set(int v) {
    parent[v] = v;
    rango[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rango[a] < rango[b])
            swap(a, b);
        parent[b] = a;
        if (rango[a] == rango[b])
            rango[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<Edge> result;
parent.resize(n);
rango.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) { // DSU
        cost += e.weight;
        result.push_back(e);
        union_sets(e.u, e.v);
    }
}