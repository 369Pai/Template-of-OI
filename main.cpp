#include "bits/stdc++.h"
using namespace std;
mt19937_64 rnd(time(NULL));
ofstream fout;
ll Random(ll l , ll r){return ll(rnd % (r - l + 1)) + l;}
void MakeData(int cs)
{
	fout << flush;
}
int main()
{
	srand(time(NULL));
	int tp = 1 , L = 1 , R = 10;
	string name = "";
	if(tp == 1)
	{
		for(int cs = L ; cs <= R ; cs++)
		{
			string str = name + to_string(cs);
			fout.open((str + ".in").c_str());
			MakeData(cs);
			fout.close();
			string op = "cat ./" + (str + ".in") + " | ./std > ./" + (str + ".out");
			printf("%s\n" , op.c_str());
			system(op.c_str());
		}		
	}
	else
	{
		for(int cs = L ; cs <= R ; cs++)
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
			if (system("diff -w std.out test.out"))
			{
				printf("Wrong Answer\n");
				return 0;
			}
			else printf("Accepted std: %lfms test: %lfms\n" , std::chrono::duration<double, std::milli>(t_2 - t_1).count() , std::chrono::duration<double, std::milli>(t_3 - t_2).count());			
		}
	}
	return 0;
}