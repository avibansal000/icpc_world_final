vl pref;

ll f(ll i,ll j){ // gives hash of string in i and j
    ll ans=pref[j+1]-pref[i];
    ans=divide(ans,expo(d,i)); // 
    return ans;
}
// in main function
ll curr=1;
for( int i=0;i<n;i++){
    pref[i+1]=add(pref[i],a[i]*curr);
    curr=mul(curr,d);
}