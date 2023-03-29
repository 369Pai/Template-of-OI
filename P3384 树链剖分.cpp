#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
const int N = 1e5 + 5;
int n , m , rt; ll val[N] , tr[N * 4] , tag[N * 4] , mod;
int num , fa[N] , son[N] , sz[N] , dep[N] , dfn[N] , rk[N] , top[N] , bottom[N];
int tot = 1 , head[N];
struct Edge{int to , nxt;}e[N * 2];
void Add(int u , int v){e[++tot] = {v , head[u]} , head[u] = tot;}
void Dfs(int x)
{
	sz[x] = 1;
	for(int i = head[x] ; i ; i = e[i].nxt)
	{
		int y = e[i].to;
		if(sz[y])continue ;
		dep[y] = dep[x] + 1 , fa[y] = x;
		Dfs(y);
		sz[x] += sz[y];
		if(sz[y] > sz[son[x]])son[x] = y;
	}
}
void Dfs(int x , int tp)
{
	bottom[x] = dfn[x] = ++num , rk[num] = x , top[x] = tp;
	if(!son[x])return ;
	Dfs(son[x] , tp);
	bottom[x] = max(bottom[x] , bottom[son[x]]);
	for(int i = head[x] ; i ; i = e[i].nxt)
	{
		int y = e[i].to;
		if(y == fa[x] || y == son[x])continue ;
		Dfs(y , y);
		bottom[x] = max(bottom[x] , bottom[y]);
	}
}
void Add(int len , int p , ll v)
{
	tr[p] = ((ll)v * len + tr[p]) % mod;
	tag[p] = (tag[p] + v) % mod;
}
void Pushup(int p){tr[p] = (tr[p * 2] + tr[p * 2 + 1]) % mod;}
void Pushdown(int l , int r , int p)
{
	if(tag[p])
	{
		int mid = l + r >> 1;
		Add(mid - l + 1 , p * 2 , tag[p]);
		Add(r - mid , p * 2 + 1 , tag[p]);
		tag[p] = 0;
	}
}
void Build(int l , int r , int p)
{
	if(l == r)
	{
		Add(1 , p , val[rk[l]]);
		return ;
	}
	int mid = l + r >> 1;
	Build(l , mid , p * 2);
	Build(mid + 1 , r , p * 2 + 1);
	Pushup(p);
}
void Update(int l , int r , int p , int s , int e , ll v)
{
	if(s <= l && r <= e)
	{
		Add(r - l + 1 , p , v);
		return ;
	}
	Pushdown(l , r , p);
	int mid = l + r >> 1;
	if(s <= mid)Update(l , mid , p * 2 , s , e , v);
	if(mid < e)Update(mid + 1 , r , p * 2 + 1 , s , e , v);
	Pushup(p);
}
ll Query(int l , int r , int p , int s , int e)
{
	if(s <= l && r <= e)return tr[p];
	Pushdown(l , r , p);
	ll mid = l + r >> 1 , ans = 0;
	if(s <= mid)ans = (ans + Query(l , mid , p * 2 , s , e)) % mod;
	if(mid < e)ans = (ans + Query(mid + 1 , r , p * 2 + 1 , s , e)) % mod;
	Pushup(p);
	return ans;
}
int main()
{
	n = Read() , m = Read() , rt = Read() , mod = Read();
	for(int i = 1 ; i <= n ; i++)val[i] = Read();
	for(int i = 1 ; i < n ; i++)
	{
		int u = Read() , v = Read();
		Add(u , v) , Add(v , u);
	}
	dep[rt] = 1;
	Dfs(rt) , Dfs(rt , rt);
	Build(1 , n , 1);
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read() , x = Read() , y , z;
		if(op == 1)
		{
			y = Read() , z = Read();
			while(top[x] != top[y])
			{
				if(dep[top[x]] < dep[top[y]])swap(x , y);
				Update(1 , n , 1 , dfn[top[x]] , dfn[x] , z);
				x = fa[top[x]];
			}
			if(dep[x] > dep[y])swap(x , y);
			Update(1 , n , 1 , dfn[x] , dfn[y] , z);
		}
		if(op == 2)
		{
			y = Read();
			ll ans = 0;
			while(top[x] != top[y])
			{
				if(dep[top[x]] < dep[top[y]])swap(x , y);
				ans = (ans + Query(1 , n , 1 , dfn[top[x]] , dfn[x])) % mod;
				x = fa[top[x]];
			}
			if(dep[x] > dep[y])swap(x , y);
			ans = (ans + Query(1 , n , 1 , dfn[x] , dfn[y])) % mod;
			printf("%lld\n" , (ans + mod) % mod);
		}
		if(op == 3)
		{
			z = Read();
			Update(1 , n , 1 , dfn[x] , bottom[x] , z);
		}
		if(op == 4)
		{
			printf("%lld\n" , (Query(1 , n , 1 , dfn[x] , bottom[x]) % mod + mod) % mod);
		}
	}
	return 0;
}
