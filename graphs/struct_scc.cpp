struct scc{
    ll n;
    vector<vector<ll>> adj;
    vector<vector<ll>> rev_adj;
    vector<ll> order,visited;
    vector<ll> component; 
    vector<vector<ll>> answer; 
    scc(ll n){
        this->n=n;
        adj.resize(n);
        rev_adj.resize(n);
        visited.resize(n,0);
    }
    void add_edge(ll l,ll r){
        adj[l].push_back(r);
        rev_adj[r].push_back(l); 
    }
    void dfs1(ll cur){
        visited[cur]=1;
        for(auto chld:adj[cur]){
            if(!visited[chld]){
                dfs1(chld);
            }
        }
        order.push_back(cur);
    }
    void dfs2(ll cur){
        visited[cur]=1;
        for(auto chld:rev_adj[cur]){
            if(!visited[chld]){
                dfs2(chld);
            }
        }
        component.push_back(cur);
    }
    void perform_op(){
        for(ll i=0;i<n;i++){
            if(!visited[i]){
                dfs1(i);
            }
        }
        for(ll i=0;i<n;i++){
            visited[i]=0;
        }
        reverse(all(order));
        for(auto it:order){
            if(!visited[it]){
                dfs2(it);
                answer.push_back(component); 
                component.clear(); 
            }
        }
    }
    vector<vector<ll>> getv(){
        return answer; 
    }
};
