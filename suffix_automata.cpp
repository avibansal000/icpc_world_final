struct suffix_auto{
    struct node
    {
        ll link=-1,len=0,cnt=0;
        bool clone = false;
        map<char, ll> next;
    };
    ll sz = 1,len=0,last=0;
    vector<node> st;
    suffix_auto(string s)
    {
        int n=s.size();
        st.resize(2*n);
        for(auto e: s)add_c(e);
    }
    void add_c(char c)
    {
        int p = last;
        len++;
        int curr = sz++;
        st[curr].len = len;
        while (p != -1 && st[p].count(c) == 0)
        {
            st[p].next[c] = curr;
            p = st[p].link;
        }
        if (p == -1)st[curr].link = 0;
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
                    if (st[p].count(c) && st[p].next[c] == q)
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
    //not necessary code depends on problems
    void add_cnt()  // value of values in endpos set of the node
    {
        int n = len;
        vvl val(n + 1);
        for(int i=1;i<sz;i++)
        {
            if (!st[i].clone)
            {
                st[i].cnt = 1;
            }
            val[st[i].len].push_back(i);
        }
        for (int i = n; i > 0; i--)
        {
            for(auto e: val[i])
            {
                st[st[e].link].cnt += st[e].cnt;
                st[st[e].link].cnt %= MOD;
            }
        }
    }
    // int k;
    // dp[v] stores no. of different path from v to any node in subtree
    vector<ll> dp; // better to initialize in constuctor
    void init(){
        dp.resize(sz+1,0);
    }
    vl color(2e6+2,0);
    void dfs(int v)
    {
        dp[v] = 1;
        color[v]=1;
        for(auto e: st[v].next)
        {
            if(color[e.second]==0)
            dfs(e.second);
            dp[v] += dp[e.second];
            // dp[v] %= MOD;
        }
    }
    string s_k;
    //find kth
    void find(int k, int v)
    {
        for(auto e: st[v].next)
        {
            if (dp[e.second] >= k)
            {
                k -= 1;
                s_k.push_back(e.first);
                if (k <= 0)return ;
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
};