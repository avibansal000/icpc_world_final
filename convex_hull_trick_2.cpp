// for applying convex hull but with limits on each line in a range like line in valid from (0-r);
struct line
{
    ll m=-INF;
    ll c=-INF;
    ll val(ll v)
    {
        if(m==-INF){
            return -1e18;
        }
        return m * v + c;
    }
};

ll mx;
vector<line> t;
void add(int v,int l,int r,line val,int ind){
    if(l>ind)return;
    if(r<=ind){
        while(l<=r){
            ll m=(l+r)/2;
            bool mid = (t[v].val(m)<val.val(m));  //change in case of min
            bool lf = (t[v].val(l)<val.val(l));  //change in case of min
            if(mid){
                swap(t[v],val);
            }
            if(lf!=mid){
                r=m;
                v=2*v;
            }
            else{
                v=2*v+1;
                l=m+1;
            }
        }
        return;
    }
    else{
        ll m=(l+r)/2;
        add(2*v,l,m,val,ind);
        add(2*v+1,m+1,r,val,ind);

    }
}
ll get(int ind){
    ll ans=-INF;
    int v=1;
    int l=0;
    int r=mx;
    while(l<r){
        ans=max(ans,t[v].val(ind));  //change in case of min
        ll m=(l+r)/2;
        if(ind<=m){
            v=2*v;
            r=m;
        }
        else{
            v=2*v+1;
            l=m+1;
        }
    }
    ans=max(ans,t[v].val(ind));
    return ans;
}


