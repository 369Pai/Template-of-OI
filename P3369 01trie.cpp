#include<iostream>
#include<cstdio>
using namespace std;
const int SZ = 32 * (1e5 + 5);
int trie[SZ][2] , cnt[SZ] , tot = 1;
bool ed[SZ];
void Insert(int x , int v)
{
	int p = 1;
	for(int i = 31 ; i >= 0 ; i--)
	{
		int ch = x & (1 << i);
		if(trie[p][ch] == 0)trie[p][ch] = ++tot;
		p = trie[p][ch];
		cnt[p] += v;
	}
	if(cnt[p] > 0)ed[p] = 1;
}
int Rank(int x)
{
	int p = 1 , ans = 0;
	for(int i = 31 ; i >= 0 ; i--)
	{
		int ch = x & (1 << i);
		if(ch)ans += trie[p][0];
		if(trie[p][ch] == 0)break;
		p = trie[p][ch];
	}
	return ans;
}
int main()
{
	int n;
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		int op , x;
		scanf("%d%d" , &op , &x);
		if(op == 1)Insert(x , 1);
		if(op == 2)Insert(x , -1);
		if(op == 3)printf("%d\n" , Rank(x));
		if(op == 4)
		{
			
		}
		if(op == 5)
		{
			
		}
		if(op == 6)
		{
			
		}
	}
	return 0;
}
