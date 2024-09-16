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