#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937_64 rnd(time(NULL));
int m = 12, p[20] = {0 , 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37};
ll Qpow(ll x , ll p , ll mod)
{
	ll res = 1;
	for(; p > 0 ; p >>= 1 , x = (__int128)x * x % mod)
		if(p & 1)res = (__int128)res * x % mod;
	return res;
}
bool MillerRabbin(ll n)
{
	if(n % 2 == 0 || n < 3)return n == 2;
	ll u = n - 1 , t = 0;
	while(~u & 1)u >>= 1 , t++;
	for(int i = 1 ; i <= 12 ; i++)
	{
		ll v = Qpow(p[i] , u , n);
		if(v == 1 || v == n - 1 || v == 0)continue;
		for(int j = 1 ; j <= t ; j++)
		{
			v = (__int128)v * v % n;
			if(v == n - 1 && j != t){v = 1; break;}
			if(v == 1)return 0;
		}
		if(v != 1)return 0;
	}
	return 1;
}
ll PollardRho(ll n)
{
	if(n == 4)return 2;
	if(MillerRabbin(n))return n;
	while(1)
	{
		ll c = rnd() % (n - 1) + 1;
		auto F = [&](ll x){return ((__int128)x * x + c) % n;};
		ll x = 0 , y = 0 , p = 1 , q = 0;
		do
		{
			for(int i = 1 ; i < (1 << 7) ; i++)
			{
				x = F(x) , y = F(F(y));
				if(x == y || (q = (__int128)p * abs(y - x) % n) == 0)break;
				p = q;
			}		
			ll d = __gcd(p , n);
			if(d > 1)return d;
		}while(x != y);
	}
}
ll MaxPrimeFactor(ll n)
{
	ll p = PollardRho(n);
	if(p == n)return n;
	while(n > p && n % p == 0)n /= p;
	return max(MaxPrimeFactor(n) , MaxPrimeFactor(p));
}
int main()
{
	int T; scanf("%d" , &T);
	while(T--)
	{
		ll n; scanf("%lld" , &n);
		ll mp = MaxPrimeFactor(n);
		if(mp == n)puts("Prime");
		else printf("%lld\n" , mp);
	}
	return 0;
}
