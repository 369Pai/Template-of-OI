#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e4 + 5;
int n , sz[N] , dis[N] , minsz , center;
int tot , head[N] , to[N * 2] , nxt[N * 2];
void Add(int u , int v)
{
	to[++tot] = v , nxt[tot] = head[u] , head[u] = tot;
}
void Dfs(int x , int fa)
{
	int maxsz = 0;
	sz[x] = 1;
	for(int i = head[x] ; i ; i = nxt[i])
	{
		int y = to[i];
		if(y == fa)continue;
		Dfs(y , x);
		sz[x] += sz[y];
		maxsz = max(maxsz , sz[y]);		
	}
	maxsz = max(maxsz , n - sz[x]);
	if(maxsz < minsz || (maxsz == minsz && x < center))
	{
		minsz = maxsz;
		center = x;
	}
}
void GetDis(int x , int fa)
{
	for(int i = head[x] ; i ; i = nxt[i])
	{
		int y = to[i];
		if(y == fa)continue;
		dis[y] = dis[x] + 1;
		GetDis(y , x);
	}
}
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i < n ; i++)
	{
		int u , v;
		scanf("%d%d" , &u , &v);
		Add(u , v); Add(v , u);
	}
	center = minsz = N;
	Dfs(1 , 0);
	GetDis(center , 0);
	int ans = 0;
	for(int i = 1 ; i <= n ; i++)
		ans += dis[i];
	printf("%d %d" , center , ans);
	return 0;
}
