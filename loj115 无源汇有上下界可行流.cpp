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
const int N = 205 , M = 10205;
int n , m , s , t , low[M] , upp[M] , inf[M] , ouf[M] , d[N] , now[N];
int tot = 1 , head[N];
struct Edge{int to , nxt , f;}e[M * 2 + N * 2];
queue<int>q , eq;
void Add(int u , int v , int f)
{
//	cout << u << ' ' << v << ' ' << f << endl;
	e[++tot] = {v , head[u] , f};
	head[u] = tot;
}
bool BFS()
{
	memcpy(now , head , sizeof head);
	memset(d , 0 , sizeof d);
	d[s] = 1;
	q = eq , q.push(s);
	while(!q.empty())
	{
		int u = q.front() ; q.pop();
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
int Dinic(int u , int flow)
{
	if(u == t)return flow;
	int rest = flow;
	for(int i = now[u] ; i && rest ; now[u] = i , i = e[i].nxt)
	{
		int v = e[i].to , f = e[i].f;
		if(f && d[v] == d[u] + 1)
		{
			int k = Dinic(v , min(rest , f));
			if(!k)d[v] = 0;
			e[i].f -= k , e[i ^ 1].f += k;
			rest -= k;
		}
	}	
	return flow - rest;
}
int main()
{
	n = Read() , m = Read();
	for(int i = 1 ; i <= m ; i++)
	{
		int u = Read() , v = Read();
		low[i] = Read() , upp[i] = Read();
		Add(u , v , upp[i] - low[i]) , Add(v , u , 0);
		ouf[u] += low[i] , inf[v] += low[i];
	}
	s = 0 , t = n + 1;
	for(int i = 1 ; i <= n ; i++)
	{
		if(inf[i] > ouf[i])Add(s , i , inf[i] - ouf[i]) , Add(i , s , 0);
		if(inf[i] < ouf[i])Add(i , t , ouf[i] - inf[i]) , Add(t , i , 0);
	}			
	int maxf = 0;
	while(BFS())maxf += Dinic(s , 0x3f3f3f3f);
	bool ans = 1;
	for(int i = head[s] ; i ; i = e[i].nxt)
	{
		if(i & 1)continue;
		if(e[i].f)
		{
			ans = 0;
			break;
		}
	}
	if(!ans)puts("NO");
	else
	{
		puts("YES");
		for(int i = 2 ; i <= tot ; i += 2)
		{
			int u = e[i ^ 1].to , v = e[i].to;
			if(u == s || v == t)break;
			printf("%d\n" , low[i / 2] + e[i ^ 1].f);
		}
	}
	return 0;
}
