//https://usaco.org/index.php?page=viewproblem2&cpid=943
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <set>
#include <array>
#include <cmath>
#include <bitset>
#include <queue>
#include <map>
#include <utility>
#include <fstream>

#define int long long
#define ll long long
#define printv(v) for(int iz=0; iz< v.size(); iz++) fout<<v[iz]<<((iz==v.size()-1)?'\n':' ')
#define printm(m) for(int jz=0; jz<m.size(); jz++) printv(m[jz])

using namespace std;

inline int signedDet(int ax, int ay, int bx, int by)
{
    int val = ax * by - ay * bx;
    if (val == 0)
        return 0;
    return val < 0 ? -1 : 1;
}

// Chequea si dos segmentos se intersectan usando el signed area del triángulo
bool checkInter(const array<int, 4>& a, const array<int, 4>& b)
{
    return (signedDet(b[2]-a[0], b[3]-a[1], a[2]-a[0], a[3]-a[1]) * signedDet(a[2]-a[0], a[3]-a[1], b[0]-a[0], b[1]-a[1])) >= 0 &&
        (signedDet(a[2]-b[0], a[3]-b[1], b[2]-b[0], b[3]-b[1]) * signedDet(b[2]-b[0], b[3]-b[1], a[0]-b[0], a[1]-b[1])) >= 0;
}

void solve()
{
    ifstream fin("cowjump.in");
    ofstream fout("cowjump.out");

    int n;
    fin >> n;

    vector<array<int, 4>> seg(n); // guarda los segmentos (x1, y1, x2, y2)
    // NOTA: agregar odenamiento por y en process si es necesario
    vector<array<int, 3>> process(2*n); // guarda los eventos (x, tipo, indice segmento)

    for (int i = 0; i < n; i++)
    {
        fin >> seg[i][0] >> seg[i][1] >> seg[i][2] >> seg[i][3];
        if (seg[i][0] > seg[i][2]) // ordena los endpoints de cada segmento según el eje x
        {
            swap(seg[i][0], seg[i][2]);
            swap(seg[i][1], seg[i][3]);
        }
        process[2*i] = {seg[i][0], 0, i}; // evento de entrada del segmento
        process[2*i+1] = {seg[i][2], 1, i}; // evento de salida del segmento
    }

    sort(process.begin(), process.end(), [](const array<int, 3> a, const array<int, 3> b) {
        if (a[0] == b[0])
        {
            if (a[1] == b[1])
                return a[2] < b[2];
            return a[1] < b[1];
        }
        return a[0] < b[0];
    }); // ordena los segmentos según el eje x (eventos de entrada primero)

    int sweepLine;

    auto lamb = [&seg, &sweepLine](int a, int b) {
        // calcular intersecciones (eje y) con la sweepline.
        double ay, by;
        if (seg[a][0] == seg[a][2])
            ay = seg[a][1];
        else
            ay = (double)seg[a][1] + (double)(sweepLine - seg[a][0]) * (double)(seg[a][3] - seg[a][1]) / (double)(seg[a][2] - seg[a][0]);
        if (seg[b][0] == seg[b][2])
            by = seg[b][1];
        else
            by = (double)seg[b][1] + (double)(sweepLine - seg[b][0]) * (double)(seg[b][3] - seg[b][1]) / (double)(seg[b][2] - seg[b][0]);

        if (ay == by)
            return a < b;
        return ay < by;
    };

    set<int, decltype(lamb)> active(lamb); // segmentos "activos" ordenados por el eje y
    // que intersecta la sweepLine actualmente

    // Se busca solo una intersección
    int fs, ss; // indices de los segmentos intersectados

    for (int i = 0; i < 2*n; i++) // Para cada evento
    {
        sweepLine = process[i][0]; // Actualiza la sweepline

        if (process[i][1]) // Si acaba un segmento
        {
            auto newIt = active.find(process[i][2]);

            // Chequear intersecciones (solo son posibles entre elementos adyacentes)
            auto other = next(newIt);
            if (other != active.end() && newIt != active.begin()) // de los elementos adyacentes una vez eliminado este segmento
            {
                auto otherOther = prev(newIt);
                if (checkInter(seg[(*other)], seg[(*otherOther)]))
                {
                    fs = (*other);
                    ss = (*otherOther);
                    break;
                }
            }
            
            active.erase(newIt);
        }
        else // Si inicia un segmento
        {
            auto newIt = active.insert(process[i][2]).first; // agregar a active

            // Chequear intersecciones (solo son posibles entre elementos adyacentes)
            auto other = next(newIt);
            if (other != active.end()) // con el segmento posterior al insertado
            {
                if (checkInter(seg[(*other)], seg[process[i][2]]))
                {
                    fs = (*other);
                    ss = process[i][2];
                    break;
                }
            }
            if (newIt != active.begin()) // con el segmento anterior al insertado
            {
                other = prev(newIt);
                if (checkInter(seg[(*other)], seg[process[i][2]]))
                {
                    fs = (*other);
                    ss = process[i][2];
                    break;
                }
            }
        }
    }

    // Revisa cuál de los dos se debe eliminar
    if (fs > ss)
        swap(fs, ss);

    int cnt = 0;
    for (int i = 0 ; i < n; i++) // Cuenta intersecciones del segmento de index más alto
    {
        if (i != ss)
        {
            cnt += checkInter(seg[ss], seg[i]);
        }
    }
    
    // Si el segmento de index más alto tiene más collisiones, se elimina ese, sino el otro
    fout << (cnt > 1 ? ss : fs) + 1 << '\n';
}

signed main()
{
    // ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

    // int t;
    // cin >> t;
    // while (t--)
        solve();
    
    return 0;
}