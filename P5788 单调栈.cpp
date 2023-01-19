#include<iostream>
#include<cstdio>
using namespace std;
const int N = 3e6 + 5;
int a[N] , f[N] , stk[N] , top;
inline int Read()
{
	int x = 0; char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x;
}
int main()
{
	int n = Read();
	for(int i = 1 ; i <= n ; i++)
	{
		a[i] = Read();
		while(top && a[stk[top]] < a[i])
		{
			f[stk[top]] = i;
			top--;
		}
		stk[++top] = i;
	}
	for(int i = 1 ; i <= n ; i++)
		printf("%d " , f[i]);
	return 0;
}
