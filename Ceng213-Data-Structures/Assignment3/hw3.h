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
	/*cout overloading
	std::ostream &operator<<( std::ostream &out, const std::pair<int, int> &p ) {
         out << p.first << " " << p.second;
         return out; }*/

	// Table1 std::pair<string, string>, contain the usernames and passwords(OLD/NEW) of the registered users.
	// Table2 string to string, contain usernames of the active(logged in) users.
	// next empty cell refers to the index that hash function returns when called with incremented i.	
	// when resizing table, also update occupied cells 
	// We can add new users in deleted entries
public:
	AccessControl(int table1Size, int table2Size); // Initialize tables with <“EMPTY”, “EMPTY”> and “EMPTY respectively.
	~AccessControl();

	int addUser(std::string username, std::string pass);    // add to registered users if not registered.Return 1 or 0
	int addUsers(std::string filePath); // return the number of users registered from ﬁle
	int delUser(std::string username, std::vector<std::string>& oldPasswords); // The oldest password comes first in the oldPasswords list.
	int changePass(std::string username, std::string oldpass, std::string newpass);

	int login(std::string username, std::string pass);  	// active users
	int logout(std::string username);

	float printActiveUsers();
	float printPasswords();
private:
	std::vector< std::pair<std::string, std::string> > regUsers;
	std::vector< std::string > activeUsers;
	int hashFunction(std::string key, int tableSize, int i);

	int table1Size;
	int table2Size;
	int occupied1;
	int occupied2;
	std::vector<int> allPassIndex;
	std::vector<std::string> allPassString;

	bool setAllPassword(std::string key);
	float loadFactor(int selectTable);
	bool isPrime(int a);
	int leastPrime(int a);
	void resize(int selectTable);
	std::string getValue(std::string key, int selectTable, std::string passDate = "old");
	
};

#endif