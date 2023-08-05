vector<ll> siz(MAX,0);
ll dfs(int v,int par){
    ll sz=1;
    for(auto e: adj[v]){
        if(e==par)continue;
        sz+=dfs(e,v);
    }
    siz[v]=sz;
    return sz;
}
ll k1,k2;
ll ans=0;
void dfs_exact(int v, FenwickTree<ll>& ans,int dis, int par){
    ans.add(dis,1);
    for(auto e: adj[v]){
        if(color[e]==0 and e!=par){
            dfs_exact(e,ans,dis+1,v);
        }
    }
}
void dfs_cen(int v){
    for(auto e: adj[v]){
        if(color[e]==0){
            if(2*siz[e]>siz[v]){
                ll t=siz[v];
                siz[v]=siz[v]-siz[e];
                siz[e]=t;
                dfs_cen(e);
                t=siz[e];
                siz[e]-=siz[v];
                siz[v]=t;
                return;
            }
        }
    }
    FenwickTree<ll> res(siz[v]+1);
    res.add(0,1);
    if(siz[v]==0)assert(0);
    color[v]=1;
    for(auto e: adj[v]){
        if(color[e]==1)continue;
        FenwickTree<ll> q(siz[e]+1);
        dfs_exact(e,q,0,v);
        dfs_cen(e);
        for(int i=0;i<=(siz[e]);i++){
            ll num=q.sum(i,i);
            ll dis=i+1;
            ans+=res.sum(k1-dis,k2-dis)*1ll*num;
        }
        for(int i=0;i<=(siz[e]);i++){
            ll num=q.sum(i,i);
            ll dis=i+1;
            res.add(dis,num);
        }
    }   
    return ;
}

typedef long double ld;
void solve(){
    ll n;cin>>n>>k1>>k2;
    for(ll i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1);
    dfs_cen(1);
    cout<<ans<<endl;
}