vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    // p[] almacen la longitud de los palindromos centradas en la ith pos
    // si el tam del palindromo es x, p[] es (x + 1) / 2
    vector<int> p(n + 2);
    int l = 1, r = 1; // (l y r) son los limites "exteriores" del palindromo actual mas a la derecha
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)])); // caso i >= r e i < r
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) { 
            l = i - p[i], r = i + p[i]; // actualizamos el rightmost palindrome
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
// Manacher par e impar
// si es par significa q el palindromo comienza desde s[i -2], s[i- 1], s[i], s[i + 1]
vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#"); 
    // d[2 * i - 1] = 2dpar[i] + 1
    // d[2 * i + 1 - 1] = 2dimpar[i]
    return vi(res.begin() + 1, res.end() - 1); // retorna d
}