struct query
{
    ll v, u;
    bool united;
};
struct dsu_save
{
    int v, rnkv, u, rnku;
    dsu_save() {}
    dsu_save(int _v, ll _rnkv, int _u, ll _rnku): v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};
struct dsu_with_rollbacks
{
    vector<ll> p, rnk,size;
    stack<dsu_save> op;
    int comps;
    dsu_with_rollbacks() {}
    dsu_with_rollbacks(int n)
    {
        p.resize(n);
        rnk.resize(n);
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
            rnk[i] = 1;
        }
        comps = n;
    }
    int find_set(int v)
    {
        return (v == p[v]) ? v : find_set(p[v]);
    }
    bool unite(int v, int u)
    {
        v = find_set(v);
        u = find_set(u);
        if (v == u)return false;
        comps--;
        if (rnk[v] > rnk[u])swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        rnk[u] += rnk[v];
        return true;
    }
    void rollback()
    {
        if (op.empty())return;
        dsu_save x = op.top();
        op.pop();
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};
struct QueryTree
{
    vector<vector<query>> t;
    dsu_with_rollbacks dsu;
    int T;
    ll ans=0;
    QueryTree() {}
    QueryTree(int _T, int n) : T(_T)
    {
        dsu = dsu_with_rollbacks(n);
        t.resize(4 * T + 4);
    }
    void add_to_tree(int v, int l, int r, int ul, int ur, query &q)
    {
        if (ul > ur)return;
        if (l == ul && r == ur)
        {
            t[v].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
        add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
    }
    void add_query(query q, int l, int r)
    {
        add_to_tree(1, 0, T - 1, l, r, q);
    }
    void dfs(int v, int l, int r)
    {
        for (query &q : t[v])if(q.united)dsu.unite(q.v, q.u);
        if (l == r)
        {
            for(auto e: t[v])
            {
                if (e.united == 0)
                {
                    ans += dsu.rnk[dsu.find_set(e.u)] * dsu.rnk[dsu.find_set(e.v)];  // we can change it accordingly 
                }
            }
        }
        else
        {
            int mid = (l + r) / 2;
            dfs(2 * v, l, mid);
            dfs(2 * v + 1, mid + 1, r);
        }
        for (query q : t[v])
        {
            if (q.united)dsu.rollback();
        }
    }
    ll solve()
    {
        dfs(1, 0, T - 1);
        return ans;
    }
};