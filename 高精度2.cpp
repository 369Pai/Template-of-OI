#include<bits/stdc++.h>
using namespace std;
long long c1 , c2;
struct UBigint : public vector<int>
{
	const static int BASE = 1e7 , D = 7;
	UBigint(){}
	UBigint(string s) 
	{
		emplace_back(0);
		for(int i = s.size() - 1 , j , t ; i >= 0 ; i -= D)
		{
			for(j = max(0 , i - D + 1) , t = 0; j <= i ; ++j)t = (t * 10 + (s[j] - '0'));
			emplace_back(t);
		}
	}
	UBigint(int t)
	{
		string s = "";
		if(!t)s = "0";
		while(t > 0)s += t % 10 + '0' , t /= 10;
		reverse(s.begin() , s.end());
		*this = s;
	}
	friend void Maintain(UBigint& c){while(c.size() > 2 && !c.back())c.pop_back();}
	friend void Print(UBigint a , char ch = ' ')
	{
		Maintain(a);
		for(int i = a.size() - 1 ; i >= 1 ; i--)
		{
			if(i == a.size() - 1)printf("%d" , a[i]);
			else printf("%0*d" , D , a[i]);
		}
		putchar(ch);
	}
	friend bool operator <(const UBigint &a , const UBigint &b)
	{
		if(a.size() != b.size())return a.size() < b.size();
		for(int i = a.size() - 1 ; i >= 1 ; i--)
			if(a[i] != b[i])return a[i] < b[i];
		return 0;
	}
	friend bool operator <=(const UBigint &a , const UBigint &b){return a < b || a == b;}
	friend bool operator >=(const UBigint &a , const UBigint &b){return !(a < b);}
	friend bool operator >(const UBigint &a , const UBigint &b){return !(a < b) && a != b;}
	friend UBigint operator + (const UBigint &a , const UBigint &b)
	{
		UBigint c = a;
		c.resize(max(a.size() , b.size()) + 1);
		//tips1:save the size
		for(int i = 1 , en = b.size() ; i < en ; i++)c[i] += b[i];
		for(int i = 1 , en = c.size() ; i + 1 < en ; i++)
			c[i + 1] += c[i] / BASE , c[i] %= BASE;
		Maintain(c);
		return c;
	}
	friend UBigint operator - (const UBigint &a , const UBigint &b)
	{
		UBigint c = a;
		for(int i = 1 , en = b.size() ; i < en ; i++)c[i] -= b[i];
		for(int i = 1 , en = c.size() ; i + 1 < en ; i++)if(c[i] < 0)c[i] += BASE , c[i + 1]--;	
		Maintain(c);
		return c;
	}
	friend UBigint operator * (const UBigint &a , const UBigint &b)
	{
		auto t1 = chrono::steady_clock::now();
		int sa = a.size() , sb = b.size();
		vector<long long>t(sa + sb);
		for(int i = 1 ; i < sa ; i++)
			for(int j = 1 ; j < sb ; j++)
				t[i + j - 1] += (long long)a[i] * b[j];//can hold digits = 2^63/((BASE-1)^2)*D
		for(int i = 1 , en = t.size() ; i + 1 < en ; i++)
			t[i + 1] += t[i] / BASE , t[i] %= BASE; 
		UBigint c;
		c.resize(sa + sb);			
		for(int i = 1 , en = c.size() ; i < en ; i++)c[i] = (int)t[i];
		Maintain(c);
		auto t2 = chrono::steady_clock::now();
		c2 += (t2 - t1) / 1us;
		return c;
	}
	friend UBigint operator / (const UBigint &a , const int &b)
	{
		UBigint c = a;
		for(int x = 0 , i = c.size() - 1 ; i >= 1 ; i--)
			x = x * BASE + c[i] , c[i] = x / b , x %= b;
		Maintain(c);
		return c;
	}
	friend int operator % (const UBigint &a , const int &b)
	{
		int x = 0;
		for(int i = a.size() - 1 ; i >= 1 ; i--)
			x = x * BASE + a[i] , x %= b;
		return x;
	}
	friend UBigint operator / (const UBigint &a , const UBigint &b)
	{
		UBigint c;
		c.resize(max((int)a.size() - (int)b.size() , 0) + 2);
		if(!(a < b))
		{
			UBigint x; x.resize(1);
			for(int i = a.size() - 1 , en = c.size() - 1; i > en ; i--)x.insert(x.begin() + 1 , a[i]);
			for(int i = c.size() - 1 ; i >= 1 ; i--)
			{
				//tips2: use insert and assign
				x.insert(x.begin() + 1 , a[i]); Maintain(x);
				long long t = (x.size() > b.size()) ? (1ll * x.back() * BASE + x[x.size() - 2]) : x.back();
				int l = t / (b.back() + 1) , r = (t + 1) / b.back();//tips3: guess l , r;
				while(l < r)
				{
					int mid = (l + r + 1) / 2;
					if(b * mid <= x)l = mid;
					else r = mid - 1;
				}
				c[i] = l;
				x = x - b * l;
			}	
		}
		Maintain(c);
		return c;
	}
	friend UBigint operator % (const UBigint &a , const UBigint &b){return a - a / b * b;}
	inline friend UBigint operator ^ (UBigint x , int p)
	{
		auto t1 = chrono::steady_clock::now();
		UBigint res = 1;
		for(; p > 0 ; p >>= 1 , x = x * x)
			if(p & 1)res = res * x;
		auto t2 = chrono::steady_clock::now();
		c1 += (t2 - t1) / 1us;
		return res;	
	}
	inline friend UBigint sqrt(const UBigint& n , const int& m)
	{
		UBigint l = 0 , r = 1;
		if(m == 1)return n;
		while((r ^ m) <= n)r = r * 2;
		l = r / 2;
		while(l < r)
		{
			UBigint mid = (l + r + 1) / 2;
			if((mid ^ m) <= n)l = mid;
			else r = mid - 1;
		}
		return l;
	}
};
typedef unsigned long long ull;
int main()
{
	int m; string s1;
	cin >> m >> s1;
	Print(sqrt(UBigint(s1) , m));
	return 0;
}
