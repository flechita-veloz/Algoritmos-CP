long long compute_hash(string const& s) {
    const int p = 31; // numero primo cercano al tamanio del alfabeto
    const int m = 1e9 + 9; // numero primo, + grande = - colisiones
    long long hash_value = 0;
    long long p_pow = 1;
                    // n-1
    // hash(s) = Σ s[i]*p^i % m
                    // i=0
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

int count_unique_substrings(string const& s) {
    int n = s.size();

    const int p = 31;
    const int m = 1e9 + 9;
    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++)
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

    int cnt = 0;
    for (int l = 1; l <= n; l++) {
        unordered_set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
            // formula h[i...j] = h[0...j] - h[0...i-1] % m 
            long long cur_h = (h[i + l] + m - h[i]) % m; 
            // para comparar * p[n-i]
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}