int anc(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}
int lca(int u, int v)
{
    if (anc(u, v))
        return u;
    if (anc(v, u))
        return v;
    for (int i = 21; i >= 0; i--)
    {
        if (!anc(par[v][i], u))
        {
            v = par[v][i];
        }
    }
    return par[v][0];
}
par[v][0] = p;
for (int i = 1; i < 22; i++)
{
    par[v][i] = par[par[v][i - 1]][i - 1];
}

// full code 
vector<vector<int>> adj(2e5 + 5); // graph represented as an adjacency list
// int n;                   // number of vertices
vector<int> color(2e5 + 5); // color is 0 if vertex not entered ,else 1 if entered but not exited ,else 2
vector<int> tin(2e5 + 5), tout(2e5 + 5);
int dfs_timer = 0;
vector<vi> par(2e5 + 5, vi(23));
int anc(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}
int lca(int u, int v)
{
    if (anc(u, v))
        return u;
    if (anc(v, u))
        return v;
    for (int i = 21; i >= 0; i--)
    {
        if (!anc(par[v][i], u))
        {
            v = par[v][i];
        }
    }
    return par[v][0];
}

void dfs(int v,int p)
{
    tin[v] = dfs_timer++;
    color[v] = 1;
    par[v][0] = p;
    for (int i = 1; i < 22; i++)
    {
        par[v][i] = par[par[v][i - 1]][i - 1];
    }
    for (int u : adj[v])
    {
        if (color[u] == 0)
        {
            dfs(u,v);
        }
    }
    color[v] = 2;
    tout[v] = dfs_timer++;
}