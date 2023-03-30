//Lazy Segment Tree supporting range assignment, range addition and range query

struct segment_tree{
    ll n;
    vector<ll> len,segt;
    vector<ll> lazy,mark;
    segment_tree(ll n){
        this->n=n;
        len.resize(4*n,0);
        segt.resize(4*n,0);
        lazy.resize(4*n,0); 
        mark.resize(4*n,0); 
    }
    void build(vector<ll> &a){
        build(a,1,1,n);
    }
    void build(vector<ll> &a,ll v,ll l,ll r){
        if(l==r){
            len[v]=1;
            segt[v]=a[l];
        }   
        else{  
            ll m=(l+r)/2;
            build(a,2*v,l,m);
            build(a,2*v+1,m+1,r);
            segt[v]=segt[2*v]+segt[2*v+1];  
            len[v]=len[2*v]+len[2*v+1];   
        }    
    }   
    void push(ll v){
        if(mark[v]){
            segt[2*v]=segt[2*v+1]=0; 
            lazy[2*v]=lazy[2*v+1]=0; 
            mark[2*v]=mark[v];
            mark[2*v+1]=mark[v];
        }
        segt[2*v]+=(mark[v]+lazy[v])*len[2*v];
        segt[2*v+1]+=(mark[v]+lazy[v])*len[2*v+1];
        lazy[2*v]+=lazy[v];
        lazy[2*v+1]+=lazy[v];  
        lazy[v]=mark[v]=0; 
    }
    void inc_update(ll l,ll r,ll delta){  
        inc_update(1,1,n,l,r,delta);   
    }         
    void inc_update(ll v,ll l,ll r,ll ql,ll qr,ll delta){  
        if(ql>qr){  
            return; 
        }
        if((l==ql) and (r==qr)){  
            segt[v]+=len[v]*delta; 
            lazy[v]+=delta; 
        }
        else{   
            ll m=(l+r)/2;
            push(v);
            inc_update(2*v,l,m,ql,min(m,qr),delta);
            inc_update(2*v+1,m+1,r,max(m+1,ql),qr,delta);
            segt[v]=segt[2*v]+segt[2*v+1]; 
        }
    }
    void set_update(ll l,ll r,ll val){
        set_update(1,1,n,l,r,val);   
    }
     void set_update(ll v,ll l,ll r,ll ql,ll qr,ll val){  
        if(ql>qr){  
            return; 
        }
        if((l==ql) and (r==qr)){  
            segt[v]=len[v]*val; 
            mark[v]=val; 
            lazy[v]=0; 
        }
        else{   
            ll m=(l+r)/2;
            push(v);
            set_update(2*v,l,m,ql,min(m,qr),val);
            set_update(2*v+1,m+1,r,max(m+1,ql),qr,val);
            segt[v]=segt[2*v]+segt[2*v+1]; 
        }
    }
    ll query(ll l,ll r){
        return query(1,1,n,l,r);
    }
    ll query(ll v,ll l,ll r,ll ql,ll qr){
        if(ql>qr){   
            return 0;
        }   
        if((l==ql) and (r==qr)){  
            return segt[v]; 
        }
        ll m=(l+r)/2;
        push(v); 
        return query(2*v,l,m,ql,min(m,qr))+query(2*v+1,m+1,r,max(ql,m+1),qr); 
    }
};
