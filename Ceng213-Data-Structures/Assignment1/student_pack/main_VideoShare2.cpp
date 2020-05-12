//g++ main_VideoShare.cpp VideoShare.cpp Video.cpp User.cpp  -o VideoShare -g
//valgrind --leak-check=full -v ./main
//valgrind --leak-check=full --log-file="logfile.out" -v ./VideoShare

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "VideoShare.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    VideoShare vs1 = VideoShare();
    vs1.loadUsers("listUser10.txt");
    vs1.loadVideos("listVideo10.txt");

    /* vs1.printAllUsers();
    vs1.printAllVideos(); */

    vs1.addFriendship("userName284", "userName392");
    vs1.addFriendship("userName284", "userName163");
    vs1.addFriendship("userName284", "userName265");
    
    vs1.addFriendship("userName061", "userName392");
    vs1.addFriendship("userName061", "userName265");

    /* cout << "Friends  of userName284" << endl;
    vs1.printFriendsOfUser("userName284");   */  
/* 
    vs1.subscribe("userName341", "title061");
    vs1.subscribe("userName341", "title051");
    vs1.subscribe("userName341", "title384");  */
    
    vs1.subscribe("userName392", "title353");
    vs1.subscribe("userName392", "title384");
    vs1.subscribe("userName392", "title343");
    vs1.subscribe("userName392", "title061");
    vs1.subscribe("userName392", "title051");

    vs1.subscribe("userName265", "title051");
    vs1.subscribe("userName265", "title311");
    vs1.subscribe("userName265", "title061");
    vs1.subscribe("userName265", "title384");
    vs1.subscribe("userName265", "title061");
    vs1.subscribe("userName265", "title051");
    
    vs1.subscribe("userName163", "title353");
    vs1.subscribe("userName163", "title109");
    vs1.subscribe("userName163", "title061");
    vs1.subscribe("userName163", "title384");
    vs1.subscribe("userName163", "title051");
    
    /* vs1.sortUserSubscriptions("userName341");
    vs1.sortUserSubscriptions("userName392");
    vs1.sortUserSubscriptions("userName265");

    cout << "Subscriptions of 341,392,265" << endl;
    vs1.printUserSubscriptions("userName163");
    vs1.printUserSubscriptions("userName392"); 
    vs1.printUserSubscriptions("userName265");  */

    cout << "/****************************************************/" << endl;
    cout << "Friends  of userName284" << endl;
    vs1.printFriendsOfUser("userName284");
    cout << "UserName284's friends all subs" << endl;    
    vs1.printFriendSubscriptions("userName284");
    
    cout<<"END OF TESTS.."<<endl;

    cout << vs1.isConnected("userName163","userName061");

    return 0;
}