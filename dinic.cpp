template <typename T>
class Dinic
{
    public:
    vector<vector<T>> adj;
    vector<vector<T>> adjp;
    vector<vector<T>> cap;
    vector<T> level;
    vector<T> used;
    T source = 1;
    T sink = 0;
    Dinic(int n, int s1, int s2)
    {
        adj = vector<vector<T>>(n + 1, vector<T>(n + 1));
        adjp = vector<vector<T>>(n + 1, vector<T>(n + 1));
        cap = vector<vector<T>>(n + 1, vector<T>(n + 1));
        level = vector<T>(n + 1);
        used = vector<T>(n + 1, 0);
        source = s1;
        sink = s2;
    }
    void addEdge(int a,int b,int c){
        adj[a].push_back(b);
        adj[b].push_back(a);
        cap[a][b]=c;
        adjp[a].push_back(b);

    }
    bool bfs()
    {
        queue<T> q;
        q.push(source);
        level[source] = 0;
        for (int i = 0; i < (int)used.size(); i++)
        {
            used[i] = 0;
        }
        used[source] = 1;
        while (!q.empty())
        {
            T v = q.front();
            q.pop();
            if (v == sink)
            {
                return true;
            }
            for (auto u : adj[v])
            {
                if (used[u])
                    continue;
                if (cap[v][u] > 0)
                {
                    used[u] = 1;
                    level[u] = level[v] + 1;
                    q.push(u);
                }
            }
        }
        return false;
    }
    T dfs(T v, T min_cap)
    {
        used[v] = 1;
        if (v == sink)
        {
            return min_cap;
        }
        for (auto u : adj[v])
        {
            if (!used[u] && cap[v][u] > 0 && level[u] == level[v] + 1)
            {
                T p = dfs(u, min(min_cap, cap[v][u]));
                if (p != 0)
                {
                    cap[v][u] -= p;
                    cap[u][v] += p;
                    return p;
                }
            }
        }
        return 0;
    }
    //for getting paths if needed
    // stack<T> st;
    // bool dfs2(T v)
    // {
    //     // debug(used);
    //     used[v] = 1;
    //     if (v == sink)
    //     {
    //         st.push(v);
    //         return true;
    //     }
    //     for (auto u : adjp[v])
    //     {
    //         if (!used[u] && cap[v][u] == 0)
    //         {
    //             bool ok=dfs2(u);
    //             if(ok){
    //                 cap[v][u]=1;
    //                 st.push(v);
    //                 return ok;
    //             }
    //         }
    //     }
    //     return false;
    // }

    T max_flow()
    {
        T flow = 0;
        while (bfs())
        {

            while (1)
            {
                for (int i = 0; i < (int)used.size(); i++)
                {
                    used[i] = 0;
                }
                T p = dfs(source, INF);
                if (p == 0)
                    break;
                flow += p;
            }
        }
        return flow;
    }
};
