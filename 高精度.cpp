#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
void Trans(string s , int a[])
{
	reverse(s.begin() , s.end());
	for(int i = 0 ; i < s.size() ; i++)
		a[i + 1] = s[i] - '0';
	a[0] = s.size();
}
void Add(const int a[] , const int b[] , int c[])
{
	int x = 0;
	c[0] = max(a[0] , b[0]);
	fill(c , c + c[0] + 1 , 0);
	for(int i = 1 ; i <= c[0] ; i++)
	{
		c[i] = a[i] + b[i] + x;
		x = c[i] / 10;
		c[i] %= 10;
	}
	if(x)c[++c[0]] = x;
}
void Sub(const int a[] , const int b[] , int c[])
{
	int x = 0;
	c[0] = max(a[0] , b[0]);
	fill(c , c + c[0] + 1 , 0);
	for(int i = 1 ; i <= c[0] ; i++)
	{
		c[i] = a[i] - b[i] - x;
		if(c[i] < 0)
		{
			c[i] += 10;
			x = 1;
		}
		else x = 0;
	}
	while(c[0] > 1 && !c[c[0]])c[0]--;
}
void Mul(const int a[] , const int b[] , int c[])
{
	c[0] = a[0] + b[0];
	fill(c , c + c[0] + 1 , 0);
	for(int i = 1 ; i <= a[0] ; i++)
	{
		int x = 0;
		for(int j = 1 ; j <= b[0] ; j++)
		{
			c[i + j - 1] += a[i] * b[j] + x;
			x = c[i + j - 1] / 10;
			c[i + j - 1] %= 10;
		}
		c[i + b[0]] += x;
	}
	while(c[0] > 1 && !c[c[0]])c[0]--;
}
void Div(const int a[] , const int b , int c[] , int& yu)
{
	long long x = 0;
	c[0] = a[0];
	fill(c , c + c[0] + 1 , 0);
	for(int i = a[0] ; i >= 1 ; i--)
	{
		x = x * 10 + a[i];
		c[i] = x / b;
		x %= b;
	}
	while(c[0] > 1 && !c[c[0]])c[0]--;
	yu = x;
}
void Print(const int a[])
{
	for(int i = a[0] ; i >= 1 ; i--)
		printf("%d" , a[i]);
	printf("\n");
}
int main()
{
	return 0;
}

