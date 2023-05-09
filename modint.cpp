#include<bits/stdc++.h>
using namespace std;
template<int MOD>
struct ModInt
{
	typedef ModInt mint;
	typedef long long ll;
	int v;
	ModInt(ll x = 0)
	{
		if(x <= -MOD || x >= MOD)x %= MOD;
		if(x < 0)x += MOD;
		v = x;
	}
	mint operator + (const mint &b){return ModInt(v + b.v);}
	mint operator - (const mint &b){return ModInt(v - b.v);}
	mint operator * (const mint &b){return ModInt((ll)v * b.v);}
	mint operator ^ (ll p)
	{
		mint x = *this , res = 1;
		for(; p ; p >>= 1 , x = x * x)
			if(p & 1)res = res * x;
		return res;
	}
};
int main()
{
	return 0;
}