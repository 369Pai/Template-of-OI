#include "bits/stdc++.h"
using namespace std;
int main()
{
	string name = "";
	for(int cs = 1 ; cs <= 10 ; cs++)
	{
		string str = name + to_string(cs);
		string op1 = "cat ./" + (str + ".in") + " | ./std > ./" + "std.out";
		printf("%s\n" , op1.c_str());	
		auto t_1 = chrono::high_resolution_clock::now();
		system(op1.c_str());
		auto t_2 = chrono::high_resolution_clock::now();
		string op2 = "cat ./" + (str + ".in") + " | ./test > ./" + "test.out";
		printf("%s\n" , op2.c_str());
		system(op2.c_str());
		auto t_3 = chrono::high_resolution_clock::now();
		if (system("diff std.out test.out"))
		{
			printf("Wrong Answer\n");
			break ;
		}
		else printf("Accepted std: %lfms test: %lfms\n" , std::chrono::duration<double, std::milli>(t_2 - t_1).count() , std::chrono::duration<double, std::milli>(t_3 - t_2).count());			
	}
	system("rm std.out test.out");
	return 0;
}
