#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e5 + 5;
int n , m;
int a[N] , c[N];
void Add(int x , int v)
{
	for(int i = x ; i <= n ; i += i & -i)
		c[i] += v;
}
int Query(int x)
{
	if(x <= 0)return 0;
	int sum = 0;
	for(int i = x ; i ; i -= i & -i)
		sum += c[i];
	return sum;
}
inline int Read()
{
	int x = 0 , f = 1; char ch = getchar();
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
		a[i] = Read();
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read() , x = Read();
		if(op == 1)
		{
			int y = Read() , k = Read();
			Add(x , k);
			Add(y + 1 , -k);
		}
		else printf("%d\n" , Query(x) + a[x]);
	}
	return 0;
}
