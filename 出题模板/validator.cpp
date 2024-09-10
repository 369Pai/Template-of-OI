#include "bits/stdc++.h"
#include "unistd.h"
using namespace std;
typedef long long ll;
ifstream fin;
void Check(int task)
{

}
int main()
{
	string name = "";
	for(int task = 1 ; task <=  ; task++)
	{
		for(int cs = 1 ; ; cs++)
		{
			string str = name + to_string(task) + "-" + to_string(cs);
			if(access((str + ".in").c_str() , F_OK) != 0)break ;
			cerr << "Task " << task << " #" << cs << "\n";
			fin.open((str + ".in").c_str());
			Check(task);
			fin.close();
		}
	}
	return 0;
}
