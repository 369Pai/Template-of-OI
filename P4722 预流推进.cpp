#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PI;
#define h first
#define num second
const int N = 1205, M = 1.2e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, top, h[N], gap[N];
ll ex[N]; bool vis[N]; int tot = 1, head[N];
struct Edge{	int to, nxt;	ll f;} e[M * 2];
list<int>pq[N * 2]; queue<int>q;
void Add(int u, int v, int w)
{
	e[++tot] = {v, head[u], w};
	head[u] = tot;
}
void BFS()
{
	memset(h , 0 , sizeof h);
	q.push(t);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to;
			if(e[i ^ 1].f && !h[v])
			{
				h[v] = h[u] + 1;
				q.push(v);
			}
		}
	}
	if(h[s] == 0){printf("0"); exit(0);}
}
ll HLPP()
{
	BFS();
	memset(vis, 0, sizeof vis);
	vis[s] = vis[t] = 1, h[s] = n;
	for (int i = head[s] ; i ; i = e[i].nxt)
	{
		int v = e[i].to;
		if (e[i].f)
		{
			ex[s] -= e[i].f;
			ex[v] += e[i].f;
			e[i ^ 1].f += e[i].f;
			e[i].f = 0;
			if (!vis[v])
			{
				pq[h[v]].push_back(v); top = max(top , h[v]);
				vis[v] = 1;
			}
		}
	}
	for (int i = 1 ; i <= n ; i++)
		if(h[i] <= n)gap[h[i]]++;
	while (top)
	{
		int u = pq[top].back(); pq[top].pop_back();
		while(top && pq[top].empty())top--;
		vis[u] = 0;
		for (int i = head[u] ; i && ex[u] ; i = e[i].nxt)
		{
			int v = e[i].to;
			if (e[i].f && h[u] == h[v] + 1)
			{
				ll k = min(e[i].f, ex[u]);
				e[i].f -= k, e[i ^ 1].f += k;
				ex[u] -= k, ex[v] += k;
				if (!vis[v])
				{
					pq[h[v]].push_back(v); top = max(top , h[v]);
					vis[v] = 1;
				}
			}
		}
		if (!ex[u])continue;
		if (h[u] <= n && !--gap[h[u]])//一个点的h是单调增的（因为每次relable是minh），则如果出现断层,h大的就不能送到t
			for (int i = 1 ; i <= n ; i++)
				if (i != s && i != t && h[i] > h[u] && h[i] < n + 1)
		{
			h[i] = n + 1;
		}
		int minh = INF;
		for (int i = head[u] ; i ; i = e[i].nxt)
			if (e[i].f)minh = min(minh, h[e[i].to]);
		if (minh != INF)
		{
			h[u] = minh + 1;
			pq[h[u]].push_back(u); top = max(top , h[u]);
			vis[u] = 1;
			if(h[u] <= n)++gap[h[u]];
		}
	}
	return ex[t];
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1 ; i <= m ; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		Add(u, v, w);
		Add(v, u, 0);
	}
	printf("%lld", HLPP());
	return 0;
}
