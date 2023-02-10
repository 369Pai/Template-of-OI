#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5 , INF = 0x3f3f3f3f;
int rt , tot , fa[N] , ch[N][2] , val[N] , sz[N] , tag[N] , a[N];
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
int New(int v)
{
	tot++;
	val[tot] = v , sz[tot] = 1;
	fa[tot] = lc(tot) = rc(tot) = 0;
	return tot;
}
void Pushup(int p){sz[p] = sz[lc(p)] + sz[rc(p)] + 1;}
void Pushdown(int p)
{
	if(tag[p])
	{
		swap(lc(p) , rc(p));
		tag[lc(p)] ^= 1;
		tag[rc(p)] ^= 1;
		tag[p] = 0;
	}
}
bool Get(int p){return p == rc(fa[p]);}
void Rotate(int x)
{
	Pushdown(fa[x]) , Pushdown(x);
	int y = fa[x] , z = fa[y] , chk = Get(x);
	(ch[y][chk] = ch[x][chk ^ 1]) ? (fa[ch[x][chk ^ 1]] = y) : 0;
	ch[x][chk ^ 1] = y , fa[y] = x;
	(fa[x] = z) ? (ch[z][y == rc(z)] = x) : 0;
	Pushup(y) , Pushup(x);
}
void Splay(int x , int g)
{
	for(int f = fa[x] ; f = fa[x] , f != g ; Rotate(x))
		if(fa[f] != g)Rotate(Get(f) == Get(x) ? f : x);
	if(!g)rt = x;
}
void Build(int l , int r , int& p)
{
	if(l > r)return ;
	int mid = (l + r) >> 1;
	p = New(a[mid]);
	Build(l , mid - 1 , lc(p));
	Build(mid + 1 , r , rc(p));
	fa[lc(p)] = fa[rc(p)] = p , fa[0] = 0;
	Pushup(p);
}
int Kth(int k)
{
	int cur = rt;
	while(1)
	{
		Pushdown(cur);
		if(lc(cur) && k <= sz[lc(cur)])cur = lc(cur);
		else
		{
			k -= sz[lc(cur)] + 1;
			if(k <= 0)
			{
				Splay(cur , 0);
				return cur;
			}
			cur = rc(cur);
		}
	}
}
void Reverse(int l , int r)
{
	int cr = Kth(r + 1) , cl = Kth(l - 1);
	Splay(cr , cl);
	tag[lc(cr)] ^= 1;
}
void Dfs(int p)
{
	if(!p)return ;
	Pushdown(p);
	Dfs(lc(p));
	if(abs(val[p]) != INF)printf("%d " , val[p]);
	Dfs(rc(p));
}
int main()
{
	int n , m;
	scanf("%d%d" , &n , &m);
	a[1] = -INF , a[n + 2] = INF;
	for(int i = 2 ; i <= n + 1 ; i++)a[i] = i - 1;
	Build(1 , n + 2 , rt);
	for(int i = 1 ; i <= m ; i++)
	{
		int l , r; scanf("%d%d" , &l , &r);
		Reverse(l + 1 , r + 1);
	}
	Dfs(rt);
	return 0;
}
