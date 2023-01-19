#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> PI;
inline char Gc(){return getchar();}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
const int N = 210 , M = 1e4 + 5 , INF = 0x3f3f3f3f;
int n , m , s , t , s_ , t_ , a[N] , ex[N] , h[N] , gap[N];
int low[M] , upp[M]; bool vis[N]; priority_queue<PI>pq;
int tot = 1 , head[N];
struct Edge{int to , nxt , f;}e[M * 2 + N * 2];
void Add(int u , int v , int f)
{
	e[++tot] = {v , head[u] , f};
	head[u] = tot;
}
int HLPP(int s_ , int t_)
{
	memset(ex , 0 , sizeof ex);
	memset(gap , 0 , sizeof gap);
	memset(vis , 0 , sizeof vis);
	memset(h , 0 , sizeof h);
	vis[s_] = vis[t_] = 1;
	h[s_] = n + 1;
	for(int i = head[s_] ; i ; i = e[i].nxt)
	{
		int v = e[i].to , f = e[i].f;
		if(f)
		{
			ex[s_] -= f , ex[v] += f;
			e[i].f -= f , e[i ^ 1].f += f;
//			cout << v << ' ' << vis[v] << endl;
			if(!vis[v])pq.push(make_pair(h[v] , v)) , vis[v] = 1;
		}
	}
	for(int i = 0 ; i <= n + 1 ; i++)
		if(h[i] < n + 1)gap[h[i]]++;
//	cout << pq.size() << endl;
	while(!pq.empty())
	{
		int u = pq.top().second; pq.pop();
//		cout << u << endl;
		vis[u] = 0;
		for(int i = head[u] ; i && ex[u] ; i = e[i].nxt)
		{
			int v = e[i].to , f = e[i].f;
			if(f && h[u] == h[v] + 1)
			{
				int k = min(f , ex[u]);
				ex[u] -= k , ex[v] += k;
				e[i].f -= k , e[i ^ 1].f += k;
				if(!vis[v])pq.push(make_pair(h[v] , v)) , vis[v] = 1;
			}
		}
		if(!ex[u])continue;
		if(h[u] <= n + 1 && !--gap[h[u]])
			for(int i = 1 ; i <= n ; i++)
				if(h[i] > h[u] && h[i] <= n + 1)
					h[i] = n + 1;
		int minh = INF;
		for(int i = head[u] ; i ; i = e[i].nxt)
			if(e[i].f)minh = min(minh , h[e[i].to]);
		h[u] = minh + 1;
		if(h[u] <= n + 1)gap[h[u]]++;
		pq.push(make_pair(h[u] , u)) , vis[u] = 1;
	}
//	printf("f:%d\n" , ex[t_]);
	return ex[t_];
}
int main()
{	
	n = Read() , m = Read() , s = Read() , t = Read();
	Add(t , s , INF) , Add(s , t , 0);
	s_ = 0 , t_ = n + 1;
	for(int i = 1 ; i <= m ; i++)
	{
		int u = Read() , v = Read();
		low[i] = Read() , upp[i] = Read();
		Add(u , v , upp[i] - low[i]) , Add(v , u , 0);
		a[v] += low[i] , a[u] -= low[i];
	}
	int sf = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		if(a[i] > 0)Add(s_ , i , a[i]) , Add(i , s_ , 0) , sf += a[i];
		if(a[i] < 0)Add(i , t_ , -a[i]) , Add(t_ , i , 0);
	}
//	for(int i = 2 ; i <= tot ; i += 2)
//		cout << e[i ^ 1].to << ' ' << e[i].to << ' ' << e[i].f << endl;	
	if(HLPP(s_ , t_) != sf)puts("please go home to sleep");
	else
	{
		int maxf = e[3].f;
		e[2].f = e[3].f = 0;
		maxf += HLPP(s , t);
		printf("%d\n" , maxf);
	}
	return 0;
}
