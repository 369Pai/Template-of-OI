#include<bits/stdc++.h>
using namespace std;
typedef pair<int , int> PI;
const int N = 5e3+5 , M = 5e4 + 5 , INF = 0x3f3f3f3f;
int n , m , s , t , tot = 1 , head[N] , minc , maxf;
struct Edge{int to , nxt , f , c;}e[M * 2];
int now[N] , dis[N] , h[N]; bool vis[N] , jump[N];
queue<int>q; priority_queue<PI , vector<PI> , greater<PI> >pq;
void Add(int u , int v , int f , int w)
{
	e[++tot] = {v , head[u] , f , w};
	head[u] = tot;
}
bool SPFA()
{
	memset(h , 0x3f , sizeof h);
	q.push(s) , vis[s] = 1 , h[s] = 0;
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , w = e[i].c;
			if(e[i].f && h[u] + w < h[v])
			{
				h[v] = h[u] + w;
				if(!vis[v])q.push(v) , vis[v] = 1;
			}
		}
	}
	return h[t] != INF;
}
bool Dijkstra()
{
	for(int i = 1 ; i <= n ; i++)
		h[i] += dis[i];
	memcpy(now , head , sizeof now);
	memset(dis , 0x3f , sizeof dis);
	memset(vis , 0 , sizeof vis);
	memset(jump , 0 , sizeof jump);
	pq.push(make_pair(0 , s)) , dis[s] = 0;
	while(!pq.empty())
	{
		int u = pq.top().second; pq.pop();
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , w = e[i].c + h[u] - h[v];
			if(e[i].f && dis[u] + w < dis[v])
			{
				dis[v] = dis[u] + w;
				pq.push(make_pair(dis[v] , v));
			}
		}
	}
	return dis[t] != INF;
}
int Dinic(int u , int flow)
{
	if(u == t)return flow;
	int rest = flow;
	vis[u] = 1;
	for(int i = now[u] ; i && rest ; now[u] = i , i = e[i].nxt)
	{
		int v = e[i].to , w = e[i].c + h[u] - h[v];
		if(!vis[v] && e[i].f && dis[v] == dis[u] + w && !jump[v])
		{
			int k = Dinic(v , min(flow , e[i].f));
			if(!k){jump[v] = 1;continue;}
			e[i].f -= k , e[i ^ 1].f += k;
			rest -= k , minc += k * e[i].c;
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
		int u , v , c , w;
		scanf("%d%d%d%d" , &u , &v , &c , &w);
		Add(u , v , c , w) , Add(v , u , 0 , -w);
	}
	SPFA();
	while(Dijkstra())maxf += Dinic(s , INF);
	printf("%d %d" , maxf , minc);
	return 0;
}
