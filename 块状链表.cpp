#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct Rope
{	
	typedef typename list<vector<T> >::iterator ptr;
	const static int sz = 23333;
	list<vector<T> >List;
	ptr Next(ptr x){return ++x;}
	ptr Find(int &x)
	{
		for(ptr i = List.begin() ; i != List.end() ; i++)
		{
			if(x <= i->size())
				return i;
			x -= i->size();
		}
		return List.begin();
	}
	void Merge(ptr x)
	{
		x->insert(x->end() , Next(x)->begin() , Next(x)->end());
		List.erase(Next(x));
	}
	void Split(ptr x , int pos)
	{
		if(pos == x->size())
			return ;
		List.insert(Next(x) , std::vector<char>(x->begin() + pos , x->end()));
		x->erase(x->begin() + pos , x->end());
	}
	void Update()
	{
		for(ptr i = List.begin() ; i != List.end() ; i++)
		{
			while(i->size() >= (sz << 1))
				Split(i , i->size() - sz);
			while(Next(i) != List.end() && i->size() + Next(i)->size() <= sz)
				Merge(i);
			while(Next(i) != List.end() && Next(i)->empty())
				List.erase(Next(i));
		}
	}
	void Insert(int pos , const std::vector<char>& ins)
	{
		ptr curr = Find(pos);
		if(!List.empty())
			Split(curr , pos);
		List.insert(Next(curr) , ins);
		Update();
	}
	void Erase(int l , int r)// [l ,r)
	{
		ptr L , R;
		L = Find(l) , Split(L , l);
		R = Find(r) , Split(R , r);//Attention the order
		for(++R ; Next(L) != R ; List.erase(Next(L)));
		Update();
	}
	void Output(int l , int r)
	{
		ptr L = Find(l) , R = Find(r);
		if(L == R)
			for(int i = l ; i < r ; i++)
				cout << L->at(i);
		else
		{
			for(int i = l ; i < L->size() ; i++)
				cout << L->at(i);
			for(++L ; L != R ; ++L)
				for(int i = 0 ; i < L->size() ; i++)
					cout << L->at(i);
			for(int i = 0 ; i < r ; i++)
				cout << R->at(i);
		}
		putchar('\n');
	}
};
int main()
{
	return 0;
}
