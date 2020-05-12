#include "hw3O.h"

AccessControl::AccessControl(int table1Size, int table2Size){
	int i;
	this->table1Size = table1Size;
	this->table2Size = table2Size;
	regUsers = new std::pair<std::string, std::string> [table1Size];
	activeUsers = new std::string [table2Size];
	for(i=0; i<table1Size; i++){
		regUsers[i].first = EMPTY;
		regUsers[i].second = EMPTY;
	}
	for(i=0; i<table2Size; i++)
		activeUsers[i] = EMPTY;
	n1=0;
	n2=0;
}

AccessControl::~AccessControl(){
	delete [] regUsers;
	delete [] activeUsers;
}

int AccessControl::isUserRegistered(std::string& username){
	int i, index;
	for(i=0; i<table1Size; i++){
		index = hashFunction(username, table1Size, i);
		if(regUsers[index].first == EMPTY)
			break;
		if(regUsers[index].first == username)
			return index;
	}
	return -1;
}

int AccessControl::addUser(std::string username, std::string pass){
	if(isUserRegistered(username) == -1){
		int check = insert(username, pass);
		if(getLoadFactor1() > MAX_LOAD_FACTOR) expandTable1();
		return check;
	}
	return 0;
}

int AccessControl::addUsers(std::string filePath){
	std::ifstream inStream;
	inStream.open(filePath.c_str());
	if(!inStream.good())
	{
	    return 0;
	}
	int count = 0;
	std::string username, password, line;
	size_t pos;
	while(getline(inStream, line))
	{
	    pos = line.find(" ");
	    username = line.substr(0,pos);
	    password = line.substr(pos+1);
	    if(addUser(username, password) == 1)
	    	count++;
	}
	inStream.close();
	return count;
}

int AccessControl::delUser(std::string username, std::vector<std::string>& oldPasswords){
	int index, i, flag = 0;
	for(i=0; i<table1Size; i++){
		index = hashFunction(username, table1Size, i);
		if(regUsers[index].first == EMPTY)
			break;
		if(regUsers[index].first == username){
			oldPasswords.push_back(regUsers[index].second);
			regUsers[index].first = DELETED;
			regUsers[index].second = DELETED;
			n1--;
			flag = 1;
		}
	}
	return flag;
}

float AccessControl::printActiveUsers(){
	for(int i=0; i<table2Size; i++){
		std::cout << activeUsers[i] << std::endl;
	}
	return ((float) n2 / table2Size);
}

float AccessControl::printPasswords(){
	for(int i=0; i<table1Size; i++){
		std::cout << regUsers[i].first << " " << regUsers[i].second << std::endl;
	}
	return ((float) n1 / table1Size);
}

bool AccessControl::isPrime(int n) const{
	if(n%2 == 0) return false;
    for(int i=3; i*i<=n; i+=2)
        if(n%i == 0)
            return false;
    return true;
}

int AccessControl::nextPrimeAfter(int n) const{
	for( int i=n+1; ; i++ )
        if(isPrime(i))
            return i;
}

void AccessControl::expandTable1(){
	std::string username;
    int i, j, oldIndex, newIndex;
    int oldSize = table1Size;
    int newSize = nextPrimeAfter(2 * table1Size);
    std::pair<std::string, std::string>* temp = new std::pair<std::string, std::string> [table1Size];
    for(i=0; i<table1Size; i++)
    {
        temp[i].first = regUsers[i].first;
        temp[i].second = regUsers[i].second;
    }
    delete [] regUsers;
    n1 = 0;
    table1Size = newSize;
    regUsers = new std::pair<std::string, std::string> [table1Size];
    for(i=0; i<table1Size; i++)
    {
        regUsers[i].first = EMPTY;
        regUsers[i].second = EMPTY;
    }
    for(i=0; i<oldSize; i++)
    {
        if(temp[i].first!=EMPTY && temp[i].first!=DELETED){
        	if(isUserRegistered(temp[i].first) == -1){
	        	username = temp[i].first;
	        	for(j=0; j<oldSize; j++){
	        		oldIndex = hashFunction(username, oldSize, j);
	        		if(temp[oldIndex].first == username)
	        			insert(temp[oldIndex].first, temp[oldIndex].second);
	        	}
	        }
        }
    }
    delete [] temp;
}

void AccessControl::expandTable2(){
    int i;
    int oldSize = table2Size;
    int newSize = nextPrimeAfter(2 * table2Size);
    std::string* temp = new std::string [table1Size];
    for(i=0; i<table2Size; i++)
    {
        temp[i] = activeUsers[i];
    }
    delete [] activeUsers;
    n2 = 0;
    table2Size = newSize;
    activeUsers = new std::string [table2Size];
    for(i=0; i<table2Size; i++)
    {
        activeUsers[i] = EMPTY;
    }
    for(i=0; i<oldSize; i++)
    {
        if(temp[i]!=EMPTY && temp[i]!=DELETED)
        	addLogin(temp[i]);
    }
    delete [] temp;
}

int AccessControl::addLogin(std::string username){
	if(isUserLoggedIn(username) == -1){
		int index;
		for(int i=0; i<table2Size; i++){
			index = hashFunction(username, table2Size, i);
			if(activeUsers[index] == EMPTY || activeUsers[index] == DELETED){
				activeUsers[index] = username;
				n2++;
				if(getLoadFactor2() > MAX_LOAD_FACTOR) expandTable2();
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

int AccessControl::isUserLoggedIn(std::string& username){
	int i, index;
	for(i=0; i<table2Size; i++){
		index = hashFunction(username, table2Size, i);
		if(activeUsers[index] == EMPTY)
			break;
		if(activeUsers[index] == username)
			return index;
	}
	return -1;
}

float AccessControl::getLoadFactor1() const{
	return ((float) n1 / table1Size);
}
	
float AccessControl::getLoadFactor2() const{
	return ((float) n2 / table2Size);
}

int AccessControl::logout(std::string username){
	int index = isUserLoggedIn(username);
	if(index != -1){
		activeUsers[index] = DELETED;
		n2--;
		return 1;
	}
	return 0;
}

int AccessControl::changePass(std::string username, std::string oldpass, std::string newpass){
	if(isUserRegistered(username) != -1 && oldpass == currentPassword(username)){
	    int index;
		for(int i=0; i<table1Size; i++){
		    index = hashFunction(username, table1Size, i);
			if(regUsers[index].first == EMPTY || regUsers[index].first == DELETED){
				regUsers[index].first = username;
				regUsers[index].second = newpass;
				n1++;
				if(getLoadFactor1() > MAX_LOAD_FACTOR) expandTable1();
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

int AccessControl::login(std::string username, std::string pass){
    int check = 0;
	if(isUserRegistered(username) != -1 && pass == currentPassword(username)){
		check = addLogin(username);
	}
	return check;
}

std::string AccessControl::currentPassword(std::string username){
	int index;
	std::string currPass;
	for(int i=0; i<table1Size; i++){
		index = hashFunction(username, table1Size, i);
		if(regUsers[index].first == username)
			currPass = regUsers[index].second;
	}
	return currPass;
}

int AccessControl::insert(std::string username, std::string pass){
	int index;
		for(int i=0; i<table1Size; i++){
			index = hashFunction(username, table1Size, i);
			if(regUsers[index].first == EMPTY || regUsers[index].first == DELETED){
				regUsers[index].first = username;
				regUsers[index].second = pass;
				n1++;
				return 1;
			}
		}
		return 0;
}