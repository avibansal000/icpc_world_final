vector<vector<int>> adj(2e5 + 5);     // graph represented as an adjacency list
vector<vector<int>> adj_rev(2e5 + 5); // graph represented as an adjacency list in reverse order
vector<vector<int>> adj_scc(2e5 + 5);  // list of edges in scc
vector<int> roots(2e5 + 5); // gives the roots of a scc component
vector<int> color(2e5 + 5, 0); // color is 0 if vertex not entered ,else 1 if entered but not exited ,else 2
ll n, m;  // number of vertex
vi order; // topo order
void dfs(int v)
{
    color[v] = 1;
    for (int u : adj[v])
    {
        if (color[u] == 0)
        {
            dfs(u);
        }
    }
    color[v] = 2;
    order.push_back(v);
}

int curr_root;
vi topo_scc(2e5 + 5);
void dfs1(int v)
{
    color[v] = 1;
    roots[v] = curr_root;
    debug(v);
    for (auto u : adj_rev[v])
    {
        if (color[u] == 0)
        {
            dfs1(u);
        }
    }
}


void make_scc()
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (color[i] == 0)
        {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());
    debug(order);
    color = vi(n + 1, 0);
    int k1 = 1;
    for (auto e : order)
    {
        if (color[e] == 0)
        {
            curr_root = k1++;
            dfs1(e);
        }
    }
    for (i = 1; i <= n; i++)
    {
        for (auto u : adj[i])
        {
            if (roots[i] != roots[u])
            {
                adj_scc[roots[i]].push_back(roots[u]);
            }
        }
    }
}
