#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 5e5 + 5;
int n , a[N] , b[N];
long long ans = 0;
void MergeSort(int l , int r)
{
	if(l == r)return ;
	int mid = (l + r) >> 1;
	MergeSort(l , mid);
	MergeSort(mid + 1 , r);
	int i = l , j = mid + 1;
	for(int k = l ; k <= r ; k++)
	{
		if(j > r || (i <= mid && a[i] <= a[j]))b[k] = a[i++];
		else b[k] = a[j++] , ans += mid - i + 1;
	}
	for(int i = l ; i <= r ; i++)
		a[i] = b[i];
}
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	MergeSort(1 , n);
	printf("%lld" , ans);
	return 0;
}
