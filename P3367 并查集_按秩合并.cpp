#include<iostream>
#include<cstdio>
using namespace std;
const int N = 1e4 + 5;
int fa[N] , sz[N];
int Find(int x){return x == fa[x] ? x : Find(fa[x]);}
int main()
{
	int n , m;
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i++)
		fa[i] = i , sz[i] = 1;
	for(int i = 1 ; i <= m ; i++)
	{
		int op , x , y;
		scanf("%d%d%d" , &op , &x , &y);
		int fx = Find(x) , fy = Find(y);
		if(op == 1)
		{
			if(fx == fy)continue;
			if(sz[fx] < sz[fy])
			{
				fa[fx] = fy;
				sz[fy] += sz[fx];
			}	
			else
			{
				fa[fy] = fx;
				sz[fx] += sz[fy];
			}
		}
		if(op == 2)puts(fx == fy ? "Y" : "N");
	}
	return 0;
}
