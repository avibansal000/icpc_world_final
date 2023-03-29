// calculates z-function which is at position z[i]=max(k| s(0...k-1)==s(i....i+k-1)
vector<ll> z_function(string s){
    int n=s.size();
    vl z(n,0);
    z[0]=n;
    ll l=0, r=0;
    for( int i=1;i<n;i++){
        if( r>=i){
            z[i]=min(r-i+1,z[i-l]);
        }
        while(z[i]<n-i&&s[i+z[i]]==s[z[i]])z[i]++;
        if(r<i+z[i]-1){
            r=z[i]+i-1;
            l=i;
        }
    }
    return z;
}
// Z_function can be used to calculate array cnt() where cnt[i] = numbers of substring of string s which occurs exactly i times in O(n^2);
vl cnt(n+1,0);
for( int j=0;j<n;j++){
    vl ans=z_function(s); // z array
    s.erase(s.begin()); 
    vl q(n+1,0);
    for( auto e: ans)q[e]++;
    for(int i=n-1;i>0;i--){
        q[i]+=q[i+1];
    }
    for( int i=1;i<=n;i++){
        cnt[q[i]]++;
    }
}
for( int i=1;i<n;i++){
    cnt[i]-=cnt[i+1];
}
