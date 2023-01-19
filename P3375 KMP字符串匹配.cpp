#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int N = 1e6 + 5; 
string s1 , s2;
int n , m , nxt[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin >> s1 >> s2;
	n = s1.size() , m = s2.size();
	s1 = '#' + s1;  s2 = '#' + s2;
	
	nxt[1] = 0;
	for(int i = 2 , j = 0; i <= m ; i++)
	{
		while(j > 0 && s2[i] != s2[j + 1])j = nxt[j];
		if(s2[i] == s2[j + 1])j++;
		nxt[i] = j;
	}
	
	for(int i = 1 , j = 0 ; i <= n ; i++)
	{
		while(j > 0 && s1[i] != s2[j + 1])j = nxt[j];
		if(s1[i] == s2[j + 1])j++;
		if(j == m)
		{
			cout << i - m + 1 << '\n';
			j = nxt[j];
		}
	}
	
	for(int i = 1 ; i <= m ; i++)
		cout << nxt[i] << ' ';
	
	return 0;
}
