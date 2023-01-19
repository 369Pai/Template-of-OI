#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e4 + 5;
int fa[N * 3];
int Find(int x)
{
	if(x == fa[x])return x;
	return fa[x] = Find(fa[x]);
}
int main()
{
	int n , k , ans = 0;
	scanf("%d%d" , &n , &k);
	for(int i = 1 ; i <= n * 3 ; i++)
		fa[i] = i;
	for(int i = 1 ; i <= k ; i++)
	{
		int op , x , y;
		scanf("%d%d%d" , &op , &x , &y);
		if(x > n || y > n)
		{
			ans++;
			continue;
		}
		if(op == 1)
		{
			if(Find(x) == Find(y + n) || Find(x) == Find(y + n * 2))
			{
				ans++;
				continue;
			}
			fa[Find(y)] = Find(x);
			fa[Find(y + n)] = Find(x + n);
			fa[Find(y + n * 2)] = Find(x + n * 2);
		}
		else
		{
			if(Find(x) == Find(y) || Find(x) == Find(y + n))
			{
				ans++;
				continue;
			}
			fa[Find(y)] = Find(x + n);
			fa[Find(y + n)] = Find(x + n * 2);
			fa[Find(y + n * 2)] = Find(x);
		}
	}
	printf("%d" , ans);
	return 0;
}
