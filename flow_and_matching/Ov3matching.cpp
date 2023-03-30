struct Max_match{
    int n1, n2;
    vector<vector<int>> g;
    vector<pair<int,int>> ans;
    vector<int> mt;
    vector<bool> used,used1;
    Max_match(int _n1,int _n2){
        n1=_n1;
        n2=_n2;
        mt.assign(n2,-1);
        used1.assign(n2,0);
        g.assign(n1,vector<int>());
    }
    void add_edge(int u,int v){
        g[u].push_back(v);
    }
    bool try_kuhn(int v) {
        if (used[v])return false;
        used[v] = true;
        for (int to : g[v]) {
            if (mt[to] == -1 || try_kuhn(mt[to])) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }
    int matching(){
        for (int v = 0; v < n1; ++v) {
            for (int to : g[v]) {
                if (mt[to] == -1) {
                    mt[to] = v;
                    used1[v] = true;
                    break;
                }
            }
        }
        for (int v = 0; v < n1; ++v) {
            if (used1[v])
                continue;
            used.assign(n1, false);
            try_kuhn(v);
        }

        for (int i = 0; i < n2; ++i)
            if (mt[i] != -1)
                ans.emplace_back(mt[i],i);
        return ans.size();
    }
    vector<pair<int,int>> answer(){return ans;}
};