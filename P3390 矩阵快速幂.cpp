#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
typedef long long ll;
typedef vector<vector<int> >Mat;
Mat NewMat(int n , int m)
{
	Mat c; c.resize(n + 1);
	for(int i = 0 ; i <= n ; i++)c[i].resize(m + 1);
	c[0][0] = n , c[0][1] = m;
	return c;
}
Mat operator * (const Mat& a , const Mat& b)
{
	int n = a[0][0] , t = a[0][1] , m = b[0][1];
	Mat c = NewMat(n , m);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			for(int k = 1 ; k <= t ; k++)
				c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
	return c;
}
Mat operator ^ (Mat x , ll p)
{
	int n = x[0][0];
	Mat res = NewMat(n, n);
	for(int i = 1 ; i <= n ; i++)res[i][i] = 1;
	for(; p > 0 ; x = x * x , p >>= 1)
		if(p & 1)res = res * x;
	return res;
}
void Print(const Mat& a)
{
	int n = a[0][0] , m = a[0][1];
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
			printf("%d " , a[i][j]);
		printf("\n");
	}
}
int main()
{
	int n; ll k;
	scanf("%d%lld" , &n , &k);
	Mat A = NewMat(n , n);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			scanf("%d" , &A[i][j]);
	Print(A ^ k);
	return 0;
}
