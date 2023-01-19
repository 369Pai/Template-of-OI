#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
double a[15];
inline double F(double x)
{
	double ans = 0;
	for(int i = 0 ; i <= n ; i++)
		ans += pow(x , i) * a[i];
	return ans;
}
int main()
{
	double l , r , eps = 1e-7;
	scanf("%d%lf%lf" , &n , &l , &r);
	for(int i = n ; i >= 0 ; i--)
		scanf("%lf" , &a[i]);
	while(fabs(l - r) > eps)
	{
		double lmid = (l + r) / 2 , rmid = (lmid + r) / 2;
		if(F(lmid) < F(rmid))l = lmid;
		else r = rmid;
	}
	printf("%.7lf" , l);
	return 0;
}
