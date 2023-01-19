#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6 + 5 , P = 133; 
string s1 , s2;
int n , m , nxt[N];
ull ans , f[N] , p[N] = {1,P};
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin >> s1 >> s2;
	n = s1.size() , m = s2.size();
	s1 = '#' + s1;  s2 = '#' + s2;
	
	nxt[1] = 0 , ans = s2[1] - 'A' + 1 ;
	for(int i = 2 , j = 0; i <= m ; i++)
	{
		while(j > 0 && s2[i] != s2[j + 1])j = nxt[j];
		if(s2[i] == s2[j + 1])j++;
		nxt[i] = j;
		
		ans = ans * P + (s2[i] - 'A' + 1);
	}
	for(int i = 1 ; i <= n ; i++)
		f[i] = f[i - 1] * P + (s1[i] - 'A' + 1) , p[i] = p[i - 1] * P;
	
	for(int i = 1 ; i <= n - m + 1; i++)
	{
		if(f[i + m - 1] - f[i - 1] * p[m] == ans)
		{
			cout << i << '\n';
		}
	}
	
	for(int i = 1 ; i <= m ; i++)
		cout << nxt[i] << ' ';
	
	return 0;
}
