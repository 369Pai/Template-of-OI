#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-10 , PI = acos(-1);
struct Point
{
	double x , y;
	Point(double x = 0 , double y = 0):x(x),y(y){}
};
typedef Point Vector;
Vector operator + (Vector a , Vector b){return Vector(a.x + b.x , a.y + b.y);}
Vector operator - (Vector a , Vector b){return Vector(a.x - b.x , a.y - b.y);}
Vector operator * (Vector a , double P){return Vector(a.x * P , a.y * P);}
Vector operator / (Vector a , double P){return Vector(a.x / P , a.y / P);}
bool operator < (const Point& A , const Point &B){return A.x < B.x || (A.x == B.x && A.y < B.y);}
int Dcmp(double x){if(fabs(x) < EPS)return 0; else return x < 0 ? -1 : 1;}
bool operator == (const Point& A , const Point & B){return Dcmp(A.x - B.x) == 0 && Dcmp(A.y - B.y) == 0;}
double Dot(Vector a , Vector b){return a.x * b.x + a.y * b.y;}
double Length(Vector a){return sqrt(Dot(a , a));}
double Angle(Vector a , Vector b){return acos(Dot(a , b) / Length(a) / Length(b));}
double Cross(Vector a , Vector b){return a.x * b.y - a.y * b.x;}
double ConvexHull(Point p[] , int n , Point ch[])
{
	for(int i = 2 ; i <= n ; i++)if(p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x))swap(p[1] , p[i]);
	auto Cmp = [&](Point a , Point b)
	{
		int d = Dcmp(Cross(a - p[1] , b - p[1]));
		return d > 0 || (d == 0 && Length(a - p[1]) < Length(b - p[1])); 
	};
	sort(p + 2 , p + n + 1 , Cmp);
	int top = 1; ch[1] = p[1];
	for(int i = 2 ; i <= n ; i++)
	{
		while(top > 1 && Dcmp(Cross(ch[top] - ch[top - 1] , p[i] - ch[top - 1])) <= 0)top--;
		ch[++top] = p[i];
	}
	return top;
}
const int N = 1e5 + 5;
int n , m; Point p[N] , ch[N];
int main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%lf%lf" , &p[i].x , &p[i].y);
	int m = ConvexHull(p , n , ch);
	double ans = 0;
	for(int i = 1 ; i <= m ; i++)
		ans += Length(ch[i % m + 1] - ch[i]);
	printf("%.2lf" , ans);
	return 0;
}
