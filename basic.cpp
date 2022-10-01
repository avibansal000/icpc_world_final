#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
typedef vector<ll> vl; 
typedef vector<int> vi; 
#include <sys/time.h>
ll expo(ll a, ll b, ll mod = MOD)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}
ll mminvprime(ll a, ll b = MOD)
{
    return expo(a, b - 2, b);
}
void solve(){
    
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt=1;
    cin>>tt;
    struct timeval st,et;
    gettimeofday(&st,NULL);
    while(tt--){
        solve();
    }
    gettimeofday(&et,NULL);
    cerr<<"time: "<<(double)((et.tv_sec-st.tv_sec)*1000000+et.tv_usec-st.tv_usec)/1000<<"ms\n";

}