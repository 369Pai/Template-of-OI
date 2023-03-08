#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 55; 
const double EPS = 1e-8;
int n; double a[N][N];
void Guass()
{
	for(int i = 1 , tot = 1 ; i <= n ; i++)
	{
		for(int j = tot ; j <= n ; j++)
		{
			if(fabs(a[j][i]) > EPS)
			{
				for(int k = 1 ; k <= n + 1; k++)swap(a[j][k] , a[tot][k]);
				break;
			}
		}
		if(fabs(a[tot][i]) < EPS)continue ;
		for(int j = 1 ; j <= n ; j++)
		{
			if(tot == j)continue ;
			double r = a[j][i] / a[tot][i];
			for(int k = 1 ; k <= n + 1 ; k++)a[j][k] -= a[tot][k] * r;
		}
		tot++;
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		bool all0 = 1;
		for(int j = 1 ; j <= n ; j++)if(fabs(a[i][j]) > EPS)all0 = 0;
		if(!all0)continue ;
		if(fabs(a[i][n + 1]) < EPS)ans = max(ans , 1);
		else ans = max(ans , 2);
	}
	if(ans == 2)printf("-1");
	else if(ans == 1)printf("0");
	else
	{
		for(int i = 1 ; i <= n ; i++)
		{
			double ans = a[i][n + 1] / a[i][i];
			string str; char buf[20];
			sprintf(buf , "%.2lf" , ans);
			str = buf;
			if(str == "-0.00")str = "0.00";
			printf("x%d=%s\n" , i , str.c_str());
		}		
	}
}
int main()
{	
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n + 1 ; j++)
			scanf("%lf" , &a[i][j]);
	Guass();
	return 0;
}
