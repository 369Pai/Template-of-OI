#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int N = 5e5 + 5 , SZ = 3e6 + 5;
int trie[SZ][62] , cnt[SZ] , tot = 1;
bool ed[SZ];
void Insert(string s)
{
	int p = 1;
	for(int i = 0 ; i < s.size() ; i++)
	{
		int ch;
		if('0' <= s[i] && s[i] <= '9')ch = s[i] - '0';
		if('A' <= s[i] && s[i] <= 'Z')ch = s[i] - 'A' + 10;
		if('a' <= s[i] && s[i] <= 'z')ch = s[i] - 'a' + 36;
		if(trie[p][ch] == 0)trie[p][ch] = ++tot;
		p = trie[p][ch];
		cnt[p]++;
	}
	ed[p] = true;
}
int Search(string s)
{
	int p = 1;
	for(int i = 0 ; i < s.size() ; i++)
	{
		int ch;
		if('0' <= s[i] && s[i] <= '9')ch = s[i] - '0';
		if('A' <= s[i] && s[i] <= 'Z')ch = s[i] - 'A' + 10;
		if('a' <= s[i] && s[i] <= 'z')ch = s[i] - 'a' + 36;
		if(trie[p][ch] == 0)return 0;
		p = trie[p][ch];
	}
	return cnt[p];
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--)
	{
		memset(trie , 0 , sizeof(int) * (tot + 1) * 62);
		memset(cnt , 0 , sizeof(int) * (tot + 1));
		memset(ed , 0 , sizeof(bool) * (tot + 1));
		tot = 1;
		int n , q;
		cin >> n >> q;
		for(int i = 1 ; i <= n ; i++)
		{
			string s;
			cin >> s;
			Insert(s);
		}
		for(int i = 1 ; i <= q ; i++)
		{
			string s;
			cin >> s;
			cout << Search(s) << '\n';
		}
	}
	return 0;
}
