#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
const int N = 1e6 + 5;
inline int Read()
{
	long long x = 0 , f = 1; char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	return x * f;
}
int a[N];
deque<int>dq;
int main()
{
	int n = Read(), k = Read();
	for(int i = 1 ; i <= n ; i++)
		a[i] = Read();
	for(int i = 1 ; i <= n ; i++)
	{
		while(!dq.empty() && dq.front() <= i - k)dq.pop_front();
		while(!dq.empty() && a[dq.back()] > a[i])dq.pop_back();
		dq.push_back(i);
		if(i >= k)printf("%d " , a[dq.front()]);
	}
	puts("");
	dq.clear();
	for(int i = 1 ; i <= n ; i++)
	{
		while(!dq.empty() && dq.front() <= i - k)dq.pop_front();
		while(!dq.empty() && a[dq.back()] < a[i])dq.pop_back();
		dq.push_back(i);
		if(i >= k)printf("%d " , a[dq.front()]);
	}	
	return 0;
}
