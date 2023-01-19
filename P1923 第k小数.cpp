#include<iostream>
#include<cstdio>
using namespace std;
const int N = 5e6 + 5;
int n , k , a[N];
int Kth(int l , int r , int k)
{
	if(l == r)return a[l];
	int val = a[(l + r) >> 1] , i = l , j = r;
	while(i <= j)
	{
		while(i <= j && a[i] < val)i++;
		while(i <= j && a[j] > val)j--;
		if(i <= j)swap(a[i++] , a[j--]);
	}
//	cout << l << ' ' << r << ' ' << k << ':' << val << ';'<< i << ',' << j << endl;
//	for(int i = 1 ; i <= n ; i++)
//		cout << a[i] << ' ';
//	cout << endl;
	if(k <= (j - l + 1))return Kth(l , j , k);
	else if(k == j - l + 2)return a[j + 1];
	else return Kth(i , r , k - (j - l + 1));
}
int main()
{
	scanf("%d%d" , &n , &k);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	printf("%d" , Kth(1 , n , k + 1));
	return 0;
}
