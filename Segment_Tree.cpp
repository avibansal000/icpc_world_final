
// Lazy additions
// In case of index queries only have to change sum accordingly
vector<ll> t;
vector<ll> marked;
void push(int v, int l, int r)
{
    if (marked[v])
    {
        int m = (l + r) / 2;
        marked[2 * v] += marked[v];
        marked[2 * v + 1] += marked[v];
        t[2 * v] = t[2*v]+marked[v]*(m-l+1); //ignore range part for min max
        t[2 * v + 1] = t[2*v+1]+marked[v]*(r-m); // ignore range part for min max
        marked[v] = 0;
    }
}
void update(ll v, ll tl, ll tr, ll i, ll j, ll new_val)
{
    if (tr < i || tl > j)
    {
        return;
    }
    if (tl >= i && tr <= j)
    {
        marked[v] += new_val;
        t[v] = t[v] + new_val*(tr-tl+1);   //ignore range part for min max
        return;
    }
    else
    {
        push(v, tl, tr);
        ll tm = (tl + tr) / 2;
        update(v * 2, tl, tm, i,j, new_val);
        update(v * 2 + 1, tm + 1, tr, i,j, new_val);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}
ll sum(ll v, ll tl, ll tr, ll l, ll r)
{
    if (tr<l||tl>r)
        return 0;    //change for min max
    if (l == tl && r == tr)
    {
        return t[v];
    }
    ll tm = (tl + tr) / 2;
    push(v,tl,tr);
    return combine(sum(v * 2, tl, tm, l, min(r, tm)), sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}
void build(vector<ll> &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
    {
        t[v] = a[tl ];
    }
    else
    {
        ll tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}
ll combine(ll a, ll b)
{
    return (a + b);
}
//index find sum
ll sum(ll v, ll tl, ll tr, ll l, ll r,ll val)
{
    if (l>r)
        return -1;
    if (l == tl && r == tr)
    {
        if(t[v]>=val)return -1;    // return a value which will not interfere with answer

        while(l!=r){
            push(v,l,r);
            int m=(l+r)/2;
            if(t[2*v]<val){   //will depend on lesser or greater value we want
                r=m;
                v=2*v;
            }
            else{
                l=m+1;
                v=2*v+1;
            }
        }
        return l;
        
    }
    ll tm = (tl + tr) / 2;
    push(v,tl,tr);
    int p=sum(v * 2, tl, tm, l, min(r, tm),val);
    if(p!=-1)return p;

    return sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r,val);
}
//Lazy Assignment other functions are similar to upper one

vector<ll> t;
vector<bool> marked;
void push(int v, int l, int r)
{
    if (marked[v])
    {
        int m = (l + r) / 2;
        t[2 * v] = t[v] / (r - l + 1) * (m - l + 1);   //For min max remove the range multipication
        t[2 * v + 1] = t[v] / (r - l + 1) * (r - m);
        marked[2 * v] = true;
        marked[2 * v + 1] = true;
        marked[v] = false;
    }
}
void update(ll v, ll tl, ll tr, ll i, ll j, ll new_val)
{
    if (tr < i || tl > j)
    {
        return;
    }
    if (tl >= i && tr <= j)
    {
        t[v] = (tr - tl + 1) * new_val;   //For min max remove the range multipication
        marked[v] = true;
        return;
    }
    else
    {
        push(v, tl, tr);
        ll tm = (tl + tr) / 2;
        update(v * 2, tl, tm, i,j, new_val);
        update(v * 2 + 1, tm + 1, tr, i,j, new_val);
        t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
}

