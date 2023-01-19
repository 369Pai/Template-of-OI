#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e3;
int a[N + 5][N + 5];
inline int At(int x , int y)
{
	if(x < 0 || y < 0)return 0;
	else return a[x][y];
}
int main()
{
	int n , m , ans = 0;
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i++)
	{
		int x , y , v;
		scanf("%d%d%d" , &x , &y , &v);
		a[x][y] += v;
	}
	for(int i = 0 ; i <= N ; i++)
		for(int j = 0 ; j <= N ; j++)
		{
			a[i][j] += At(i - 1 , j) + At(i , j - 1) - At(i - 1 , j - 1);
			ans = max(ans , a[i][j] - At(i - m , j) - At(i , j - m) + At(i - m , j - m));
		}
	printf("%d" , ans);
	return 0;
}

