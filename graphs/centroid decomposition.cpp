vector<ll> adj[MAX];
ll now=0,till=log2(MAX)+1;
vector<ll> tin(MAX,0),tout(MAX,0),depth(MAX,0);
vector<vector<ll>> jump(MAX,vector<ll>(till+1,0));
vector<ll> subtree(MAX,0);
void dfs(ll cur,ll par){
    jump[cur][0]=par;
    subtree[cur]=1;
    for(ll i=1;i<=till;i++)
        jump[cur][i]=jump[jump[cur][i-1]][i-1];
    tin[cur]=++now;
    for(ll chld:adj[cur]){
        if(chld!=par){
            depth[chld]=depth[cur]+1;
            dfs(chld,cur);
            subtree[cur]+=subtree[chld]; 
        }
    }
    tout[cur]=++now;
} 
bool is_ancestor(ll a,ll b){
    if((tin[a]<=tin[b])&&(tout[a]>=tout[b]))
        return 1;
    return 0;
} 
ll lca(ll a,ll b){
    if(is_ancestor(a,b))
        return a;
    for(ll i=till;i>=0;i--){
        if(!is_ancestor(jump[a][i],b))
            a=jump[a][i];
    }
    return jump[a][0];
}  
 
ll distance(ll a,ll b){
    return depth[a]+depth[b]-2*depth[lca(a,b)]; 
}
vector<ll> new_adj[MAX];
vector<ll> parent(MAX,0);
map<pair<ll,ll>,ll> skip_edge; 
void recal(ll cur,ll par){
    subtree[cur]=1;
    for(auto it:adj[cur]){
        if(it!=par){
            if(skip_edge[{it,cur}]){
                ;
            }
            else{
                recal(it,cur);
                subtree[cur]+=subtree[it]; 
            }
        }
    }
}
ll get_centroid(ll cur,ll par,ll len){
    for(auto it:adj[cur]){
        if(it!=par){
            if(skip_edge[{it,cur}]){
                ;
            }
            else{
                if(subtree[it]>len/2){
                    return get_centroid(it,cur,len);
                }
            }
        }
    }
    return cur; 
}
ll construct(ll cur){
    recal(cur,-1);
    ll root=get_centroid(cur,-1,subtree[cur]); 
    for(auto it:adj[root]){
        if(skip_edge[{it,root}]){
            ;
        }
        else{
            skip_edge[{it,root}]=1;
            skip_edge[{root,it}]=1; 
            ll getv=construct(it);
            parent[getv]=root; 
            new_adj[root].push_back(getv); 
        }
    }
    return root;
}
void solve(){   
    ll n,q; cin>>n>>q;
    for(ll i=1;i<n;i++){
        ll u,v; cin>>u>>v;
        adj[u].push_back(v);  
        adj[v].push_back(u);
    }
    dfs(1,1); 
    ll root=construct(1); 
    vector<ll> dp(MAX,INF_ADD); 
    auto upd=[&](ll cur){
        ll u=cur;
        while(u!=0){
            dp[u]=min(dp[u],distance(u,cur));
            u=parent[u];
        }
    };   
    auto get_ans=[&](ll cur){
        ll u=cur;
        ll now=INF_ADD;
        while(u!=0){  
            now=min(now,distance(u,cur)+dp[u]);
            u=parent[u];
        }
        return now; 
    };
    upd(1); 
    while(q--){
        ll t,v; cin>>t>>v;
        if(t==1){
            upd(v); 
        }
        else{
            cout<<get_ans(v)<<nline; 
        }
    }
    return;                                  
}                             
