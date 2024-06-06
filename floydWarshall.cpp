void floydWarshall(vector<vector<int>>& d, vector<vector<int>>& p)
{
    // Se debe inicializar la matriz d con las aristas
    // Si no hay arista entre i y j, entonces d[i][j] = INF
    // y con d[i][i] = 0 para todo i=0..n-1
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (d[i][k] < INF && d[k][j] < INF)
                {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    p[i][j] = k;
                }
            }
        }
    }
}
// Si hay un ciclo negativo entonces d[i][i] será menor que 0.