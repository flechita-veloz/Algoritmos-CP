const int N=400005, mod1=1e9+9, mod2=1e9+7;
struct Hasher
{
    int x, y;

    Hasher(int X = 0, int Y = 0)
    {
        x = X, y = Y;
    }

    long long get_val()
    {
        return ((1LL*x)<<31LL)|(1LL*y);
    }

    bool operator==(const Hasher& A) const
    {
        return x == A.x && y == A.y;
    }

    Hasher operator+(const Hasher& A) const
    {
        return Hasher((x + A.x) % mod1, (y + A.y) % mod2);
    }

    Hasher operator-(const Hasher& A) const
    {
        return Hasher((x - A.x + mod1) % mod1, (y - A.y + mod2) % mod2);
    }

    Hasher operator*(const Hasher& A) const
    {
        return Hasher(1LL * x * A.x % mod1, 1LL * y * A.y % mod2);
    }
} seed(31, 131); 