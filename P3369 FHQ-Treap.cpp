#include<iostream>
#include<cstdio>
#include<random>
using namespace std;
const int N = 1e5 + 5;
mt19937 rnd(time(NULL));
int rt , tot , lc[N] , rc[N] , val[N] , dat[N] , cnt[N] , sz[N];
int New(int v)
{
	val[++tot] = v , dat[tot] = rnd();
	cnt[tot] = sz[tot] = 1;	
	;//cout << "NODE:" << tot << ' ' << val[tot] << ' ' << dat[tot] << endl;	
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
	;//cout << "SPL:" << p << ' ' << l << ' ' << r << endl;
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
	;//cout << "MER:" << l << ' ' << r << ' ' << p << endl;
	Pushup(p);
	return p;
}
void Insert(int x)
{
	int l = 0 , r = 0 , ll = 0 , lr = 0;
	Split(rt , l , r , x);
	Split(l , ll , lr , x - 1);
	;//cout << "INS:" << l << ' ' << r << ' ' << ll << ' ' << lr << endl;
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
	;//cout << "DEL:" << l << ' ' << r << ' ' << ll << ' ' << lr << endl;
	if(lr)cnt[lr]-- , sz[lr]--;
	if(!cnt[lr])lr = 0;
	l = Merge(ll , lr);
	rt = Merge(l , r);	
}
void Dfs(int p)
{
	if(!p)return ;
	;//cout << p << ':' << lc[p] << ' ' << rc[p] << ' ' << sz[p] << endl;
	Dfs(lc[p]);
	//cout << val[p] << ' ';
	Dfs(rc[p]);
}
int Rank(int p , int x)
{
	;//if(x == 493598)cout << p << ' ' << val[p] << endl;
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
	;//cout << "RK:" << Rank(rt , x) << endl;
	return Kth(rt , Rank(rt , x));	
}
int Nxt(int x)
{
	;//cout << "RK:" << Rank(rt , x + 1) << endl;
	return Kth(rt , Rank(rt , x + 1) + 1);
}
int main()
{
	int n;
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		int op , x;
		scanf("%d%d" , &op , &x);
		if(op == 1)Insert(x);
		if(op == 2)Delete(x);
		if(op == 3)printf("%d\n" , Rank(rt , x) + 1);
		if(op == 4)printf("%d\n" , Kth(rt , x));
		if(op == 5)printf("%d\n" , Pre(x));
		if(op == 6)printf("%d\n" , Nxt(x));
		//Dfs(rt);
		;//cout << endl;
	}
	return 0;
}
