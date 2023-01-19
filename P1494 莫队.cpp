#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 5e4 + 5 , T = 224 + 5;
struct Q{int l , r , id;}a[N];
bool Cmp1(Q x , Q y){return x.l < y.l;}
bool Cmp2(Q x , Q y){return x.r < y.r;}
bool Cmp3(Q x , Q y){return x.r > y.r;}
int n , m , k , t , sz , v[N] , L[T] , R[T] , cnt[N];
long long res[N];
int main()
{
	scanf("%d%d%d" , &n , &m , &k);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d" , &v[i]);
	for(int i = 1 ; i <= m ; i++)
	{
		scanf("%d%d" , &a[i].l , &a[i].r);
		a[i].id = i;
	}
	sort(a + 1 , a + m + 1 , Cmp1);
	sz = sqrt(n) , t = (n + sz - 1) / sz;
	for(int i = 1 ; i <= t ; i++)
	{
		L[i] = R[i - 1] + 1 , R[i] = min(n , i * sz);
		sort(a + L[i] , a + R[i] + 1 , (i & 1 ? Cmp2 : Cmp3));
	}
	long long ans = 0;
	for(int i = a[1].l ; i <= a[1].r ; i++)
		ans += cnt[v[i]] * 2 + 1 , cnt[v[i]]++;
	res[a[1].id] = ans;
	for(int i = 2 ; i <= n ; i++)
	{
		for(int j = a[i - 1].l ; j < a[i].l ; j++)ans -= --cnt[v[j]] * 2 + 1;
		for(int j = a[i].r ; j > a[i - 1].r ; j--)ans += cnt[v[j]]++ * 2 + 1;		
		for(int j = a[i - 1].r ; j > a[i].r ; j--)ans -= --cnt[v[j]] * 2 + 1;		
		for(int j = a[i].l ; j < a[i - 1].l ; j++)ans += cnt[v[j]]++ * 2 + 1;
		res[a[i].id] = ans;
	}
	for(int i = 1 ; i <= m ; i++)
		printf("%lld\n" , res[i]);
	return 0;
}
