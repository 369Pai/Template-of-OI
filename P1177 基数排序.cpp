#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1e5 + 5 , K = 1000 , D = 3;
int n , a[N] , b[N] , t[K + 5] , p = 1;
void CountSort()
{
	memset(t , 0 , sizeof t);
	for(int i = 1 ; i <= n ; i++)
		t[a[i] / p % K]++;
	for(int i = 1 ; i < K ; i++)
		t[i] += t[i - 1];
	for(int i = n ; i >= 1 ; i--)
		b[t[a[i] / p % K]--] = a[i];
	memcpy(a , b , sizeof b);
}
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	for(int i = 1 ; i <= D ; i++)
	{
		CountSort();
		p *= K;
	}	
	for(int i = 1 ; i <= n ; i++)
		printf("%d " , a[i]);
	return 0;
}
