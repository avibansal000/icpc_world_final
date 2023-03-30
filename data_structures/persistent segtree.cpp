//(Kth element in sorted range [i, j])

#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
 
const int N = 1e5+5;
const int LG = log2(N) + 1;
 
int a[N];
int n, m, ct=0, num=0;
int root[N], st[21*N], lc[21*N], rc[21*N];
map<int, int> comp;
map<int, int> rcomp;
 
int build(int L, int R)
{
	int node = ++ct;
	if(L==R)
		return node;
	int M = (L+R)/2;
	lc[node] = build(L, M);
	rc[node] = build(M+1, R);
	return node;
}
 
int update(int onode, int L, int R, int pos)
{
	int node = ++ct;
	if(L==R)
	{
		st[node] = st[onode] + 1;
		return node;
	}
	int M = (L+R)/2;
	lc[node] = lc[onode];
	rc[node] = rc[onode];
	if(pos <= M)
		lc[node] = update(lc[onode], L, M, pos);
	else
		rc[node] = update(rc[onode], M+1, R, pos);
	st[node] = st[lc[node]] + st[rc[node]];
	return node;
}
 
int query(int nodeu, int nodev, int L, int R, int pos)
{
	if(L==R)
		return L;
	int M = (L+R)/2;
	int leftval = st[lc[nodev]] - st[lc[nodeu]];
	int rightval = st[rc[nodev]] - st[rc[nodeu]];
	if(leftval>=pos)
		return query(lc[nodeu], lc[nodev], L, M, pos);
	else
		return query(rc[nodeu], rc[nodev], M+1, R, pos - leftval);
}
 
int32_t main()
{
	IOS;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		comp[a[i]];
	}
	for(auto &it:comp)
	{
		it.second = ++num;
		rcomp[num] = it.first;
	}
	for(int i=1;i<=n;i++)
		a[i] = comp[a[i]];
	root[0] = build(1, num);
	for(int i=1;i<=n;i++)
		root[i] = update(root[i-1], 1, num, a[i]);
	for(int i=1;i<=m;i++)
	{
		int u, v, k;
		cin>>u>>v>>k;
		int store = query(root[u-1], root[v], 1, num, k);
		int val = rcomp[store];
		cout<<val<<endl;
	}
	return 0;
} 
