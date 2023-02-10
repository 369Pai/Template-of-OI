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
const int N = 1.1e6 + 5;
const double ALPHA = 0.6874;
int rt , tot , lc[N] , rc[N] , val[N] , cnt[N] , s[N] , sd[N] , sz[N];
int tc , a[N] , *sgt , zero;
int New(int v)
{
	val[++tot] = v;
	cnt[tot] = sz[tot] = 1;	
	return tot;
}
void Pushup(int p)
{
	s[p] = s[lc[p]] + s[rc[p]] + 1;
	sz[p] = sz[lc[p]] + sz[rc[p]] + cnt[p];
	sd[p] = sd[lc[p]] + sd[rc[p]] + (cnt[p] != 0);
}
bool IsUnbalanced(int p)
{
	return cnt[p] && (ALPHA * s[p] <= max(s[lc[p]] , s[rc[p]]) || sd[p] <= ALPHA * s[p]);
}
void Travel(int p)
{
	if(!p)return ;
	Travel(lc[p]);
	if(cnt[p])a[++tc] = p;
	Travel(rc[p]);
}
void Build(int l , int r , int &p)
{
	if(l > r)return ;
	int mid = (l + r) >> 1;
	p = a[mid] , lc[p] = rc[p] = 0 , s[p] = sd[p] = 1 , sz[p] = cnt[p];
	if(l == r)return ;
	Build(l , mid - 1 , lc[p]);
	Build(mid + 1 , r , rc[p]);
	Pushup(p);
}
void Rebuild(int& p)
{
	tc = 0;
	Travel(p);
	Build(1 , tc , p);
}
void Insert(int &p , int v)
{
	if(!p)
	{
		p = New(v);
		return ;
	}
	if(v < val[p])Insert(lc[p] , v);
	else if(v == val[p])cnt[p]++;
	else Insert(rc[p] , v);
	Pushup(p);
	if(IsUnbalanced(p))sgt = &p;
}
void Delete(int &p , int v)
{
	if(!p)return ;
	if(v < val[p])Delete(lc[p] , v);
	else if(v == val[p])cnt[p]--;
	else Delete(rc[p] , v);
	Pushup(p);
	if(IsUnbalanced(p))sgt = &p;
}
int Rank(int p , int x)
{
	if(!p)return 0;
	if(x < val[p])return Rank(lc[p], x);
	if(x == val[p])return sz[lc[p]];
	if(x > val[p])return sz[lc[p]] + cnt[p] + Rank(rc[p] , x); 
}
int Kth(int p , int k)
{
	if(!p)return 0x7fffffff;
	if(sz[lc[p]] >= k)return Kth(lc[p] , k);
	else if(sz[lc[p]] + cnt[p] >= k)return val[p];
	else return Kth(rc[p] , k - cnt[p] - sz[lc[p]]);
}
int Pre(int x)
{
	return Kth(rt , Rank(rt , x));	
}
int Nxt(int x)
{
	return Kth(rt , Rank(rt , x + 1) + 1);
}
int main()
{
	int n = Read() , m = Read() , lst = 0 , ans = 0;
	for(int i = 1 ; i <= n ; i++)sgt = &zero , Insert(rt , Read()) , Rebuild(*sgt);
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read() , x = Read() ^ lst;
		if(op == 1)sgt = &zero , Insert(rt , x) , Rebuild(*sgt);
		if(op == 2)sgt = &zero , Delete(rt , x) , Rebuild(*sgt);
		if(op == 3)ans ^= (lst = Rank(rt , x) + 1);
		if(op == 4)ans ^= (lst = Kth(rt , x));
		if(op == 5)ans ^= (lst = Pre(x));
		if(op == 6)ans ^= (lst = Nxt(x));
	}
	printf("%d" , ans);
	return 0;
}
