// Manacher 2
vector<vector<int>> p(2, vector<int> (n)); // palindromos par e impar

for (int z=0; z<2; z++) // para palindromos par e impar
{
    int l = 0; // limites (del palíndormo "de afuera")
    int r = 0;
    for (int i=0; i<n; i++)
    {
        if (i<r) // si está dentro del palíndromo "de afuera", sino 0
            p[z][i] = min(r-i, p[z][l+r-i+!z]); // mínimo entre palíndromos de su reflejo y los límites
        while (i-p[z][i]-!z >= 0 && i+p[z][i] < n && s[i-p[z][i]-!z] == s[i+p[z][i]])
            p[z][i]++; // algoritmo "intuitivo"
        if (i+p[z][i] > r) // si se excedio el límite derecho
        {
            l = i-p[z][i]-!z; // actualizar los límites del palíndromo "de afuera"
            r = i+p[z][i];
        }
    }
}