struct node
{
    ll link;
    ll len;
    map<char, ll> next;
    bool is_exist(char d)
    {
        if (next.find(d) == next.end())
            return false;
        return true;
    }
    bool clone = false;
    ll cnt = 0;
};
ll sz = 0;
ll len = 0;
ll last = 0;
vector<node> st(2 * 1e6 + 2);
void init_sa()
{
    st[0].len = 0;
    st[0].link = -1;
    sz++;
}
void add_c(char c)
{
    int p = last;
    // sz++;
    len++;
    int curr = sz++;
    st[curr].len = len;
    // debug(curr);
    while (p != -1 && st[p].is_exist(c) == false)
    {
        st[p].next[c] = curr;
        p = st[p].link;
    }
    if (p == -1)
    {
        st[curr].link = 0;
    }
    else
    {
        int q = st[p].next[c];
        if (st[q].len == st[p].len + 1)
        {
            st[curr].link = q;
        }
        else
        {
            int clone = sz++;
            st[clone] = st[q];
            st[q].link = clone;
            st[clone].len = st[p].len + 1;
            st[curr].link = clone;
            st[clone].clone = true;
            while (p != -1)
            {
                if (st[p].is_exist(c) && st[p].next[c] == q)
                {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                else
                {
                    break;
                }
            }
        }
    }
    last = curr;
}

void make_sa(str s)
{
    init_sa();
    trav(e, s)
    {
        add_c(e);
    }
}
void add_cnt()  // value of endpos set of  string  ending at node
{
    int n = len;
    int i;
    vvl val(n + 1);
    fi(i, 1, sz)
    {
        if (!st[i].clone)
        {
            st[i].cnt = 1;
        }
        val[st[i].len].push_back(i);
    }
    for (i = n; i > 0; i--)
    {
        trav(e, val[i])
        {
            st[st[e].link].cnt += st[e].cnt;
            st[st[e].link].cnt %= MOD;
        }
    }
}
// int k;
// no. of different substrings at a node number of paths from t0 to its subtree.
vector<ll> dp(2 * 1e6 + 2);
vl color(2e6+2,0);
void dfs(int v)
{
    dp[v] = 1;
    color[v]=1;
    trav(e, st[v].next)
    {
        if(color[e.second]==0)
        dfs(e.second);
        dp[v] += dp[e.second];
        // dp[v] %= MOD;
    }
}
str s;

//find kth
void find(int k, int v)
{
    trav(e, st[v].next)
    {
        if (dp[e.second] >= k)
        {
            k -= 1;
            s.push_back(e.first);
            if (k <= 0)
            {
                return;
            }

            find(k, e.second);
            return;
        }
        else
        {
            k -= dp[e.second];
        }
    }
}
// dp holds number of substrings from a node in its subtree.
//total length of all substrings simple dp in graph
// lezicographically kth substring above code 
// number of occurences  --> using cnt;
