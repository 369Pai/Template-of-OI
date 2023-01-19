#include <iostream>
#include <algorithm>


signed main(signed argc, char** argv)
{
    freopen("in.txt","r",stdin);
    freopen("test.out","w",stdout);
	for(int i = 1 ; i <= 10000000 ; i++)
	{
		printf("%d\n" , i % 100000000);
	}
	return 0;
}
