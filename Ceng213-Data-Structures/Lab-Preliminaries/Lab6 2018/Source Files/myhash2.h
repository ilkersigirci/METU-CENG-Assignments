#include <iostream>
#include <string>
#include <vector>   
#include <utility> 

using namespace std;

class MyHash
{
public: 

	MyHash( int table_size);
	void insert(const std::string &key, int val );
	int get(const std::string &key) const;
	void printTable() const;

private:
	int hash(const string & key) const;
	vector< std::pair<std::string, int> > table;
	int tableSize;

};

MyHash::MyHash(int table_size)
{
	table.resize(table_size);
	this->tableSize=table_size;
}

void MyHash::printTable() const
{
	cout<<"index \t key \tvalue"<<endl;
	for (int i=0;i<table.size();i++)
	{
		if (table[i].first=="") cout<<i<<":\t"<<"Empty ,\tEmpty"<<endl;
			else cout<<i<<":\t"<<table[i].first + " ,\t"<<table[i].second<<endl;
	}
}

int MyHash::hash(const string &key) const
{
	//COPY& PASTE YOUR IMPLEMENTED CODE IN TASK-1
}


void MyHash::insert(const std::string &key, int val )
{
	//IMPLEMENT HERE,  insert function for quadratic probing.
}

int MyHash::get(const std::string &key) const
{
	//IMPLEMENT HERE,  get function for quadratic probing.
}




