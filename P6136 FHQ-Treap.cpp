#include<iostream>
#include<cstdio>
#include<random>
using namespace std;
typedef long long ll;
const int N = 1.1e6 + 5;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
mt19937 rnd(time(NULL));
int rt , tot , lc[N] , rc[N] , val[N] , dat[N] , cnt[N] , sz[N];
int New(int v)
{
	val[++tot] = v , dat[tot] = rnd();
	cnt[tot] = sz[tot] = 1;	
	return tot;
}
void Pushup(int p){sz[p] = sz[lc[p]] + sz[rc[p]] + cnt[p];}
void Split(int p , int &l , int &r , int v)
{
	if(!p)
	{
		l = r = 0;
		return;
	}
	if(val[p] <= v)
	{
		l = p;
		Split(rc[p] , rc[p] , r , v);
	}
	else
	{
		r = p;
		Split(lc[p] , l , lc[p] , v);
	}
	Pushup(p);
}
int Merge(int l , int r)
{
	if(!l || !r)return l + r;
	int p = 0;
	if(dat[l] > dat[r])
	{
		p = l;
		rc[p] = Merge(rc[p] , r);
	}
	else
	{
		p = r;
		lc[p] = Merge(l , lc[p]);
	}
	Pushup(p);
	return p;
}
void Insert(int x)
{
	int l = 0 , r = 0 , ll = 0 , lr = 0;
	Split(rt , l , r , x);
	Split(l , ll , lr , x - 1);
	if(lr)cnt[lr]++ , sz[lr]++;
	else lr = New(x);
	l = Merge(ll , lr);
	rt = Merge(l , r);
}
void Delete(int x)
{
	int l = 0 , r = 0 , ll = 0 , lr = 0;
	Split(rt , l , r , x);
	Split(l , ll , lr , x - 1);
	if(lr)cnt[lr]-- , sz[lr]--;
	if(!cnt[lr])lr = 0;
	l = Merge(ll , lr);
	rt = Merge(l , r);	
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
	for(int i = 1 ; i <= n ; i++)Insert(Read());
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read() , x = Read() ^ lst;
		if(op == 1)Insert(x);
		if(op == 2)Delete(x);
		if(op == 3)ans ^= (lst = Rank(rt , x) + 1);
		if(op == 4)ans ^= (lst = Kth(rt , x));
		if(op == 5)ans ^= (lst = Pre(x));
		if(op == 6)ans ^= (lst = Nxt(x));
	}
	printf("%d" , ans);
	return 0;
}
