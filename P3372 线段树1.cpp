#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll a[N] , tr[N * 4] , lazy[N * 4];
void Pushup(int p){tr[p] = tr[p * 2] + tr[p * 2 + 1];}
void Pushdown(int l , int r , int p)
{
	if(lazy[p])
	{
		int mid = (l + r) >> 1;
		tr[p * 2] += (mid - l + 1) * lazy[p];
		lazy[p * 2] += lazy[p];
		tr[p * 2 + 1] += (r - mid) * lazy[p];
		lazy[p * 2 + 1] += lazy[p];
		lazy[p] = 0;
	}
}
void Build(int l , int r , int p)
{
	if(l == r)
	{
		tr[p] = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	Build(l , mid , p * 2);
	Build(mid + 1 , r , p * 2 + 1);
	Pushup(p);
}
void Update(int l , int r , int p , int s , int e , ll v)
{
	if(s <= l && r <= e)
	{
		tr[p] += (r - l + 1) * v;
		lazy[p] += v;
		return ;
	}
	Pushdown(l , r , p);
	int mid = (l + r) >> 1;
	if(s <= mid)Update(l , mid , p * 2 , s , e , v);
	if(mid < e)Update(mid + 1 , r , p * 2 + 1 , s , e , v);
	Pushup(p);
}
ll Query(int l , int r , int p , int s , int e)
{
	if(s <= l && r <= e)
	{
		return tr[p];
	}
	Pushdown(l , r , p);
	int mid = (l + r) >> 1; ll ans = 0;
	if(s <= mid)ans += Query(l , mid , p * 2 , s , e);
	if(mid < e)ans += Query(mid + 1 , r , p * 2 + 1 , s , e);
	return ans;
}
int main()
{
	int n , m;
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i++)
		scanf("%lld" , &a[i]);
	Build(1 , n , 1);
	for(int i = 1 ; i <= m ; i++)
	{
		int op , x , y; ll v;
		scanf("%d%d%d" , &op , &x , &y);
		if(op == 1)
		{
			scanf("%lld" , &v);
			Update(1 , n , 1 , x , y , v);
		}
		if(op == 2)printf("%lld\n" , Query(1 , n , 1 , x , y));
	}
	return 0;
}
