#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int N = 1e5 + 5 , T = 16; 
int n , m , a[N] , f[T + 1][N];
inline int Read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void STPrework()
{
	for(int i = 1 ; i <= n ; i++)f[0][i] = a[i];
	for(int i = 1 ; i <= T ; i++)
		for(int j = 1 ; j + (1 << (i - 1)) <= n ; j++)
			f[i][j] = max(f[i - 1][j] , f[i - 1][j + (1 << (i - 1))]);	
}
int STQuery(int l , int r)
{
	int k = log2(r - l + 1);
	return max(f[k][l] , f[k][r - (1 << k) + 1]);
}
int main()
{
	n = Read() , m = Read();
	for(int i = 1 ; i <= n ; i++)
		a[i] = Read();
	STPrework();
	for(int i = 1 ; i <= m ; i++)
	{
		int l = Read() , r = Read();
		printf("%d\n" , STQuery(l , r));
	}
	return 0;
}
