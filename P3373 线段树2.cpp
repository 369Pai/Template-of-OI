#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll n , m , mod , a[N] , tr[N * 4] , mul[N * 4] , add[N * 4];
void Pushup(int p){tr[p] = (tr[p * 2] + tr[p * 2 + 1]) % mod;}
void Pushdown(int l , int r , int p)
{
	int mid = (l + r) >> 1;
	if(mul[p] != 1)
	{
		tr[p * 2] = (tr[p * 2] * mul[p]) % mod;
		add[p * 2] = (add[p * 2] * mul[p]) % mod;
		mul[p * 2] = (mul[p * 2] * mul[p]) % mod;
		tr[p * 2 + 1] = (tr[p * 2 + 1] * mul[p]) % mod;
		add[p * 2 + 1] = (add[p * 2 + 1] * mul[p]) % mod;
		mul[p * 2 + 1] = (mul[p * 2 + 1] * mul[p]) % mod;		
		mul[p] = 1;		
	}
	if(add[p])
	{
		tr[p * 2] = (tr[p * 2] + (mid - l + 1) * add[p]) % mod;
		add[p * 2] = (add[p * 2] + add[p]) % mod;
		tr[p * 2 + 1] = (tr[p * 2 + 1] + (r - mid) * add[p]) % mod;
		add[p * 2 + 1] = (add[p * 2 + 1] + add[p]) % mod;
		add[p] = 0;
	}
}
void Build(int l , int r , int p)
{
	add[p] = 0 , mul[p] = 1;
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
void Update1(int l , int r , int p , int s , int e , ll v)
{
	if(s <= l && r <= e)
	{
		tr[p] = (tr[p] * v) % mod;
		mul[p] = (mul[p] * v) % mod;
		add[p] = (add[p] * v) % mod;
		return ;
	}
	Pushdown(l , r , p);
	int mid = (l + r) >> 1;
	if(s <= mid)Update1(l , mid , p * 2 , s , e , v);
	if(mid < e)Update1(mid + 1 , r , p * 2 + 1 , s , e , v);
	Pushup(p);
}
void Update2(int l , int r , int p , int s , int e , ll v)
{
	if(s <= l && r <= e)
	{
		tr[p] = (tr[p] + (r - l + 1) * v) % mod;
		add[p] = (add[p] + v) % mod;
		return ;
	}
	Pushdown(l , r , p);
	int mid = (l + r) >> 1;
	if(s <= mid)Update2(l , mid , p * 2 , s , e , v);
	if(mid < e)Update2(mid + 1 , r , p * 2 + 1 , s , e , v);
	Pushup(p);
}
ll Query(int l , int r , int p , int s , int e)
{
	if(s <= l && r <= e)
	{
		return tr[p] % mod;
	}
	Pushdown(l , r , p);
	int mid = (l + r) >> 1; ll ans = 0;
	if(s <= mid)ans = (ans + Query(l , mid , p * 2 , s , e)) % mod;
	if(mid < e)ans = (ans + Query(mid + 1 , r , p * 2 + 1 , s , e)) % mod;
	return ans % mod;
}
int main()
{
	scanf("%lld%lld%lld" , &n , &m , &mod);
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
			Update1(1 , n , 1 , x , y , v);
		}
		if(op == 2)
		{
			scanf("%lld" , &v);
			Update2(1 , n , 1 , x , y , v);
		}
		if(op == 3)printf("%lld\n" , Query(1 , n , 1 , x , y) % mod);
	}
	return 0;
}
