#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int pr[15] = {0 , 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37};//OEIS,<2^64
ll Qpow(ll x , ll p , ll mod)
{
	ll res = 1;
	for(; p > 0 ; x = (__int128)x * x % mod , p >>= 1)
		if(p & 1)res = (__int128)res * x % mod;
	return res;
}
bool MillerRabbin(ll n)
{
	if(n < 3 || n % 2 == 0)return n == 2;//特判
	ll u = n - 1 , t = 0;
	while(~u & 1)u >>= 1 , t++;
	for(int i = 1 ; i <= 12 ; i++)
	{
		ll v = Qpow(pr[i] , u , n);
		if(v == 1 || v == n - 1 || v == 0)continue;//all 1
		for(int j = 1 ; j <= t ; j++)
		{
			v = (__int128)v * v % n;
			if(v == n - 1 && j != t){v = 1; break;}//n-1(not last),1,1,1...
			if(v == 1)return 0;//1 before n-1,false like 25^2 mod 135 = 85 but 26^2 % 135 = 1
		}
		if(v != 1)return 0;//Fermat
	}
	return 1;
}
int main()
{
	int T; scanf("%d" , &T);
	while(T--)
	{
		ll n; scanf("%lld" , &n);
		puts((MillerRabbin(n) ? "YES" : "NO"));
	}
	return 0;
}
