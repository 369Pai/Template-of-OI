#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char Gc(){return getchar();}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
const ll N = 5e4 + 10 , M = 1.3e5 + 10 , INF = 0x3f3f3f3f3f3f3f3fll;
int n , m , s , t , S , T , now[N] , d[N];
ll low[M] , upp[M], a[N];
int tot = 1 , head[N];
struct Edge{int to , nxt; ll f;}e[N * 2 + M * 2];
queue<int>q , eq;
void Add(int u , int v , ll f)
{
	e[++tot] = {v , head[u] , f};
	head[u] = tot;
}
bool Bfs()
{
	memcpy(now , head , sizeof head);
	memset(d , 0 , sizeof d);
	d[s] = 1;
	q = eq , q.push(s);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to , f = e[i].f;
			if(f && !d[v])
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
		int v = e[i].to; ll f = e[i].f;
		if(f && d[u] + 1 == d[v])
		{
			ll k = Dinic(v , min(rest , f));
			if(!k)d[v] = 0;
			e[i].f -= k , e[i ^ 1].f += k;
			rest -= k;
		}
	}
	return flow - rest;
}
int main()
{
	n = Read() , m = Read() , S = Read() , T = Read();
	Add(T , S , INF) , Add(S , T , 0);
	for(int i = 1 ; i <= m ; i++)
	{
		int u = Read() , v = Read();
		low[i] = Read() , upp[i] = Read();
		Add(u , v , upp[i] - low[i]) , Add(v , u , 0);
		a[u] -= low[i] , a[v] += low[i];
	}
	s = 0 , t = n + 1;
	ll sf = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		if(a[i] > 0)Add(s , i , a[i]) , Add(i , s , 0) , sf += a[i];
		if(a[i] < 0)Add(i , t , -a[i]) , Add(t , i , 0);
	}
	ll maxf = 0;
	while(Bfs())maxf += Dinic(s , INF);
	if(maxf != sf)puts("please go home to sleep");
	else
	{
		ll minf = e[3].f;
		e[2].f = e[3].f = 0;
		s = T , t = S;
		while(Bfs())minf -= Dinic(s , INF);
		printf("%lld" , minf);
	}
	return 0;
}
