#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e4 + 5;
int fa[N] , v[N];
int Find(int x)
{
	if(x == fa[x])return x;
	int rt = Find(fa[x]);
	v[x] = (v[x] + v[fa[x]]) % 3;
	return fa[x] = rt;
}
int main()
{
	int n , k , ans = 0;
	scanf("%d%d" , &n , &k);
	for(int i = 1 ; i <= n ; i++)
		fa[i] = i , v[i] = 0;
	for(int i = 1 ; i <= k ; i++)
	{
		int op , x , y;
		scanf("%d%d%d" , &op , &x , &y);
		if(x > n || y > n)
		{
			ans++;
			continue;
		}
		int fx = Find(x) , fy = Find(y);
		if(fx == fy)
		{
			if(op == 1)
			{
				if(v[x] != v[y])ans++;
			}
			else
			{
				if(v[x] != (v[y] + 1) % 3)ans++;
			}
		}
		else
		{
			if(op == 1)
			{
				fa[fx] = fy;
				v[fx] = (v[y] - v[x] + 3) % 3;
			}
			else
			{
				fa[fx] = fy;
				v[fx] = (1 + v[y] - v[x] + 3) % 3;				
			}
		}
	}
	printf("%d" , ans);
	return 0;
}
