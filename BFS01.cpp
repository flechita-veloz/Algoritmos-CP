// Algoritmo bfs 0/1
vector<int> d(n, INF);
d[s] = 0; 
deque<int> q;
q.push_front(s);
while (!q.empty()) {
    int u = q.front(); 
    q.pop_front(); // Poner arriba si o si
    for (auto edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (d[u] + w < d[v]) {
            d[v] = d[u] + w;
            if (w == 1)
                q.push_back(v);
            else
                q.push_front(v);
        }
    }
}