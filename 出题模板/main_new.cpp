#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
ll Random(ll l , ll r){return rnd() % (r - l + 1) + l;}
ofstream fout;
void MakeData(int cs)
{
	int task = 0;
	fout << flush;
}
int main()
{
	int tp = 1;
	string name = "";
	if(tp == 1)
	{
		for(int cs = 1 ; cs <= 20 ; cs++)
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
		system("./DP");
	}
	return 0;
}
