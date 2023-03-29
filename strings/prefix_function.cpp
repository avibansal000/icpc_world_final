vector<ll> prefix( string s){ // a[i]=j means (0...j) string is equal to (i-j.....i) || if a[i]==-1 it means no proper prefix of it equals to its suffix
    int n=s.size();
    vl a(n);
    a[0]=-1;
    for( int i=1;i<n;i++){
        int j=a[i-1];
        while(j!=-1){
            if(s[j+1]==s[i])break;
            j=a[j];
        }
        if(s[j+1]==s[i])j++;
        else j=-1;
        a[i]=j;
    }
    return a;   
}
// counting how many substrings occur for a prefix in a string
vl ans=prefix(s);
vl cnt(n,1);
for( int i=n-1;i>=0;i--){
    if( ans[i]!=-1){
        cnt[ans[i]]+=cnt[i];
    }
}
// automata function of strings 
// for a string s we can form a automata which gives prefix function of s#t in O(t) time only, we have to form a dp dp[i][c] which means if current prefix value is i then by adding a character c what will happen
vector<vl> compute_automaton(string s, ) {
    s += '#';
    int n = s.size();
    vl pi = prefix_function(s);
    vector<vl> aut;
    aut.assign(n, vl(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
//please not here aut[i][c] means (0..i-1) is matching now what will happen after we read character c;