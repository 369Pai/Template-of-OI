#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
priority_queue<int , vector<int> , greater<int> >pq;
int main()
{
	int n;
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		int op , x;
		scanf("%d" , &op);
		if(op == 1)
		{
			scanf("%d" , &x);
			pq.push(x);
		}
		if(op == 2)printf("%d\n" , pq.top());
		if(op == 3)pq.pop();
	}
	return 0;
}
