int n;
vector<array<int, 3>> edges;

int bellmanFord(int s, vector<int>& d, vector<int>& p)
{
    d.assign(n, INF);
    p.assign(n, -1);
    d[s] = 0;
    int x;
    for (int i = 0; i < n; ++i)
    {
        x = -1;
        for (auto& e : edges)
            if (d[e[0]] < INF)
                if (d[e[1]] > d[e[0]] + e[2])
                {
                    d[e[1]] = max(-INF, d[e[0]] + e[2]);
                    p[e[1]] = e[0];
                    x = e[1];
                }
    }

    return x;
}
// Si x == -1, no hay ciclo negativo
// De lo contrario, se puede hallar el ciclo (al revés) con el siguiente código
/*
int y = x;
for (int i = 0; i < n; ++i)
    y = p[y];

vector<int> path;
path.push_back(y);
for (int cur = p[y]; cur != y; cur = p[cur])
{
    path.push_back(cur);
}
*/