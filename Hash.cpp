#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
struct HashTable
{
	static const int M = 13075 , P = 13003; // P is close to M and P is between N^1.1 to N^1.7
	struct Node{ll key , v; int nxt;}e[M];
	int tot , head[P];
	void Add(int u , ll k , ll v){e[++tot] = {k , v , head[u]} , head[u] = tot;}
	ll& operator[](ll x)
	{
		for(int i = head[x % P] ; i ; i = e[i].nxt)
			if(e[i].key == x)return e[i].v;
		Add(x % P , x , 0);
		return e[tot].v;
	}
	ll at(ll x)
	{
		for(int i = head[x % P] ; i ; i = e[i].nxt)
			if(e[i].key == x)return e[i].v;
		return 0;
	}
}c;
int main()
{
	ll n , x , l , r; cin >> n >> l >> r;
	for(int i = 1 ; i <= n ; i++)
		cin >> x ,  c[x]++;
	for(ll i = l ; i <= r ; i++)
		if(c.at(i))cout << i << ',' << c[i] << endl;
	return 0;
}
