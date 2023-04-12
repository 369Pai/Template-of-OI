#include "bits/stdc++.h"
using namespace std;
mt19937_64 rnd(time(NULL));
FILE *fout;
//ofstream fout;
void MakeData(int cs)
{
	//use fprintf(fout , "" , ...);
	//or use fout << 
	fprintf(fout , "%d\n" , cs);
	fflush(fout);
	//fout << flush;
}
int main()
{
	//only on Windows
	srand(time(NULL));
	int tp = 0;
	string name = "a";
	cout << "input op:";
	cin >> tp;
	if(tp == 1)
	{
		for(int cs = 1 ; cs <= 10 ; cs++)
		{
			string str = name + to_string(cs);
			fout = fopen((str + ".in").c_str(),"w");
			//fout.open((str + ".in").c_str());
			MakeData(cs); fclose(fout);
			//fout.close();
			string op = "std.exe<" + (str + ".in") + ">" + (str + ".out");
			printf("%s\n" , op.c_str());
			system(op.c_str());
		}		
	}
	else
	{
		for(int cs = 1 ; cs <= 10 ; cs++)
		{
			string str = name + to_string(cs);
			string op1 = "std.exe<" + (str + ".in") + ">" + "std.out";
			printf("%s\n" , op1.c_str());	
			auto t_1 = chrono::high_resolution_clock::now();
			system(op1.c_str());
			auto t_2 = chrono::high_resolution_clock::now();
			string op2 = "test.exe<" + (str + ".in") + ">" + "test.out";
			printf("%s\n" , op2.c_str());
			system(op2.c_str());
			auto t_3 = chrono::high_resolution_clock::now();
			if (system("fc std.out test.out"))
			{
				printf("Wrong Answer\n");
				return 0;
			}
			else printf("Accepted std: %lfms test: %lfms\n" , std::chrono::duration<double, std::milli>(t_2 - t_1).count() , std::chrono::duration<double, std::milli>(t_3 - t_2).count());			
		}
	}
	return 0;
}
