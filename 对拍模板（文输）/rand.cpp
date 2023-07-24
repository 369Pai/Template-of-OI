#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
ll Random(ll l , ll r){return ll(rnd() % (r - l + 1)) + l;}
int main()
{
	freopen(".in" , "w" , stdout);
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	return 0; 
}