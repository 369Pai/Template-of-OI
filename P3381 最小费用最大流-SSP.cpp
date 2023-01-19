#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5e3 + 5 , M = 5e4 + 5 , INF = 0x3f3f3f3f3f3f3f3fll;
int n , m , s , t , tot = 1 , head[N] , now[N];
ll dis[N] , minc;bool vis[N];
queue<int>q , eq;
struct Edge{ll to , nxt , f , c;}e[M * 2];
void Add(int u , int v , int w , int c)
{
	e[++tot] = {v , head[u] , w , c};
	head[u] = tot;
}
bool SPFA()
{
	memset(vis , 0 , sizeof vis);
	memset(dis , 0x3f , sizeof dis);
	memcpy(now , head , sizeof now);
	q = eq ; q.push(s); dis[s] = 0;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , w = e[i].c;
			if(dis[u] + w < dis[v] && e[i].f > 0)
			{
				dis[v] = dis[u] + w;
				if(!vis[v])q.push(v) , vis[v] = 1;
			}
		}
	}
	return dis[t] != INF;
}
ll Dinic(int u , ll flow)
{
	if(u == t)return flow;
	ll rest = flow;
	vis[u] = 1;
	for(int i = now[u] ; i && rest ; now[u] = i , i = e[i].nxt)
	{
		int v = e[i].to; ll w = e[i].c;
		if(!vis[v] && e[i].f && dis[v] == dis[u] + w)
		{
			ll k = Dinic(v , min(rest , e[i].f));
			if(!k)dis[v] = -INF;
			e[i].f -= k , e[i ^ 1].f += k;
			rest -= k , minc += k * w;
		}
	}
	vis[u] = 0;
	return flow - rest;
}
int main()
{
	scanf("%d%d%d%d" , &n , &m , &s , &t);
	for(int i = 1 ; i <= m ; i++)
	{
		int u , v , w , c;
		scanf("%d%d%d%d" , &u , &v , &w , &c);
		Add(u , v , w , c);
		Add(v , u , 0 , -c);
	}
	ll maxf = 0; minc = 0;
	while(SPFA())maxf += Dinic(s , INF);
	printf("%lld %lld" , maxf , minc);
	return 0;
}
