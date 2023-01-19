#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e4 + 5;
int n , m , q[105]; bool vis[N] , ans[105];
int tot , head[N] , nxt[N * 2] , to[N * 2] , c[N * 2];
int sz[N] , dis[N] , minsz , center , cnt;
pair<int , int>a[N];
void Add(int u , int v , int w)
{
	to[++tot] = v , c[tot] = w;
	nxt[tot] = head[u] , head[u] = tot; 
}
void GetCenter(int p , int fa , int total)
{
	int maxsz = 0;
	sz[p] = 1;
	for(int i = head[p] ; i ; i = nxt[i])
	{
		int v = to[i];
		if(vis[v] || v == fa)continue;
		GetCenter(v , p , total);
		sz[p] += sz[v];
		maxsz = max(maxsz , sz[v]);
	}
	maxsz = max(maxsz , total - sz[p]);
	if(maxsz < minsz)
	{
		minsz = maxsz;
		center = p;
	}
}
void GetDis(int p , int fa , int rt)
{
	a[++cnt] = make_pair(dis[p] , rt);
	for(int i = head[p] ; i ; i = nxt[i])
	{
		int v = to[i] , w = c[i];
		if(vis[v] || v == fa)continue;
		dis[v] = dis[p] + w;
		if(dis[v] <= 1e7)GetDis(v , p , rt);
	}
}
void Calc(int rt)
{
	dis[rt] = 0;
	a[cnt = 1] = make_pair(0 , rt);
	for(int i = head[rt] ; i ; i = nxt[i])
	{
		int v = to[i];
		if(vis[v])continue;
		dis[v] = c[i];
		GetDis(v , rt , v);
	}
	sort(a + 1 , a + cnt + 1);
	;//cout << '\t' << rt << ':'; 
	for(int i = 1 ; i <= cnt ; i++)
		;//cout << a[i].first << ',' << a[i].second << "  ";
	;//cout << endl;
	for(int i = 1 ; i <= m ; i++)
	{
		int k = q[i];
		;//cout << "\tK" << k << ':';
		for(int l = 1 , r = cnt ; l < r ; l++)
		{
			while(l < r && a[l].first + a[r].first > k)r--;
			if(a[l].first + a[r].first == k && a[l].second != a[r].second)
			{
				ans[i] = 1;
				break;
			}
			;//cout << l << ' ' << r << "  ";
		}
		;//cout << endl;
	}
}
void Dfs(int p)
{
	GetCenter(p , 0 , 0);
	center = 0 , minsz = N;
	GetCenter(p , 0 , sz[p]);
	int rt = center;
	;//cout << rt << ' ' << sz[rt] << endl;
	vis[rt] = 1;
	Calc(rt);
	for(int i = head[rt] ; i ; i = nxt[i])
	{
		int v = to[i];
		if(vis[v])continue;
		Dfs(v);
	}
}
int main()
{
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i < n ; i++)
	{
		int u , v , w;
		scanf("%d%d%d" , &u , &v , &w);
		Add(u , v , w);
		Add(v , u , w);
	}
	for(int i = 1 ; i <= m ; i++)
		scanf("%d" , &q[i]);
	Dfs(1);
	for(int i = 1 ; i <= m ; i++)
		puts((ans[i] ? "AYE" : "NAY"));
	return 0;
}
