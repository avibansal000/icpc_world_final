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
