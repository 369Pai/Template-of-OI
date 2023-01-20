#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5 , MODY = 1e9 + 1 , MODX = 39989;
const double EPS = 1e-8;
typedef pair<double , int>PDI;
struct LiChaoSegmentTree
{
	int rt , tot , totl , lc[N] , rc[N] , tr[N];
	struct Line{double k , b;}a[N];
	LiChaoSegmentTree():rt(0),tot(0),totl(0){a[0].k = a[0].b = -1e18;}
	double Calc(int id , double x){return a[id].k * x + a[id].b;}
	int Cmp(double x , double y)
	{
		double t = x - y;
		if(fabs(t) < EPS)return 0;
		return t < 0 ? -1 : 1;
	}
	PDI Pmax(PDI a , PDI b)
	{
		if(!Cmp(a.first , b.first))return make_pair(a.first , min(a.second , b.second));
		return Cmp(a.first , b.first) == -1 ? b : a; 
	}
	PDI Query(int l , int r , int p , int v)
	{
		if(!p)return make_pair(-1e18 , 0);
		if(l == r)return make_pair(Calc(tr[p] , v) , tr[p]);
		int mid = (l + r) >> 1; PDI ans = make_pair(Calc(tr[p] , v) , tr[p]);
		if(v <= mid)ans = Pmax(ans , Query(l , mid , lc[p] , v));
		else ans = Pmax(ans , Query(mid + 1 , r , rc[p] , v));
		return ans;
	}
	void Upd(int l , int r , int& p , int v)
	{
//		cout << "Upd:" << l << ' ' << r << ' ' << p << ' ' << v << endl;
		if(!p)p = ++tot; 
		int &u = tr[p] , mid = (l + r) >> 1;
		int cm = Cmp(Calc(u , mid) , Calc(v , mid));
		if(cm < 0 || (cm == 0 && u > v))swap(u , v);
		if(!v || l == r)return ;
		int cl = Cmp(Calc(u , l) , Calc(v , l)) , cr = Cmp(Calc(u , r) , Calc(v , r));
		if(cl < 0 || (cl == 0 && u > v))Upd(l , mid , lc[p] , v);
		if(cr < 0 || (cr == 0 && u > v))Upd(mid + 1 , r , rc[p] , v);
	}
	void Update(int l , int r , int& p , int s , int e , int v)
	{
		if(!p)p = ++tot;
		if(s <= l && r <= e)
		{
			Upd(l , r , p , v);
			return ;
		}
		int mid = (l + r) >> 1;
		if(s <= mid)Update(l , mid , lc[p] , s , e , v);
		if(mid < e)Update(mid + 1 , r , rc[p] , s , e , v);
	}
	void Add(int x0 , int y0 , int x1 , int y1)
	{
		if(x0 > x1)swap(x0 , x1) , swap(y0 , y1);
		if(x0 == x1)a[++totl] = {0 , max(y0 , y1)};
		else
		{
			double k = (double)(y0 - y1) / (x0 - x1) , b = y0 - x0 * k;
			a[++totl] = {k , b};
		}
		Update(1 , MODX , rt , x0 , x1 , totl);
	}
}sgt;
int q , lastans;
int main()
{
	scanf("%d" , &q);
	while(q--)
	{
		int op , x0 , x1 , y0 , y1;
		scanf("%d" , &op);
		if(op == 0)
		{
			scanf("%d" , &x0);
			x0 = (x0 + lastans - 1) % MODX + 1;
//			cout << "k:" << x0 << endl;
			lastans = sgt.Query(1 , MODX , sgt.rt , x0).second;
			printf("%d\n" , lastans);
		}
		if(op == 1)
		{
			scanf("%d%d%d%d" , &x0 , &y0 , &x1 , &y1);
			x0 = (x0 + lastans - 1) % MODX + 1;
			x1 = (x1 + lastans - 1) % MODX + 1;
			y0 = (y0 + lastans - 1) % MODY + 1;
			y1 = (y1 + lastans - 1) % MODY + 1;
			sgt.Add(x0 , y0 , x1 , y1);
//			cout << "4:" << x0  << ' ' << y0 << ' ' << x1 << ' ' << y1 << endl;
		}	
	}
	return 0;
}
