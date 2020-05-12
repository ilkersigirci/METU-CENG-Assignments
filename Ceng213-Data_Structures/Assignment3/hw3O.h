#ifndef _HW3_H
#define _HW3_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>  // use just for std::pair< >
#include <fstream>

#define MAX_LOAD_FACTOR 0.65
#define EMPTY "EMPTY"
#define DELETED "DELETED"


class AccessControl
{
public:
	AccessControl(int table1Size, int table2Size);
	~AccessControl();

	int addUser(std::string username, std::string pass);
	int addUsers(std::string filePath);
	int delUser(std::string username, std::vector<std::string>& oldPasswords);
	int changePass(std::string username, std::string oldpass, std::string newpass);

	int login(std::string username, std::string pass);
	int logout(std::string username);

	float printActiveUsers();
	float printPasswords();
private:
	//<<your hash class>> activeUsers;	// hash(username) -> username
	//<<your hash class>> regUsers;  		// hash(username) -> username,password

	int hashFunction(std::string key, int tableSize, int i) {
	   int length = key.length();
	   int newK = 0;
	   for (int j = 0; j < length; j++)
	     newK += (int) key[j];

		 // hash function 1 -> (newK % tableSize)
		 // hash function 2 -> (newK * tableSize - 1) % tableSize)

	   return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}
	std::pair<std::string, std::string> *regUsers;
	std::string *activeUsers;
	int table1Size;
	int table2Size;
	int n1; //number of entries in regUsers table
	int n2; //number of entries in activeUsers table
	int isUserRegistered(std::string& username);
	bool isPrime(int n) const;
	int nextPrimeAfter(int n) const;
	void expandTable1();
	void expandTable2();
	int addLogin(std::string username);
	int isUserLoggedIn(std::string& username);
	float getLoadFactor1() const;
	float getLoadFactor2() const;
	std::string currentPassword(std::string username);
	int insert(std::string username, std::string pass);
};

#endif
