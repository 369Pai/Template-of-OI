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
int n , a[15] , b[15];
ll A = 1 , ans = 0;
ll Exgcd(ll a , ll b , ll &x , ll &y)
{
	if(!b)return x = 1 , y = 0 , a;
	ll d = Exgcd(b , a % b , y , x);
	y -= a / b * x;
	return d;
}
int main()
{
	n = Read();
	for(int i = 1 ; i <= n ; i++)
	{
		a[i] = Read() , b[i] = Read();
		A = A * a[i];
	}
	for(int i = 1 ; i <= n ; i++)
	{
		ll m = A / a[i] , x , y;
		Exgcd(m , a[i] , x , y);
		ans = ((ans + b[i] * x * m) % A + A) % A;
	}
	printf("%lld" , ans);
	return 0;
}
