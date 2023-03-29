string s;cin>>s;
int n=s.size();
vector<int> d1 (n); // odd length palindromes centered on i 
int l=0, r=-1;
for (int i=0; i<n; ++i) {
    int k = i>r ? 1 : min (d1[l+r-i], r-i+1);
    while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])++k;
    d1[i] = k;
    if (i+k-1 > r)l = i-k+1,  r = i+k-1;
}
vector<int> d2 (n); // even length palindromes centered on {i-1,i}
l=0, r=-1;
for (int i=0; i<n; ++i) {
    int k = i>r ? 0 : min (d2[l+r-i+1], r-i+1);
    while (i+k < n && i-k-1 >= 0 && s[i+k] == s[i-k-1])  ++k;
    d2[i] = k;
    if (i+k-1 > r)l = i-k,  r = i+k-1;
}
for(auto e:d1)cout<<e<<" ";cout<<endl;
for(auto e:d2)cout<<e<<" ";cout<<endl;
// palindromes in O(n)