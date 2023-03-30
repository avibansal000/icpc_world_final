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
vector<ll> index_val(MAX,0),chain_no(MAX,-1);
ll pos=0;
vector<vector<ll>> track; 
vector<ll> parent(MAX,0);
void dfs_(ll cur,ll par){
    if(chain_no[cur]!=-1){
        track[chain_no[cur]].push_back(cur);
    }
    parent[cur]=par; 
    ll nax=0;
    for(auto it:adj[cur]){
        if(it!=par){
            nax=max(nax,subtree[it]); 
        }
    }
    for(auto it:adj[cur]){
        if(it!=par){
            if(nax==subtree[it]){
                if(chain_no[cur]!=-1){
                    chain_no[it]=chain_no[cur];
                }
                else{
                    vector<ll> emp;
                    track.push_back(emp); 
                    chain_no[it]=pos++;
                }
                nax=INF_ADD;
            }
            dfs_(it,cur); 
        }
    }
}
class ST{
public:
    vector<ll> segs;
    ll size=0;                       
    ll ID=-INF_ADD;
 
    ST(ll sz) {
        segs.assign(2*sz,ID);
        size=sz;  
    }   
   
    ll comb(ll a,ll b) {
        return max(a,b);  
    }
 
    void upd(ll idx, ll val) {
        segs[idx+=size]=val;
        for(idx/=2;idx;idx/=2){
            segs[idx]=comb(segs[2*idx],segs[2*idx+1]);
        }
    }
 
    ll query(ll l,ll r) {
        ll lans=ID,rans=ID;
        for(l+=size,r+=size+1;l<r;l/=2,r/=2) {
            if(l&1) {   
                lans=comb(lans,segs[l++]);
            }
            if(r&1){
                rans=comb(segs[--r],rans);
            }
        }
        return comb(lans,rans);
    }
};
void solve(){   
    ll n,q; cin>>n>>q;
    vector<ll> value(n+5);
    for(ll i=1;i<=n;i++){
        cin>>value[i]; 
    }
    for(ll i=1;i<n;i++){
        ll u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,1); 
    dfs_(1,1);
    vector<ST> segtree; 
    for(ll i=0;i<pos;i++){
        ll pos_val=0;
        ll len=track[i].size();
        ST anot(len); 
        for(ll j=0;j<len;j++){
            index_val[track[i][j]]=j;
            anot.upd(j,value[track[i][j]]); 
        }
        segtree.push_back(anot); 
    }
    while(q--){
        ll x,y,z; cin>>x>>y>>z;
        if(x==1){
            value[y]=z;
            if(chain_no[y]==-1){
                ;
            }
            else{
                segtree[chain_no[y]].upd(index_val[y],z); 
            }
        }
        else{
            ll till_node=lca(y,z);
            ll u=y,v=z;
            ll ans=value[till_node];
            while(u!=till_node){
                ans=max(ans,value[u]);
                if(chain_no[u]==-1){
                    u=parent[u];
                }
                else{
                    ll jump_to=0;
                    if(chain_no[till_node]==chain_no[u]){
                        jump_to=index_val[till_node];
                    }
                    ans=max(ans,segtree[chain_no[u]].query(jump_to,index_val[u]));
                    u=track[chain_no[u]][jump_to]; 
                    if(u!=till_node){
                        u=parent[u]; 
                    }
                }
            }
            u=v;
            while(u!=till_node){
                ans=max(ans,value[u]);
                if(chain_no[u]==-1){
                    u=parent[u];
                }
                else{
                    ll jump_to=0;
                    if(chain_no[till_node]==chain_no[u]){
                        jump_to=index_val[till_node];
                    }
                    ans=max(ans,segtree[chain_no[u]].query(jump_to,index_val[u]));
                    u=track[chain_no[u]][jump_to]; 
                    if(u!=till_node){
                        u=parent[u]; 
                    }
                }
            }
            cout<<ans<<" "; 
        }
    }
    return;                                  
}             
