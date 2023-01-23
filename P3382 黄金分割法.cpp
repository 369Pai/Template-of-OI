#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PHI = (sqrt(5) - 1) / 2;
int n , cnt; double a[20];
double F(double x)
{
	double ans = 0 , px = 1;
	for(int i = n + 1 ; i >= 1 ; i--)
	{
		ans += px * a[i];
		px *= x;
	}
	return ans;
}
int main()
{
	double l , r , eps = 1e-7;
	scanf("%d%lf%lf" , &n , &l , &r);
	for(int i = 1 ; i <= n + 1 ; i ++)
		scanf("%lf" , &a[i]);
	double mid1 = r - (r - l) * PHI , mid2 = l + (r - l) * PHI , f1 , f2;
	bool b1 = 0 , b2 = 0;
	while(fabs(l - r) > eps)
	{
		if(!b1)f1 = F(mid1); if(!b2)f2 = F(mid2);
		if(f1 < f2)l = mid1 , mid1 = mid2 , f1 = f2 , b1 = 1 , mid2 = l + (r - l) * PHI , b2 = 0;
		else r = mid2 , mid2 = mid1 , f2 = f1 , b2 = 1 , mid1 = r - (r - l) * PHI , b1 = 0;
	}
	printf("%.7lf" , l);
	return 0;
}
