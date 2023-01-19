#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 1e2 + 5;
int n , deg[N];
int tot , head[N] , nxt[N * 2] , to[N * 2];
queue<int>q;
void Add(int u , int v)
{
	to[++tot] = v , nxt[tot] = head[u] , head[u] = tot;
}
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		int x; scanf("%d" , &x);
		while(x)
		{
			Add(i , x);
			deg[x]++;
			scanf("%d" , &x);
		}
	}
	for(int i = 1 ; i <= n ; i++)
		if(!deg[i])q.push(i);
	while(!q.empty())
	{
		int t = q.front(); q.pop();
		printf("%d " , t);
		for(int i = head[t] ; i ; i = nxt[i])
		{
			int v = to[i];
			if(!--deg[v])q.push(v);
		}
	}
	return 0;
}
