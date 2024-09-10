#include "bits/stdc++.h"
#include "unistd.h"
using namespace std;
int main()
{
	string name = ""; int tp = 0;
	system("g++ -std=c++14 -O2 ./test.cpp ./grader.cpp -o test");
	bool fail[10] = {};
	for(int task = 1 ; task <= 6 ; task++)
	{
		if(task == 2 && fail[1])break ;
		for(int cs = 1 ; ; cs++)
		{
			string str = name + to_string(task) + "-" + to_string(cs);
			if(access((str + ".in").c_str() , F_OK) != 0)break ;
			
			string op1 = "cat ./" + (str + ".in") + " | ./std > ./" + "std.out";
			auto t_1 = chrono::high_resolution_clock::now();
			if(tp)
			{
				printf("%s\n" , op1.c_str());
				system(op1.c_str());
			}

			string op2 = "cat ./" + (str + ".in") + " | ./test > ./" + "test.out";
			auto t_2 = chrono::high_resolution_clock::now();
			printf("%s\n" , op2.c_str());
			bool re = system(op2.c_str());

			auto t_3 = chrono::high_resolution_clock::now();
			if (system(("diff test.out " + str + ".out").c_str()) || 
				(tp && system("diff test.out std.out")))
			{
				printf("Wrong Answer\n");
				fail[task] = 1;
				break ;
			}
			else if(re)
			{
				printf("Runtime Error\n");
				fail[task] = 1;
				break ;
			}
			else printf("Accepted std: %lfms test: %lfms\n" , std::chrono::duration<double, std::milli>(t_2 - t_1).count() , std::chrono::duration<double, std::milli>(t_3 - t_2).count());			
		}
	}
	// system("rm std.out test.out");
	return 0;
}
