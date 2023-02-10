#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int , int> PII;
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
__gnu_pbds::tree<PII , null_type , less<PII> , rb_tree_tag , tree_order_statistics_node_update>tr;
int main()
{
	int n = Read() , m = Read() , last = 0 , ans = 0;
	for(int i = 1 ; i <= n ; i++)tr.insert(make_pair(Read() , i));
	for(int i = 1 ; i <= m ; i++)
	{
		int op = Read(), x = Read() ^ last;
		if(op == 1)tr.insert(make_pair(x , i + n));
		if(op == 2)tr.erase(tr.lower_bound(make_pair(x , 0)));
		if(op == 3)last = tr.order_of_key(make_pair(x , 0)) + 1;
		if(op == 4)last = tr.find_by_order(x - 1)->first;
		if(op == 5)last = prev(tr.lower_bound(make_pair(x , 0)))->first;
		if(op == 6)last = tr.lower_bound(make_pair(x , n + m))->first;
		if(op >= 3)ans ^= last;
	}
	printf("%d" , ans);
	return 0;
}
