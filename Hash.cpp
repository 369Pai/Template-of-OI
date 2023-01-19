#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int NN = 3e7 + 5 , MOD = 14999461;
struct Hash
{
	struct Node
	{
		int nxt;
		ll key , v;
	}a[NN];
	int tot , head[MOD];
	void Add(ll key , ll v)
	{
		a[++tot] = {head[key % MOD] , key , v};
		head[key % MOD] = tot;
	}
	ll& operator [](ll key)
	{
		for(int i = head[key % MOD] ; i ; i = a[i].nxt)
		{
			if(a[i].key == key)
				return a[i].v;
		}
		Add(key , 0);
		return a[tot].v;
	}
	ll Find(ll key)
	{
		for(int i = head[key % MOD] ; i ; i = a[i].nxt)
		{
			if(a[i].key == key)
				return a[i].v;
		}
		return 0;
	}
}c;
int main()
{
	int n;
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		int x;
		scanf("%d" , &x);
		c[x]++;
	}
	for(int i = 1e9 ; i <= n  + 1e9; i++)
		cout << c[i] << ' ';
	return 0;
}
