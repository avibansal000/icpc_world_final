struct line
{
    ll m=0,c=0;
    ll val(ll v){return m*v+c;}
};
struct node
{
    line a;
    node *left = NULL,*right=NULL;
};
struct cvxtrick
{   // by default by max
    node *root = new node;
    void init(ll p)
    {
        mx = p;
        root->a.m = 0;
        root->a.c = 0;
    }
    ll mx;
    void add_line(ll m1, ll c)
    {
        node *curr = root;
        ll l = 0;
        ll r = mx;
        line p = {m1, c};
        line p1 = p;
        while (l <= r)
        {
            ll m = (r + l) / 2;
            if (curr->a.val(l) >= p.val(l) && curr->a.val(r) >= p.val(r))   
            {
                // curr->a = p; //in case of min
                break;
            }   
            else if (curr->a.val(l) <= p.val(l) && curr->a.val(r) <= p.val(r))
            {
                curr->a = p;  // not there in case of min
                break;
            }
            bool mid = (curr->a.val(m) < p.val(m));  // change here
            bool lf = (curr->a.val(l) < p.val(l)); // change here

            if (mid)
            {
                swap(curr->a, p);
            }
            if (mid == lf)
            {
                l = m + 1;
                if (curr->right == NULL)
                {
                    curr->right = new node;
                    curr = curr->right;
                    curr->a=p;
                    break;
                }
                curr = curr->right;
            }
            else
            {
                r = m;
                if (curr->left == NULL)
                {
                    curr->left = new node;
                    curr = curr->left;
                    curr->a=p;
                    break;
                }
                curr = curr->left;
            }
        }
    }
    ll find_val(ll x)
    {
        node *curr = root;
        ll l = 0;
        ll r = mx;
        ll ans = 0;
        while (l <= r)
        {
            if (curr == NULL)
            {
                break;
            }
            else
            {
                ll m = (r + l) / 2;
                ans = max(ans, curr->a.val(x));  // change in case of min
                if (x > m)
                {
                    l = m + 1;
                    curr = curr->right;
                }
                else
                {
                    r = m;
                    curr = curr->left;
                }
            }
        }
        return ans;
    }
};