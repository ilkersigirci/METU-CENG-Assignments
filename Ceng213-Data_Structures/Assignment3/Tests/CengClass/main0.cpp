#include "hw3.h"

using namespace std;

void inp1() {
    AccessControl ac1(1, 1);
    cout << "User Add: Sarah " << ac1.addUser("Sarah", "pass123") << endl;
    cout << "User Add: Sarah " << ac1.addUser("Sarah", "pass123") << endl;
    cout << "User Add: Sarah " << ac1.addUser("Sarah", "pass1234") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac1.printPasswords();

    cout << "User Add: Morgan " << ac1.addUser("Morgan", "morP4ssw0rd") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac1.printPasswords();

    cout << "User Add: BigMike " << ac1.addUser("BigMike", "mikesPassword") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac1.printPasswords();

    cout << "User Add: Jeff " << ac1.addUser("Jeff", "jeffsspassword") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac1.printPasswords();

    cout << "User Add: Lester " << ac1.addUser("Lester", "Lestersspassword") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac1.printPasswords();


    AccessControl ac2(4, 4);
    cout << "User Add: Sarah " << ac2.addUser("Sarah", "Sarahspass") << endl;
    cout << "User Add: Sarah " << ac2.addUser("Sarah", "pass1234") << endl;
    cout << "User Add: Morgan " << ac2.addUser("Morgan", "morganspass") << endl;
    cout << "User Add: Ellie " << ac2.addUser("Ellie", "elspassword") << endl;
    cout << "User Add: Vicky " << ac2.addUser("Vicky", "vickypass") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac2.printPasswords();

    cout << "User Add: Casey " << ac2.addUser("Casey", "caseysspassword") << endl;
    cout << "User Add: Casey " << ac2.addUser("Casey", "caseyssp4ssw0rd") << endl;
    cout << "User Add: Vale " << ac2.addUser("Vale", "valespass") << endl;
    cout << "User Add: Devon " << ac2.addUser("Devon", "devonspass") << endl;
    cout << "User Add: Chuck " << ac2.addUser("Chuck", "chuckspass") << endl;
    cout << "User Add: Orion " << ac2.addUser("Orion", "orionspass") << endl;
    cout << "User Add: Chuck " << ac2.addUser("Chuck", "chuckspass") << endl;
    cout << "User Add: Chuck " << ac2.addUser("Chuck", "chuckspass") << endl;
    cout << "User Add: Devon " << ac2.addUser("Devon", "devonspass") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac2.printPasswords();

    AccessControl ac3(3, 1);
    cout << "User Add: Sarah " << ac3.addUser("Sarah", "Sarahspass") << endl;
    cout << "User Add: Sarah " << ac3.addUser("Sarah", "sarspass") << endl;
    cout << "---------" << endl << "Passwords" << endl;
    ac3.printPasswords();


}

void inp2() {
    AccessControl ac(20, 3);
    cout << "User Add: Sarah " << ac.addUser("Sarah", "Sarahspass") << endl;
    cout << "User Add: Morgan " << ac.addUser("Morgan", "morganspass") << endl;
    cout << "User Add: Ellie " << ac.addUser("Ellie", "elspassword") << endl;
    cout << "User Add: Vicky " << ac.addUser("Vicky", "vickypass") << endl;
    cout << "User Add: Casey " << ac.addUser("Casey", "caseysspassword") << endl;
    cout << "User Add: Vale " << ac.addUser("Vale", "valespass") << endl;
    cout << "User Add: Devon " << ac.addUser("Devon", "devonspass") << endl;
    cout << "User Add: Chuck " << ac.addUser("Chuck", "chuckspass") << endl;
    cout << "User Add: Orion " << ac.addUser("Orion", "orionspass") << endl;
    cout << "User Add: BigMike " << ac.addUser("BigMike", "mikesPassword") << endl;
    cout << "User Add: Jeff " << ac.addUser("Jeff", "jeffsspassword") << endl;
    cout << "User Add: Lester " << ac.addUser("Lester", "Lestersspassword") << endl;

    cout << "Login: Chuck " << ac.login("Chuck", "chuckspass") << endl;
    cout << "Login: Chuck " << ac.login("Chuck", "wrong") << endl;
    cout << "Login: Morgan " << ac.login("Morgan", "wrong") << endl;
    cout << "Login: Morgan " << ac.login("Morgan", "morganspass") << endl;
    cout << "Login: Morgan " << ac.login("Morgan", "pass123") << endl;
    cout << "Login: Sarah " << ac.login("Sarah", "wrongpass") << endl;

    cout << "---------" << endl << "Active Users" << endl;
    ac.printActiveUsers();
    cout << endl;

    cout << "Login: Sarah " << ac.login("Sarah", "Sarahspass") << endl;
    cout << "Login: Sarah " << ac.login("Sarah", "Sarahspass") << endl;
    cout << "Login: Casey " << ac.login("Casey", "caseysspassword") << endl;
    cout << "Login: Orion " << ac.login("Orion", "orionspass") << endl;
    cout << "Login: Jefster " << ac.login("Jefster", "None") << endl;
    cout << "Login: BigMike " << ac.login("BigMike", "mikesPassword") << endl;
    cout << "Login: Jeff " << ac.login("Jeff", "jeffsspassword") << endl;
    cout << "Login: Lester " << ac.login("Lester", "Lestersspassword") << endl;

    cout << "---------" << endl << "Active Users" << endl;
    ac.printActiveUsers();
}

int main () {
    inp1();
    inp2();

    return 0;
}