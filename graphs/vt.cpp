#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<long long> vl;
typedef pair<ll,ll> pl;
ll MOD=998244353;
ll expo(ll a,ll b){
    ll ans=1;
    while(b>0){
        if(b&1){
            ans*=a;
            ans%=MOD;
        }
        a*=a;
        a%=MOD;
        b=(b>>1);
    }
    return ans;
}
vector<ll> important(1e5+1,false);
struct vt{ //1 indexed for  n give input (n+1);
    vector<vector<int>> adj,parent,adj_vt;  // don't forget to clear adj_vt after each query
    vector<int> used,tin,tout,level;
    int timer=0,logn=20; 
    vt(int n){
        adj.resize(n);
        adj_vt.resize(n);
        parent.resize(n,vector<int>(logn));
        used.resize(n,0);
        tin.resize(n,0);
        tout.resize(n,0);
        level.resize(n,0); // ques specific
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v,int p){
        used[v]=1;
        parent[v][0]=p;
        for(int i=1;i<logn;i++){
            parent[v][i]=parent[parent[v][i-1]][i-1];
        }
        tin[v]=timer++;
        for(auto e:adj[v]){
            if(used[e]==0){
                level[e]=level[v]+1;  // ques specific
                dfs(e,v);
            }
        }
        tout[v]=timer++;
    }
    bool check_up(int u, int v)
    {
        return tin[u]<=tin[v]&&tout[u]>=tout[v];
    }
    int lca (int u , int v )
    {
        if(check_up(u,v))return u;
        if(check_up(v,u))return v;
        for(int i=19;i>=0;i--)
        {
            if(check_up(parent[u][i], v)){
            }
            else u=parent[u][i];
        }
        return parent[u][0];
    }
    int make_vt(vector<int>& vec){
        sort(vec.begin(), vec.end(), [&](int u,int v){return tin[u]<tin[v];});
        int m=vec.size();
        for(int i=1;i<m;i++){
            vec.push_back(lca(vec[i-1],vec[i]));
        }
        sort(vec.begin(), vec.end(), [&](int u,int v){return tin[u]<tin[v];});
        vec.erase(unique(vec.begin(),vec.end()), vec.end());
        stack<int> st;
        st.push(vec[0]);
        for(int i=1;i<vec.size();i++)
        {
            int u=vec[i];
            int v=st.top();
            while(st.size()>=2 && !check_up(v,u))
            {
                st.pop();
                adj_vt[st.top()].push_back(v);
                v=st.top();
            }
            st.push(u);
        }
        while(st.size()>1){
            int u=st.top();
            st.pop();
            int v=st.top();
            adj_vt[v].push_back(u);
        }
        return st.top();
    }
    void init(){
        level[1]=0;
        dfs(1,1);
    }
    // ques specific 
    ll solve(vector<int> v){
        ans=0;
        int root=make_vt(v);
        dfs_v(root);
        ans= ((ans>=inf)?-1:ans);
        for(auto e: v){
            adj_vt[e].clear();
            used[e]=0;
        }
        return ans;
    }
    // ques specific
    ll inf=1e6;
    ll ans=0;
    bool dfs_v(int u)  // full ques specific
    {
        int cnt = 0;
        for(int v: adj_vt[u])
        {
            if(important[u] && important[v] && level[u] + 1 == level[v]) 
                ans = inf;
            cnt += dfs_v(v);
        }
        adj_vt[u].clear();
        if(important[u])
        {
            ans += cnt;
            return 1;
        }
        else
        {
            if(cnt >= 2) 
            {
                ans++;
                return 0;
            }
            if(cnt >= 1) return 1;
            else return 0;
        }
    }
};


int main(){
    ios_base::sync_with_stdio;
    cin.tie(0);
    #ifndef ONLINE_JUDGE                 
        freopen("input.txt", "r", stdin);                                                
        freopen("output.txt", "w", stdout);  
        freopen("error.txt", "w", stderr);                        
    #endif  
    int tt=1;
    int test_case=0;
    while(tt--){   
        int n,q;
        cin>>n;
        vt v(n+1);
        for(int i=0;i<n-1;i++){
            int x,y;
            cin>>x>>y;
            v.add_edge(x,y);
        }
        v.init();
        cin>>q;
        while(q--){
            int x;
            cin>>x;
            vector<int> vec;
            while(x--){
                int r;
                cin>>r;
                vec.push_back(r);
            }
            for(auto e:vec){
                important[e]=1;
            }
            ll ans=v.solve(vec);
            cout<<ans<<"\n";
            for(auto e:vec){
                important[e]=0;
            }
        }
    }  
}