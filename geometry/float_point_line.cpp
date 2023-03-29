ld epsilon =1e-12;
bool equal(ld a,ld b){
    return abs(a-b)<=epsilon;
}

struct point {
    ld x=0;
    ld y=0;
    point (ld x=0, ld y=0){
        this->x=x;
        this->y=y;
    }
    ld cross(point&b){
        return x*b.y-y*b.x;
    }
    ld dot(point &b){
        return x*b.x-y*b.y;
    }
    ld dis(point& b){
        ld disx=x-b.x;
        ld disy=y-b.y;
        return sqrtl(disx*disx+disy*disy);
    }
    bool operator<=(point & b){ //imp
        if(equal(x,b.x))return y<b.y+epsilon;
        return x<b.x+epsilon;
    }
    bool operator<(point & b){
        if(equal(x,b.x))return y<b.y;
        return x<b.x;
    }
    bool operator==(point & b){
        if(equal(x,b.x) and equal (y,b.y) )return true;
        return false;
    }
};

struct line{
    ld vert_slp=1e14;
    ld c=0;
    ld m=0;
    line(ld m=0,ld c=0){
        this->c=c; this->m=m;
    }
    line (point & a, point & b){
        if(equal(a.x,b.x)){
            c=-a.x;
            m=vert_slp*10;
        }
        else{
            m=(a.y-b.y)/(a.x-b.x);
            c=a.y-m*a.x;  
        }
    }
    ld val(point & x){ // y-mx-c;
        if(m>vert_slp)return -c;
        return x.y-m*x.x-c;
    }
    pair<point,int> intersect(line & lin){ // 2 all sol, 0 no sol,1 unique sol
        point d;
        if(equal(m,lin.m)||(m>vert_slp&&lin.m>vert_slp)){
            if(equal(c,lin.c)){
                return {d,2};
            }
            return {d,0};
        }
        if(lin.m>vert_slp){
            d.x=-lin.c;
            d.y=m*d.x+c;
        }
        else if(m>vert_slp){
            d.x=-c;
            d.y=lin.m*d.x+lin.c;
        }
        else{
            d.x=(c-lin.c)/(lin.m-m);
            d.y=lin.m*d.x+lin.c;
        }
        return {d,1};
    }
};