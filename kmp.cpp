// calculate the prefix function 
vector<int> prefix_function(string s)
{
    int n = s.size();
    vector<int> p(n, -1);
    for (int i = 1; i < n; i++)
    {
        int j = p[i - 1];
        while (j > -1 && s[i] != s[j + 1])
        {
            j = p[j];
        }
        if (s[i] == s[j + 1])
        {
            j++;
        }
        p[i] = j;
    }
    return p;
}
// pattern matcher
vector<int> kmp_check(string a, string b)
{
    vector<int> pref = prefix_function(b);
    int i = 0;
    int j = 0;
    int n = a.size();
    int m = b.size();
    vector<int> pos;
    for (; i < n;)
    {
        if (a[i] == b[j])
        {
            if (j == m-1)
            {
                pos.push_back(i - m+1);
                j=pref[j];
            }
            i++;
            j++;
        }
        else{
            if(j>0)
            j=pref[j-1]+1;
            else{
                i++;
                j=0;
            }
        }
    }
    return pos;
}