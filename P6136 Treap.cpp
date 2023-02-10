#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;
const int MAXN = 1100005;
int val[MAXN], ch[MAXN][2], cnt[MAXN], siz[MAXN], dat[MAXN], tot, root;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline long long Read()
{
	long long x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
int New(int v)
{
	val[++tot] = v;
	siz[tot] = cnt[tot] = 1;
	dat[tot] = rand();
	return tot;
}
void Maintain(int id) { siz[id] = siz[ch[id][0]] + siz[ch[id][1]] + cnt[id]; }
void Rotate(int &id, int d)
{
	int tmp = ch[id][d ^ 1];
	ch[id][d ^ 1] = ch[tmp][d];
	ch[tmp][d] = id;
	id = tmp;
	Maintain(ch[id][d]), Maintain(id);
}
void Insert(int &id, int v)
{
	if (!id)
	{
		id = New(v);
		return;
	}
	if (val[id] == v)
	{
		cnt[id]++;
	}
	else
	{
		int d = v < val[id] ? 0 : 1;
		Insert(ch[id][d], v);
		if (dat[id] < dat[ch[id][d]])
		{
			Rotate(id, d ^ 1);
		}
	}
	Maintain(id);
}
void Delete(int &id, int v)
{
	if (!id)
	{
		return;
	}
	if (val[id] == v)
	{
		if (cnt[id] > 1)
		{
			cnt[id]--;
			Maintain(id);
			return;
		}
		else if (ch[id][0] || ch[id][1])
		{
			if (!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]])
			{
				Rotate(id, 1);
				Delete(ch[id][1], v);
			}
			else
			{
				Rotate(id, 0);
				Delete(ch[id][0], v);
			}
			Maintain(id);
		}
		else
		{
			id = 0;
		}
		return;
	}
	if (v < val[id])
	{
		Delete(ch[id][0], v);
	}
	else
	{
		Delete(ch[id][1], v);
	}
	Maintain(id);
}
int Pre(int x)
{
	int id = root, pre = -0x7fffffff;
	while (id)
	{
		if (val[id] < x)
			pre = val[id], id = ch[id][1];
		else
			id = ch[id][0];
	}
	return pre;
}
int Nxt(int x)
{
	int id = root, nxt = 0x7fffffff;
	while (id)
	{
		if (val[id] > x)
			nxt = val[id], id = ch[id][0];
		else
			id = ch[id][1];
	}
	return nxt;
}
int Kth(int id, int k)
{
	if (!id)
		return 0x7fffffff;
	if (k <= siz[ch[id][0]])
		return Kth(ch[id][0], k);
	else if (k <= siz[ch[id][0]] + cnt[id])
		return val[id];
	else
		return Kth(ch[id][1], k - siz[ch[id][0]] - cnt[id]);
}
int Rank(int id, int v)
{
	if (!id)
		return 1;
	if (val[id] == v)
		return siz[ch[id][0]] + 1;
	else if (val[id] < v)
		return siz[ch[id][0]] + cnt[id] + Rank(ch[id][1], v);
	else
		return Rank(ch[id][0], v);
}
int main()
{
	int n = Read(), m = Read(), ans = 0, last = 0;
	// root = New(0x7fffffff);
	// ch[root][0] = New(-0x7fffffff);
	// Maintain(root);
	root = New(Read());
	for (int i = 2; i <= n; i++)
	{
		Insert(root, Read());
	}
	for (int i = 1; i <= m; i++)
	{
		int op = Read(), x = Read();
		x ^= last;
		//		cout << i << ' ' << x << endl;
		if (op == 1)
		{
			Insert(root, x);
		}
		else if (op == 2)
		{
			Delete(root, x);
		}
		else if (op == 3)
		{
			last = Rank(root, x);
			ans ^= last;
		}
		else if (op == 4)
		{
			last = Kth(root, x);
			ans ^= last;
		}
		else if (op == 5)
		{
			last = Pre(x);
			ans ^= last;
		}
		else
		{
			last = Nxt(x);
			ans ^= last;
		}
	}
	printf("%d", ans);
	return 0;
}
