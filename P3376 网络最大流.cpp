#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205 , M = 5e3 + 5 , INF = 0x7fffffff;
int n , m , s , t , d[N] , now[N];
int tot = 1 , head[N];
queue<int>q , eq;
struct Edge
{
	int to , nxt , f;
}e[M * 2];
void Add(int u , int v , int w)
{
	e[++tot] = {v , head[u] , w};
	head[u] = tot;
}
bool Bfs()
{
	memcpy(now , head , sizeof head);
	memset(d , 0 , sizeof d);
	q = eq; q.push(s); d[s] = 1;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to;
			if(e[i].f > 0 && !d[v])
			{
				d[v] = d[u] + 1;
				q.push(v);
				if(v == t)return 1;
			}
		}
	}
	return 0;
}
ll Dinic(int u , ll flow)
{
	if(u == t)return flow;
	ll rest = flow;
	for(int i = now[u] ; i && rest ; now[u] = i , i = e[i].nxt)
	{
		int v = e[i].to;
		if(e[i].f && d[v] == d[u] + 1)
		{
			ll k = Dinic(v , min(rest , (ll)e[i].f));
			if(!k)d[v] = 0;
			e[i].f -= k;
			e[i ^ 1].f += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int main()
{
	scanf("%d%d%d%d" , &n , &m , &s , &t);
	for(int i = 1 ; i <= m ; i++)
	{
		int u , v , w;
		scanf("%d%d%d" , &u , &v , &w);
		Add(u , v , w); Add(v , u , 0);
	}
	ll ans = 0;
	while(Bfs())
	{
		ans += Dinic(s , INF);	
	}
	printf("%lld" , ans);
	return 0;
}
