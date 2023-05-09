#include<bits/stdc++.h>
using namespace std;
int main()
{
    int i;
    system("g++ ./rand.cpp -O2 -o rand");
    system("g++ ./std.cpp -O2 -o std");
    system("g++ ./test.cpp -O2 -o test");
    for (i=1;; i++)
    {
        printf("The result of No. %d Case is:  ",i);
        system("./rand > in.txt");
		auto t1 = chrono::steady_clock::now();
        system("cat in.txt | ./std > std.out");
		auto t2 = chrono::steady_clock::now();
        system("cat in.txt | ./test > test.out");
		auto t3 = chrono::steady_clock::now();
        if (system("diff std.out test.out"))
        {
            printf("Wrong Answer\n");
            return 0;
        }
		else printf("Accepted std: %.3lfms test: %.3lfms\n" , (t2 - t1) / 1us / 1000.0 , (t3 - t2) / 1us / 1000.0);
    }
    return 0;
}