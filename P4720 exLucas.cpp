#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
const int N = 20 , PK = 1e6 + 5;
ll n , m; int a[N] , p , tot = 0 , pr[N] , pk[N] , pre[N][PK] , b[N];
int Qpow(int x , int p , int mod)
{
	int res = 1;
	for(; p > 0 ; p >>= 1 , x = (ll)x * x % mod)
		if(p & 1)res = (ll)res * x % mod;
	return res;
}
int CRT()
{
	int ans = 0;
	for(int i = 1 ; i <= tot ; i++)
	{
		int t = p / pk[i] , phi = pk[i] / pr[i] * (pr[i] - 1);
		ans = (ans + (ll)t * Qpow(t , phi - 1 , p) % p * b[i]) % p;
	}
	return ans;
}
int Fac(ll n , int id)//log^2 n?
{
	if(!n)return 1;
	int ans = pre[id][pk[id] - 1];
	ans = Qpow(ans , n / pk[id] , pk[id]);
	ans = (ll)ans * pre[id][n % pk[id]] % pk[id];
	return (ll)ans * Fac(n / pr[id] , id) % pk[id];
}
int ExLucas(ll n , ll m)
{
	if(n > m)return 0;
	for(int i = 1 ; i <= tot ; i++)
	{
		int cntp = 0 , phi = pk[i] / pr[i] * (pr[i] - 1);
		for(ll j = m ; j ; j /= pr[i])cntp += j / pr[i];
		for(ll j = n ; j ; j /= pr[i])cntp -= j / pr[i];
		for(ll j = m - n ; j ; j /= pr[i])cntp -= j / pr[i];
		b[i] = (ll)Qpow(pr[i] , cntp , pk[i]) * Fac(m , i) % pk[i] 
			* Qpow(Fac(n , i) , phi - 1 , pk[i]) % pk[i] * 
			Qpow(Fac(m - n , i) , phi - 1 , pk[i]) % pk[i];
	}
	return CRT();
}
void Init()
{
	int t = p;
	for(int i = 2 ; i * i <= t ; i++)
	{
		if(t % i == 0)
		{
			tot++ , pr[tot] = i , pk[tot] = 1;
			while(t % i == 0)pk[tot] *= i , t /= i;
		}		
	}
	if(t > 1)tot++ , pr[tot] = pk[tot] = t;
	for(int i = 1 ; i <= tot ; i++)
	{
		pre[i][0] = 1;
		for(int j = 1 ; j < pk[i] ; j++)
		{
			pre[i][j] = pre[i][j - 1];
			if(j % pr[i])pre[i][j] = (ll)pre[i][j] * j % pk[i];
		}		
	}
}
int main()
{
	n = Read() , m = Read() , p = Read();
	Init();
	printf("%d" , ExLucas(m , n));
	return 0;
}
