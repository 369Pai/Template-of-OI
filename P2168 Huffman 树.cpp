#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<ll , int> PI;
const int N = 1e5 + 5;
priority_queue<PI , vector<PI> , greater<PI> >pq;
int main()
{
	int n , k; ll ans = 0;
	scanf("%d%d" , &n , &k);
	for(int i = 1 ; i <= n ; i++)
	{
		ll w; 
		scanf("%lld" , &w);
		pq.push(make_pair(w , 0));
	}
	while((n - 1) % (k - 1))
	{
		pq.push(make_pair(0 , 0));
		n++;
	}
	while(pq.size() > 1)
	{
		ll sum = 0; int len = 0;
		for(int i = 1 ; i <= k ; i++)
		{
			PI t = pq.top(); pq.pop();
			sum += t.first , len = max(len , t.second);
		}
		ans += sum;
		pq.push(make_pair(sum , len + 1));
	}
	printf("%lld\n%d" , ans , pq.top().second);
	return 0;
}
