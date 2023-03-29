    ld epsilon=1e-13;
    ll up (ld a){
        ll x=a+1;
        if(abs(x-a)+epsilon>=1){
            x-=1;
        }
        assert(abs(x-a)+epsilon<1);
        return x;
    }
    ll down (ld a){
        ll x=a;
        if(abs(x-a)+epsilon>=1){
            x+=1;
        }
        assert(abs(x-a)+epsilon<1);
        return x;
    }
