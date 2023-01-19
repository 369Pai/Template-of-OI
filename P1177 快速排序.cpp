#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e6 + 5;
int n , a[N];
void Qsort(int l , int r)
{
	if(l >= r)return ;
	int val = a[(l + r) >> 1] , i = l , j = r;
	while(i <= j)
	{
		while(i <= j && a[i] < val)i++;
		while(i <= j && a[j] > val)j--;
		if(i <= j)swap(a[i++] , a[j--]);
	}
	Qsort(l , j);
	Qsort(i , r);
}
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	Qsort(1 , n);
	for(int i = 1 ; i <= n ; i++)
		printf("%d " , a[i]);
	return 0;
}
