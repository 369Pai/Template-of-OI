#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Flow
{
	static const int N = 250 , M = 5050;
	static const ll INF = 0x3f3f3f3f3f3f3f3fll;
	int s , t , tot = 1 , now[N] , head[N]; ll minc , dis[N];
	bool vis[N]; struct Edge{int to , nxt; ll f , w;}e[M * 2];
	void Add(int u , int v , ll f , ll w){e[++tot] = {v , head[u] , f , w} , head[u] = tot;}
	void addEdge(int u , int v , ll f , ll w = INF)
	{
		Add(u , v , f , w == INF ? 1 : w);
		Add(v , u , 0 , w == INF ? 1 : -w);
	}
	bool BFS()
	{
		queue<int>q;
		memset(dis , 0x3f , sizeof dis);
		memcpy(now , head , sizeof now);
		dis[s] = 0 , q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop(); vis[u] = 0;
			for(int i = head[u] ; i ; i = e[i].nxt)
			{
				ll v = e[i].to , f = e[i].f , w = e[i].w;
				if(f && dis[u] + w < dis[v])
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
			ll v = e[i].to , f = e[i].f , w = e[i].w;
			if(f && !vis[v] && dis[u] + w == dis[v])
			{
				ll k = Dinic(v , min(f , rest));
				if(!k)dis[v] = -INF;
				e[i].f -= k , e[i ^ 1].f += k;
				rest -= k , minc += k * w;
			}
		}
		vis[u] = 0;
		return flow - rest;
	}
	void Dfs(int u)
	{
		vis[u] = 1;
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , f = e[i].f;
			if(f && !vis[v])Dfs(v);
		}
	}
	ll flow(int ss , int tt)
	{
		ll maxf = 0; s = ss , t = tt;
		while(BFS())maxf += Dinic(s , INF);
		Dfs(s); return maxf;
	}
	pair<ll , ll> cost(int ss , int tt)
	{
		ll maxf = 0; minc = 0 , s = ss , t = tt;
		while(BFS())maxf += Dinic(s , INF);
		Dfs(s); return make_pair(maxf , minc);
	}
	void clear()
	{
		tot = 1;
		memset(head , 0 , sizeof head);
		memset(vis , 0 , sizeof vis);
	}
}flow;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	int n , m , s , t;
	cin >> n >> m >> s >> t;
	for(int i = 1 ; i <= m ; i++)
	{
		int u , v , w , c;
		cin >> u >> v >> w >> c;
		flow.addEdge(u , v , w , c);
	}
	auto [mf , mc] = flow.cost(s , t);
	cout << mf << ' ' << mc << "\n";
	return 0;
}