#include "hw3.h"
#include <math.h>

int AccessControl::hashFunction(std::string key, int tableSize, int i)
{
    int length = key.length();
    int newK = 0;
    for (int i = 0; i < length; i++) newK += (int) key[i];
        // hash function 1 -> (newK % tableSize)
        // hash function 2 -> (newK * tableSize - 1) % tableSize)
    return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
}
bool AccessControl::setAllPassword(std::string key)
{
    allPassIndex.clear();
    allPassString.clear();
    
    int hashVal = 0;
    bool result = false;

    for(int i = 0; i<table1Size; i++)
    {
        hashVal = hashFunction(key, this->table1Size, i);
        if(regUsers[hashVal].first == key) 
        {
            result = true;
            allPassIndex.push_back(i);
            allPassString.push_back(regUsers[hashVal].second);
        }
    }
    return result;
}
float AccessControl::loadFactor(int selectTable)
{
    if(selectTable == 1) return occupied1 / float(table1Size);
    else return occupied2 / float(table2Size);
}
bool AccessControl::isPrime(int a)
{
    if(a < 2) return false;
    int root = sqrt(a);
    for (int i = 2; i <= root; i++)
    {
        if (a % i == 0) return false;
    }
    return true;
}
int AccessControl::leastPrime(int a)
{
    int result = a * 2 + 1;
    while(!isPrime(result)) result++;
    return result;
}
void AccessControl::resize(int selectTable)
{
    int newSize;
    std::string username;
    if(selectTable == 1)
    {
        newSize = leastPrime(regUsers.size());  
        std::string password;
        std::vector<std::string> tempPass;
        std::vector< std::pair<std::string, std::string> > temp = regUsers;
        regUsers.clear();       
        regUsers.resize(newSize);
        this->table1Size = newSize;
        occupied1 = 0;
        for(int i = 0; i < newSize; i++)
        {
            regUsers[i].first = EMPTY;
            regUsers[i].second = EMPTY;
        }

        for(int i = 0; i < temp.size(); i++)
        {
            if(temp[i].first == EMPTY || temp[i].first == DELETED) continue;

            username = temp[i].first;
            //setAllPassword on temp
            allPassIndex.clear();
            allPassString.clear();            
            int hashVal = 0;
            for(int j = 0; j<temp.size(); j++)
            {
                hashVal = hashFunction(username, temp.size(), j);
                if(temp[hashVal].first == username) 
                {
                    allPassIndex.push_back(j);
                    allPassString.push_back(temp[hashVal].second);
                }
            }
            tempPass = allPassString;
            password = tempPass.front();
            addUser(username, password);
            for(int j = 1; j < tempPass.size(); j++)
            {
                changePass(username, password, tempPass[j]);
                password = tempPass[j];       
            }
            
            //delUser(username, tempPass); tempten siliyor
            for(int j = 0; j < temp.size(); j++)
            {
                if(temp[j].first == username)
                {
                    temp[j].first = DELETED;
                    temp[j].second = DELETED;
                }              
            } 
        }
    }

    else
    {
        newSize = leastPrime(activeUsers.size()); 
        std::vector< std::string > temp = activeUsers;       
        activeUsers.clear();       
        activeUsers.resize(newSize, EMPTY);
        this->table2Size = newSize;
        occupied2 = 0;
        std::string myPass; 

        for(int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == EMPTY || temp[i] == DELETED) continue;
            username = temp[i];
            myPass = getValue(username, 1, "new");
            login(username, myPass);

            //logout(username); tempden silindi
            for(int j = 0; j < temp.size(); j++)
            {
                if(temp[j] == username) temp[j] = DELETED;
            
            }
        }        
    }
}
std::string AccessControl::getValue(std::string key, int selectTable, std::string passDate)
{
    int hashVal = 0;

    if(selectTable == 1)
    {
        bool val = setAllPassword(key);
        if(val == false) return "";
        if(passDate == "old") return allPassString.front();
        if(passDate == "new") return allPassString.back();

    }

	else
    {
        for(int i = 0; i<table2Size; i++)
        {
            hashVal = hashFunction(key, this->table2Size, i);
            if(activeUsers[hashVal] == key) return activeUsers[hashVal];
        }
    }
    return "";
}

/******************************************************************************************************/

AccessControl::AccessControl(int table1Size, int table2Size)
{
    regUsers.resize(table1Size);
    activeUsers.resize(table2Size, EMPTY);
	this->table1Size = table1Size;
	this->table2Size = table2Size;
    occupied1 = 0;
    occupied2 = 0;

    for(int i = 0; i < table1Size; i++)
    {
        regUsers[i].first = EMPTY;
        regUsers[i].second = EMPTY;
    }
}
AccessControl::~AccessControl() 
{
}
int AccessControl::addUser(std::string username, std::string pass)
{
    if(loadFactor(1) > MAX_LOAD_FACTOR) return 0;
    if(getValue(username, 1, "old") == "")
    {
        for(int i = 0; i < this->table1Size; i++)
        {
            int hashVal = hashFunction(username, this->table1Size, i);
            if(regUsers[hashVal].first == EMPTY || regUsers[hashVal].first == DELETED)
            {
                regUsers[hashVal].first = username;
                regUsers[hashVal].second = pass;
                occupied1++;

                if(loadFactor(1) > MAX_LOAD_FACTOR) resize(1);

                return 1;
            }
        }
    }
    return 0;
}
int AccessControl::addUsers(std::string filePath)
{
    std::ifstream infile;
    infile.open(filePath.c_str());
    std::string userName,password;
    int  i = 0;
    while(infile >> userName >> password)
    {
        i += addUser(userName, password);
    }
    return i;
}
int AccessControl::delUser(std::string username, std::vector<std::string>& oldPasswords) //FIXME: activeden silinmesi test edilmeyecekmis
{
    bool val = setAllPassword(username);
    if(val == false) return 0;
    oldPasswords = allPassString;

    for(int i = 0; i < this->table1Size; i++)
    {
        if(regUsers[i].first == username)
        {
            regUsers[i].first = DELETED;
            regUsers[i].second = DELETED;
            occupied1--;
        }              
    }            
    return 1;
}
int AccessControl::changePass(std::string username, std::string oldpass, std::string newpass)
{
    int hashVal = 0;
    if(loadFactor(1) > MAX_LOAD_FACTOR) return 0;
    std::string pass = getValue(username, 1, "new");
    if(pass == "" || pass != oldpass) return 0;

    for(int i = 0; i < this->table1Size; i++)
        {
            hashVal = hashFunction(username, this->table1Size, i);
            if(regUsers[hashVal].first == EMPTY || regUsers[hashVal].first == DELETED)
            {
                regUsers[hashVal].first = username;
                regUsers[hashVal].second = newpass;
                occupied1++;
                if(loadFactor(1) > MAX_LOAD_FACTOR) resize(1);

                return 1;
            }
        }
    return 0;
}
int AccessControl::login(std::string username, std::string pass)
{
    if(loadFactor(2) > MAX_LOAD_FACTOR) return 0;
    std::string myPass = getValue(username, 1, "new");
    if(myPass == "" || myPass != pass) return 0;    
    if(getValue(username, 2) != "") return 0;

    for(int i = 0; i < this->table2Size; i++)
    {
        int hashVal = hashFunction(username, this->table2Size, i);
        if(activeUsers[hashVal] == EMPTY || activeUsers[hashVal] == DELETED)
        {
            activeUsers[hashVal] = username;
            occupied2++;

            if(loadFactor(2) > MAX_LOAD_FACTOR) resize(2);

            return 1;
        }
    }
    return 0;
}
int AccessControl::logout(std::string username)
{        
    if(getValue(username, 2) == "") return 0;

    for(int i = 0; i < this->table2Size; i++)
    {
        int hashVal = hashFunction(username, this->table2Size, i);
        if(activeUsers[hashVal] == username)
        {
            activeUsers[hashVal] = DELETED;
            occupied2--;

            return 1;
        }
    }
    return 0;
}
float AccessControl::printActiveUsers()
{
    for(int i = 0; i < this->table2Size; i++)
    {
        std::cout << activeUsers[i] << std::endl;
    }

    return loadFactor(2);
}
float AccessControl::printPasswords()
{
    for(int i = 0; i < this->table1Size; i++)
    {
        std::cout << regUsers[i].first << " " << regUsers[i].second << std::endl;
    }

    return loadFactor(1);
}