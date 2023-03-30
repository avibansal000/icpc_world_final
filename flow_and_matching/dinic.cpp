struct Dinic
{
    vector<vector<ll>> adj,adjp,cap;
    vector<ll> level,used;
    ll source = 1,sink=0;
    ll INF=1e15;
    Dinic(int n, int s1, int s2)
    {
        adj.resize(n,vl(n));
        adjp.resize(n,vl(n));
        cap.resize(n,vl(n));
        level.resize(n);
        used.resize(n,0);
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
        queue<ll> q;
        q.push(source);
        level[source] = 0;
        fill(used.begin(),used.end(),0);
        used[source] = 1;
        while (!q.empty())
        {
            ll v = q.front();
            q.pop();
            if (v == sink)return true;
            for (auto u : adj[v])
            {
                if (used[u])continue;
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
    ll dfs(ll v, ll min_cap)
    {
        used[v] = 1;
        if (v == sink)return min_cap;
        for (auto u : adj[v])
        {
            if (!used[u] && cap[v][u] > 0 && level[u] == level[v] + 1)
            {
                ll p = dfs(u, min(min_cap, cap[v][u]));
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
    ll max_flow()
    {
        ll flow = 0;
        while (bfs())
        {
            while (1)
            {
                for (int i = 0; i < (int)used.size(); i++)used[i] = 0;
                ll p = dfs(source, INF);
                if (p == 0)break;
                flow += p;
            }
        }
        return flow;
    }
    // only if needed
    stack<ll> st;
    bool dfs2(ll v)
    {
        // debug(used);
        used[v] = 1;
        if (v == sink)
        {
            st.push(v);
            return true;
        }
        for (auto u : adjp[v])
        {
            if (!used[u] && cap[v][u] == 0)
            {
                bool ok=dfs2(u);
                if(ok){
                    cap[v][u]=1;
                    st.push(v);
                    return ok;
                }
            }
        }
        return false;
    }
    // In case of 1 capacity edges  and have to find edge disjoint paths run give path max-flow times.
    vector<ll> give_path(){
        fill(used.begin(),used.end(),0);
        auto e=dfs2(1);
        vl a;
        while(!st.empty()&&e){
            a.push_back(st.top());
            st.pop();
        }
        return a;
    }
};
// if wanted capacities.
for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
        cout<<i<<" "<<j<<" "<<din.cap[j][i]<<endl;
    }
}