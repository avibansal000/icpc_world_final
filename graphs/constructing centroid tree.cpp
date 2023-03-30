vector<ll> adj[MAX];
vector<ll> skip(MAX,0);
vector<ll> subtree(MAX);
vector<ll> track;
void dfs(ll cur,ll par){
    subtree[cur]=1;
    for(auto chld:adj[cur]){
        if((chld!=par) and (!skip[chld])){
            dfs(chld,cur);
            subtree[cur]+=subtree[chld];
        }
    }
}
ll target=0;
vector<ll> ans(MAX,-1);  
ll dfs1(ll cur,ll par){
    ll found=1;
    for(auto chld:adj[cur]){
        if(chld!=par){
            if(!skip[chld]){
                if(2*subtree[chld]>target){
                    return dfs1(chld,cur);
                }
 
            }
        }
    }
    return cur;
}  
ll solve(ll cur){
    dfs(cur,-1);
    target=subtree[cur];
    debug(target);
    ll cen=dfs1(cur,-1);
    skip[cen]=1;
    for(auto chld:adj[cen]){
        if(skip[chld]){
            continue; 
        }
        ans[solve(chld)]=cen; 
    }
    debug(cen); 
    return cen;
}
void solve(){ 
    ll n; cin>>n;
    for(ll i=1;i<n;i++){
        ll u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll x=solve(1);
    for(ll i=1;i<=n;i++){
        cout<<ans[i]<<" \n"[i==n]; 
    }
    return;                             
}
