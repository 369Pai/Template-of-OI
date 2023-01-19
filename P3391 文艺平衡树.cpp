#include<iostream>
#include<cstdio>
#include<random>
using namespace std;
const int N = 1e5 + 5;
mt19937 rnd(time(NULL));
int n , m;
int rt , tot , val[N] , dat[N] , lc[N] , rc[N] , sz[N] , tag[N];
int New(int x)
{
	val[++tot] = x , dat[tot] = rnd();
	sz[tot] = 1;
	return tot;
}
void Pushup(int p){sz[p] = sz[lc[p]] + sz[rc[p]] + 1;}
void Pushdown(int p)
{
	if(tag[p])
	{
		;//cout << "TAG:" << p << endl;
		swap(lc[p] , rc[p]);
		tag[lc[p]] ^= 1;
		tag[rc[p]] ^= 1;
		tag[p] = 0;
	}
}
void Split(int p , int &l , int &r , int siz)
{
	if(!p)
	{
		l = r = 0;
		return ;
	}
	;//cout << "SPL:" << p << ' ' << lc[p] << ' ' << rc[p] << ',' << siz << ';'; 
	Pushdown(p);
	if(siz <= sz[lc[p]])
	{
		;//cout << p << ' ' << rc[p] << " lc" << lc[p] << '\n';
		r = p;
		Split(lc[p] , l , lc[p] , siz);
	}
	else
	{
		;//cout << p << ' ' << lc[p] << ' ' << "rc" << rc[p] << '\n';
		l = p;
		Split(rc[p] , rc[p] , r , siz - sz[lc[p]] - 1);
	}
	Pushup(p);
}
int Merge(int l , int r)
{
	if(!l || !r)return l + r;
	int p;
	if(dat[l] <= dat[r])
	{
		p = l;
		Pushdown(p);
		rc[p] = Merge(rc[p] , r);
	}
	else
	{
		p = r;
		Pushdown(p);
		lc[p] = Merge(l , lc[p]);
	}
	Pushup(p);
	return p;
}
void Reverse(int p , int q)
{
	int l , r , rl , rr;
	Split(rt , l , r , p - 1);
	Split(r , rl , rr , q - p + 1);
	;//cout << "R:" << l << ' ' << r << ' ' << rl << ' ' << rr << endl;
	tag[rl] ^= 1;
	r = Merge(rl , rr);
	rt = Merge(l , r);
}
void Dfs(int p)
{
	if(!p)return ;
	Pushdown(p);
	;//cout << p << ':' << lc[p] << ' ' << rc[p] << ',' << val[p] << endl;
	Dfs(lc[p]);
	printf("%d " , val[p]);
	Dfs(rc[p]);
}
int main()
{
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i++)
		rt = Merge(rt , New(i));
//	Dfs(rt);
	for(int i = 1 ; i <= m ; i++)
	{
		int l , r;
		scanf("%d%d" , &l , &r);
		Reverse(l , r);
//		Dfs(rt);
	}
	Dfs(rt);
	return 0;
}
