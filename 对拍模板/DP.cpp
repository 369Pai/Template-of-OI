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
        system("./rand");
		auto t_1 = chrono::high_resolution_clock::now();
        system("./std");
		auto t_2 = chrono::high_resolution_clock::now();
        system("./test");
		auto t_3 = chrono::high_resolution_clock::now();
        if (system("diff std.out test.out"))
        {
            printf("Wrong Answer\n");
            return 0;
        }
		else printf("Accepted std: %lfms test: %lfms\n" , std::chrono::duration<double, std::milli>(t_2 - t_1).count() , std::chrono::duration<double, std::milli>(t_3 - t_2).count());
    }
    return 0;
}
