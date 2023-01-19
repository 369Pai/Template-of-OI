#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
void Write(ll x)
{
	if(!x)return ;
	ll xx = x / 10;
	Write(xx);
	putchar(x - xx * 10 + '0');
}
ll Exgcd(ll a , ll b , ll&x , ll &y)
{
	if(!b)return x = 1 , y = 0 , a;
	ll d = Exgcd(b , a % b , y , x);
	y -= a / b * x;
	return d;
}
ll Abs(const ll& x){return x > 0 ? x : -x;}
int main()
{
	int n = Read(); ll a1 = Read() , x = Read() % a1; 
	for(int i = 2 ; i <= n ; i++)
	{
		ll a2 = Read() , b2 = Read() , c = x - b2 , y1 , y2 , d = Exgcd(-a1 , a2 , y1 , y2);
		if(c % d){puts("-1"); return 0;}
		y1 = c / d * y1 , y2 = c / d * y2;
		ll lcm = Abs(a1 / d * a2);
		x = ((x + a1 * y1) % lcm + lcm) % lcm;
		a1 = lcm;
//		Write(x) , putchar(' ') , Write(a1) , putchar('\n');		
	}
	Write(x);
	return 0;
}
