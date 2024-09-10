#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
ll Random(ll l , ll r){return rnd() % (r - l + 1) + l;}
ofstream fout;
void MakeData(int task)
{
	fout << flush;
}
int main()
{
	string name = "";
	for(int task = 1 ; task <=  ; task++)
	{
		for(int cs = 1 ; cs <=  ; cs++)
		{
			string str = name + to_string(task) + "-" + to_string(cs);
			fout.open((str + ".in").c_str());
			MakeData(task);
			fout.close();
			string op = "cat ./" + (str + ".in") + " | ./std > ./" + (str + ".out");
			printf("%s\n" , op.c_str());
			system(op.c_str());
		}		
	}
	return 0;
}
