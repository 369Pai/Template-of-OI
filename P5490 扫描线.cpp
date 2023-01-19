#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int , int> PI;
const int N = 1e5 + 5;
int n , m ,  by[N * 2];
int tr[N * 16] , tag[N * 16];
pair<PI , PI>a[N * 2];
void Pushup(int l , int r , int p)
{
	if(tag[p] >= 1)tr[p] = by[r + 1] - by[l];
	else tr[p] = tr[p * 2] + tr[p * 2 + 1];
};
void Update(int l , int r , int p , int s , int e , int v)
{
	if(s <= l && r <= e)
	{
		tag[p] += v;
		Pushup(l , r , p);
		return ;
	}
	int mid = (l + r) >> 1;
	if(s <= mid)Update(l , mid , p * 2 , s , e , v);
	if(mid < e)Update(mid + 1 , r , p * 2 + 1 , s , e , v);
	Pushup(l , r , p);
}
int main()
{
//	freopen("P5490_3.in" , "r" , stdin);
//	freopen("P5490.out" , "w" , stdout);
	int nn; long long ans = 0;
	scanf("%d" , &nn);
	for(int i = 1 ; i <= nn ; i++)
	{
		int x1 , y1 , x2 , y2;
		scanf("%d%d%d%d" , &x1 , &y1 , &x2 , &y2);
		by[++m] = y1 , by[++m] = y2;
		a[++n] = make_pair(make_pair(x1 , 1) , make_pair(y1 , y2));
		a[++n] = make_pair(make_pair(x2 , -1) , make_pair(y1 , y2));
	}
	sort(a + 1 , a + n + 1);
	sort(by + 1 , by + m + 1);
	m = unique(by + 1 , by + m + 1) - by - 1;
	for(int i = 1 ; i <= n ; i++)
	{
		int x = a[i].first.first , v = a[i].first.second;
		int y1 = a[i].second.first , y2 = a[i].second.second;
		int b1 = lower_bound(by + 1 , by + m + 1 , y1) - by;
		int b2 = lower_bound(by + 1 , by + m + 1 , y2) - by;
//		cout << b1 << ' ' << b2 << ' ' << tr[1] << endl;
		ans += (long long)tr[1] * (x - a[i - 1].first.first);
		Update(1 , m - 1 , 1 , b1 , b2 - 1 , v);
	}
	printf("%lld" , ans);
	return 0;
}
