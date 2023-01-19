#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
int n , m;
ll c[N];
void Add(int x , ll v)
{
	for(int i = x ; i <= n ; i += i & -i)
		c[i] += v;
}
ll Query(int x)
{
	if(x <= 0)return 0;
	ll sum = 0;
	for(int i = x ; i ; i -= i & -i)
		sum += c[i];
	return sum;
}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
int main()
{
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i++)
		Add(i , Read());
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read() , x = Read(); ll y = Read();
		if(op == 1)Add(x , y);
		else printf("%lld\n" , Query(y) - Query(x - 1));
	}
	return 0;
}
