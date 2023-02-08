#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5 , A = 1e5;
int fac[N] = {1} , inv[N] = {1};
int Qpow(int x , int p , int mod)
{
	int res = 1;
	for(; p > 0 ; p >>= 1 , x = 1ll * x * x % mod)
		if(p & 1)res = 1ll * res * x % mod;
	return res;
}
void Init(int p)
{
	for(int i = 1 ; i <= p ; i++)
		fac[i] = 1ll * fac[i - 1] * i % p;
	inv[p - 1] = Qpow(fac[p - 1] , p - 2 , p);
	for(int i = p - 2 ; i >= 1 ; i--)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % p;
}
int C(int m , int n , int p){return n < m ? 0 : 1ll * fac[n] * inv[n - m] % p * inv[m] % p;}
int Lucas(int m , int n , int p){return m == 0 ? 1 : 1ll * Lucas(m / p , n / p , p) * C(m % p , n % p , p) % p;}
int main()
{
	int T; scanf("%d" , &T);
	while(T--)
	{
		int n , m , p;
		scanf("%d%d%d" , &n , &m , &p);
		Init(p);
		printf("%d\n"  , Lucas(n , n + m , p));
	}
	return 0;
}
