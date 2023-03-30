struct Sparse_Table{
    vector<vector<ll>> spar;
    vector<ll> logr;
    vector<ll> power;
    ll till=0;
    Sparse_Table(ll n){
        ll x=n;
        while(x){
            x/=2;
            till++;
        }
        power.resize(till+5);
        logr.resize(n+5);
        spar=vector<vector<ll>>(n+5,vector<ll>(till+5,-MOD));
        power[0]=1;
        for(ll i=0;i<till;i++){
            if(i){
                power[i]=power[i-1]*2;
                if(power[i]<=n){
                    logr[power[i]]=i;
                }
            }
        }
        for(ll i=1;i<=n;i++){
            logr[i]=max(logr[i],logr[i-1]);
        }   
    }  
    ll combine(ll l,ll r){
        return max(l,r);
    }
    void build(vector<ll> a){
        ll n=a.size();
        for(ll i=n-1;i>=0;i--){
            spar[i][0]=a[i];
            for(ll j=1;j<till;j++){
                ll rght=min(n,i+power[j-1]);
                spar[i][j]=combine(spar[i][j-1],spar[rght][j-1]);
            }
        }
    }
    ll query(ll l,ll r){
        if(l>r){
            return -MOD;
        }
        ll len=r-l+1;
        return combine(spar[l][logr[len]],spar[r-power[logr[len]]+1][logr[len]]);
    }
};
