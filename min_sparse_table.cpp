#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h> 
#include <complex>
#include <queue>
#include <set>
#include <unordered_set>
#include <list>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <iomanip>
#include <fstream>
    
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int,int> p32;
typedef pair<ll,ll> p64;
typedef pair<double,double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int> > vv32;
typedef vector<vector<ll> > vv64;
typedef vector<vector<p64> > vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
typedef vector<set<ll>> vset;
#define forn(i,e) for(ll i = 0; i < e; i++)
#define forsn(i,s,e) for(ll i = s; i < e; i++)
#define rforn(i,s) for(ll i = s; i >= 0; i--)
#define rforsn(i,s,e) for(ll i = s; i >= e; i--)
#define ln "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

void solve(){
        ll n;
        cin>>n;
        v64 a(n);
        forn(i,n)cin>>a[i];
        v64 Log(n+1);
        Log[1]=0;
        forsn(i,2,n+1)Log[i]=Log[i/2]+1;
        ll k=log2(n)+1;
        ll st[n][k];
        forn(i,n)st[i][0]=a[i];
        forsn(i,1,k+1){
            forn(j,n-(1<<i)+1){
                ll v1=st[j][i-1];
                ll v2=st[j+(1<<(i-1))][i-1];
                st[j][i]=min(v1,v2);
            }
        }
        ll q;
        cin>>q;
        while(q--){
            ll l,r;
            cin>>l>>r;
            l--;r--;
            ll len=(r-l+1);
            ll jump=Log[len];
            cout<<min(st[l][jump],st[r+1-(1<<jump)][jump])<<ln;
        }
        return;
}
int main()
{

 fast_cin();
 solve();
 return 0;
}
