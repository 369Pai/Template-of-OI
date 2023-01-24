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
double S(Point A , Point B , Point C){return Cross(B - A, C - A);}
Vector Rotate(Vector a , double rad){return Vector(a.x * cos(rad) - a.y * sin(rad) , a.y * cos(rad) + a.x * sin(rad));}
Vector Rotate2(Vector a , double rad)
{
	double ang = atan2(a.y , a.x) , len = Length(a);
	return Vector(cos(rad + ang) * len , sin(rad + ang) * len);
}
Vector Normal(Vector a){double L = Length(a); return Vector(-a.y/L,a.x/L);}
Point GetLineIntersection(Point P , Vector v , Point Q , Vector w)
{
	Vector u = P - Q;
	double t = Cross(w , u) / Cross(v , w);
	return P + v * t;
}
double DistanceToLine(Point P , Point A , Point B)
{
	Vector v1 = B - A , v2 = P - A;
	return fabs(Cross(v1 , v2) / Length(v1));
}
double DistanceToSegment(Point P , Point A , Point B)
{
	if(A == B)return Length(P - A);
	Vector v1 = B - A , v2 = P - A , v3 = P - B;
	if(Dcmp(Dot(v1 , v2) < 0))return Length(v2);
	else if(Dcmp(Dot(v1 , v3)) > 0)return Length(v3);
	else return DistanceToLine(P , A , B);
}
Point GetLineProjection(Point P , Point A , Point B)
{
	Vector v = B - A;
	return A + v * Dot(v , P - A) / Dot(v , v);
}
bool SegmentProperIntersection(Point A1 , Point A2 , Point B1 , Point B2)
{
	double c1 = Cross(A2 - A1 , B1 - A1) , c2 = Cross(A2 - A1 , B2 - A1),
	c3 = Cross(B2 - B1 , A1 - B1) , c4 = Cross(B2 - B1 , A2 - B1);
	return Dcmp(c1) * Dcmp(c2) < 0 && Dcmp(c3) * Dcmp(c4) < 0; 
}
bool OnSegment(Point P , Point A , Point B)
{
	return (Dcmp(Cross(B - A , P - A)) == 0 && Dot(P - A , P - B) < 0) || P == A || P == B;
}
bool SegmentIntersection(Point A1 , Point A2 , Point B1 , Point B2)
{
	return SegmentProperIntersection(A1 , A2 , B1 , B2) || OnSegment(B1 , A1 , A2) || OnSegment(B2 , A1 , A2) || OnSegment(A1 , B1 , B2) || OnSegment(A2 , B1 , B2); 
}
double PolygonArea(Point P[] , int n)
{
	double area = 0;
	for(int i = 1 ; i <= n ; i++)
		area += Cross(P[i] - P[0] , P[i % n + 1] - P[0]);
	return area / 2;
}
struct Circle
{
	Point c; double r;
	Circle(Point c , double r):c(c) , r(r){}
	Point point(double a){return Point(c.x + cos(a) * r , c.y + sin(a) * r);}
};
struct Line
{
	Point P; Vector v;
	Line(Point P , Vector v):P(P) , v(v){}
	Point point(double t){return P + v * t;}
};
int GetLineCircleIntersection(Line L, Circle C , vector<Point>& sol)
{
	double d = DistanceToLine(C.c , L.P , L.P + L.v);
	if(Dcmp(d - C.r) > 0)return 0;
	Point P = GetLineProjection(C.c , L.P , L.P + L.v);
	if(Dcmp(d - C.r) == 0){sol.push_back(P);return 1;}
	double L0 = sqrt(C.r * C.r - d * d);
	Vector V = L.v / Length(L.v);
	sol.push_back(P + V * L0); sol.push_back(P - V * L0);
	return 2;
}
double Angle(Vector v){return atan2(v.y , v.x);}
int GetCircleIntersection(Circle C1 , Circle C2 , vector<Point>&sol)
{
	double d = Length(C1.c - C2.c);
	if(Dcmp(d) == 0)
	{
		if(Dcmp(C1.r - C2.r) == 0)return -1;
		return 0;
	}
	if(Dcmp(C1.r+C2.r-d)<0 || Dcmp(fabs(C1.r-C2.r)-d)>0)return 0;//分离或内含
	double a=Angle(C2.c-C1.c),da=acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
	Point P1=C1.point(a+da),P2=C1.point(a-da);
	sol.push_back(P1);
	if(P1==P2)return 1;
	sol.push_back(P2);return 2;
}
int GetTangents(Circle A, Circle B, Point* a , Point* b)
{
	int cnt = 0;
	if(A.r < B.r){swap(A , B); swap(a , b);}
	double d = Length(A.c - B.c) , diff = A.r - B.r ,rsum = A.r + B.r;
	if(d == 0 && A.r == B.r)return -1;
	if(d < diff)return 0;
	double base = Angle(A.c - B.c);
	if(d == diff)
	{
		a[++cnt] = A.point(base); b[cnt] = B.point(base); return 1;
	}
	double ang = acos((A.r - B.r) / d);
	a[++cnt] = A.point(base + ang), b[cnt] = B.point(base + ang);
	a[++cnt] = A.point(base - ang), b[cnt] = B.point(base - ang);
	if(d == rsum){a[++cnt] = A.point(base) , b[cnt] = B.point(base + PI);}
	else if(d > rsum)
	{
		double ang = acos(rsum / d);
		a[++cnt] = A.point(base + ang) , b[cnt] = B.point(base + ang + PI);
		a[++cnt] = A.point(base - ang) , b[cnt] = B.point(base - ang + PI);
	}
	return cnt;
}
bool IsPointOnSegment(Point P , Point A , Point B){return OnSegment(P , A , B) || P == A || P == B;}
int IsPointInPolygon(Point P , Point poly[] , int n)
{
	int wn = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		if(IsPointOnSegment(P , poly[i] , poly[i % n + 1]))return -1;
		int k = Dcmp(Cross(poly[i % n + 1] - poly[i] , P - poly[i]));
		int d1 = Dcmp(poly[i].y - P.y);
		int d2 = Dcmp(poly[i % n + 1].y - P.y);
		if(k > 0 && d1 <= 0 && d2 > 0)wn++;//notice =
		if(k < 0 && d2 <= 0 && d1 > 0)wn--;//notice =
	}
	if(wn != 0)return 1;
	return 0;
}
int ConvexHull(Point p[] , int n , Point ch[])
{
	sort(p + 1 , p + n + 1);
	int top = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		while(top > 1 && Dcmp(Cross(ch[top] - ch[top - 1] , p[i] - ch[top - 1])) <= 0)top--;
		ch[++top] = p[i];
	}
	int k = top;
	for(int i = n - 1 ; i >= 1 ; i--)
	{
		while(top > k && Dcmp(Cross(ch[top] - ch[top - 1] , p[i] - ch[top - 1])) <= 0)top--;
		ch[++top] = p[i];
	}
	if(n > 1)top--;
	return top;
}
int main()
{
	 
	return 0;
}
