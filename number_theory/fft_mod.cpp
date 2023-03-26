// works for MOD=998244353
vl roots(24);
vl invroots(24);
void root_cal()
{
    ll p = expo(3, 119); // 3 primitive_root(988244353) and 988244353= 1+2^23 (119)

    for (int i = 23; i >= 0; i--)
    {
        roots[i] = p;
        invroots[i] = mminvprime(p);
        p *= p;
        p %= MOD;
    }
}
vector<ll> reverse(vector<ll> a)
{
    int n = a.size();
    vector<ll> b(n);
    int p = __builtin_ctz(n);

    for (int i = 0; i < n; i++)
    {
        int num = 0;
        for (int j = 0; j < p; j++)
        {
            if (i & (1 << j))
            {
                num *= 2;
                num += 1;
            }
            else
            {
                num *= 2;
            }
        }
        b[i] = a[num];
    }
    return b;
}
vector<ll> fft(vector<ll> a, bool invert)
{
    int n = a.size();
    a = reverse(a);
    for (ll i = 2; i <= n; i *= 2)
    {
        for (ll j = 0; j < n; j += i)
        {
            int p = i / 2;
            ll w = 1;
            ll wn = roots[__builtin_ctz(i)];

            if (invert)
            {
                wn = invroots[__builtin_ctz(i)];
            }
            for (int k = j; k < j + p; k++)
            {
                auto t = a[k];
                ll q = w * a[k + i / 2];
                q %= MOD;
                a[k] = a[k] + q;
                a[k] = (a[k] >= MOD ? a[k] - MOD : a[k]);
                a[k + i / 2] = t - q + MOD;
                a[k + i / 2] = (a[k + i / 2] >= MOD ? a[k + i / 2] - MOD : a[k + i / 2]);
                w = w * wn;
                w %= MOD;
            }
        }
    }
    if (invert)
    {
        for (auto &e : a)
        {
            e = (e * mminvprime(n)) % MOD;
        }
    }
    return a;
}
vector<ll> multiple(vector<ll> a, vector<ll> b)
{
    int n = a.size();
    n *= 2;
    while (__builtin_popcount(n) != 1)n++;
    a.resize(n);
    b.resize(n);
    vector<ll> w1 = fft(a, false);
    vector<ll> w2 = fft(b, false);
    for (int i = 0; i < n; i++)
    {
        w1[i] *= w2[i];
        w1[i] %= MOD;
    }
    vector<ll> ans = fft(w1, true);

    return ans;
}