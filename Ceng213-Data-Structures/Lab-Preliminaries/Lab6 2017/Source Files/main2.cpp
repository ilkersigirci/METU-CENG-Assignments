#include "myhash2.h"

int main()
{

    MyHash a(7);

    a.insert("1",1);
    a.insert("2",2);
    a.insert("3",3);
    a.insert("8",8);
    a.printTable();
    
    //cout<<a.get("8")<<endl;
    
    return 0;
}
