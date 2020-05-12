#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */


VideoShare::VideoShare()
{
}
VideoShare::~VideoShare()
{
}
User* VideoShare::getUsernameNodePtr(const string & userName)
{
    Node<User> * head=users.first();
    User * user=head->getDataPtr();
    while(head)
    {
        if(user->getUsername()==userName) return user;
        head=head->getNext();
        user=head->getDataPtr();
    }
    return NULL;
}
Video * VideoShare::getVideotitleNodePtr(const string & title)
{
    Node<Video> * head=videos.first();
    Video * video=head->getDataPtr();
    while(head)
    {
        if(video->getTitle()==title) return video;
        head=head->getNext();
        video=head->getDataPtr();
    }
    return NULL;
}
void VideoShare::createUser(const string & userName, const string & name, const string & surname)
{
    if(userName=="") return;
    User newUser(userName,name,surname);
    Node<User> * head=users.getHead();
    users.insertNode(head,newUser);
}
void VideoShare::loadUsers(const string & fileName)
{
    ifstream infile;
    infile.open(fileName.c_str());
    string line;
    string userName,name,surname;
    int position=0;
    char semicolon=';';
    Node<User> * head=users.getHead();

    while (getline(infile, line))
    {               
        position=line.find(semicolon);
        if(position==0) continue;        
        string userName=line.substr(0,position);
        line.erase(0,position+1);
        
        position=line.find(semicolon);
        if(position==0)
        {
            line.erase(0,position+1);
            if(line.empty())
            {
                this->createUser(userName);
            }
            else
            {            
                string surname=line;
                this->createUser(userName,"",surname);           
            }            
        }
        else
        {
            string name=line.substr(0,position);
            line.erase(0,position+1);
            if(line.empty())
            {  
                this->createUser(userName,name);
            }
            else
            {
                string surname=line;
                this->createUser(userName,name,surname);                                
            }
        }       
    }  
}    
void VideoShare::createVideo(const string & title, const string & genre)
{
    if(title=="") return;
    Video newVideo(title,genre);
    Node<Video> * head=videos.getHead();
    videos.insertNode(head,newVideo);
}
void VideoShare::loadVideos(const string & fileName)  // SORUN createVideo(title);
{
    ifstream infile;
    infile.open(fileName.c_str());
    string line;
    int position=0;
    char semicolon=';';
    Node<Video> * head=videos.getHead();
    while (getline(infile, line))
    {               
        position=line.find(semicolon);
        if(position==0) continue;        
        string title=line.substr(0,position);
        line.erase(0,position+1);
        if(line.empty())
        {            
            Video newVideo(title);
            videos.insertNode(head,newVideo);
            //this->createVideo(title);
        }
        else
        {
            string genre=line;            
          /*Video newVideo(title,genre);
            videos.insertNode(head,newVideo);*/
            this->createVideo(title,genre);
        }
    }
}
void VideoShare::addFriendship(const string & userName1, const string & userName2)
{
    User * user1=getUsernameNodePtr(userName1);  
    User * user2=getUsernameNodePtr(userName2);
    if(!user1 || !user2) return;
    user1->addFriend(user2);
    user2->addFriend(user1);

}
void VideoShare::removeFriendship(const string & userName1, const string & userName2)
{
    User * user1=getUsernameNodePtr(userName1);
    User * user2=getUsernameNodePtr(userName2);
    if(!user1 || !user2) return;  
    user1->removeFriend(user2);
    user2->removeFriend(user1);
}
void VideoShare::updateUserStatus(const string & userName, Status newStatus)
{
    User * user=getUsernameNodePtr(userName);
    if(!user) return;
    user->updateStatus(newStatus);
}
void VideoShare::subscribe(const string & userName, const string & videoTitle)
{
    User * user=getUsernameNodePtr(userName);
    Video * video=getVideotitleNodePtr(videoTitle);
    if(!user || !video) return;
    if(user->getStatus()==SUSPENDED) return;
    user->subscribe(video);
    
}
void VideoShare::unSubscribe(const string & userName, const string & videoTitle)
{
    User * user=getUsernameNodePtr(userName);
    Video * video=getVideotitleNodePtr(videoTitle);
    if(!user || !video) return;
    if(user->getStatus()==SUSPENDED) return;
    user->unSubscribe(video);

}
void VideoShare::deleteUser(const string & userName) // FIXME:
{
    User * user=getUsernameNodePtr(userName);
    if(!user) return;
    Node<User> * UserPrevNode=users.findPrev(*user);    
    LinkedList< User* > * UserFriends=user->getFriends();
    Node<User*> * head=UserFriends->first();
    while(head)
    {
        User * friendData=head->getData();
        friendData->removeFriend(user);      
        head=head->getNext();
        
    }    
    users.deleteNode(UserPrevNode);

}
string VideoShare::getIndexTitle(LinkedList< Video* > * UserSubs,int index)
{
    Node<Video*> * head=UserSubs->first();
    int i=0;
    while((i<index) && head)
    {
        
        head=head->getNext();
        i++;
    }
    string videoTitle=head->getData()->getTitle();
    return videoTitle;
}
void VideoShare::bubbleSort(LinkedList< Video* > * UserSubs,int size)
{    
    Node<Video*> * head=UserSubs->first();    
    bool sorted = false ;
    for ( int i = 0; ( i < size-1) && !sorted; i++) 
    {
        sorted = true;
        for ( int j=1; j <= size-i-1; j++)
        {
            if (this->getIndexTitle(UserSubs,j-1) > this->getIndexTitle(UserSubs,j) ) 
            {                
                UserSubs->swap(j,j-1);
                sorted = false ;    
            }
        }
    }
}
void VideoShare::sortUserSubscriptions(const string & userName)
{
    User * user=getUsernameNodePtr(userName);
    if(!user) return;       
    LinkedList< Video* > * UserSubs=user->getSubscriptions();
    int size=UserSubs->getLength(); // 1 den basliyor
    if(size==1) return;
    this->bubbleSort(UserSubs,size);    
}
void VideoShare::printUserSubscriptions(const string & userName)
{
    User * user=getUsernameNodePtr(userName);
    if(!user) return;        
    user->printSubscriptions();
}
void VideoShare::printFriendsOfUser(const string & userName)
{
    User * user=getUsernameNodePtr(userName);
    if(!user) return;        
    user->printFriends();
}
void VideoShare::printCommonSubscriptions(const string & userName1, const string & userName2) // TODO: endl ekle
{
    User * user1=getUsernameNodePtr(userName1);
    User * user2=getUsernameNodePtr(userName2);
    if(!user1 || !user2) return;
    
    LinkedList< Video* > * UserSubs1=user1->getSubscriptions();
    LinkedList< Video* > * UserSubs2=user2->getSubscriptions();
    Node<Video*> * head1=UserSubs1->first();
    Node<Video*> * head2=UserSubs2->first();
    Node<Video*> * temp=head2;
    for(;head1;head1=head1->getNext())
    {
        Video * videoPtr1=head1->getData();        
        for(;temp;temp=temp->getNext())
        {
            Video * videoPtr2=temp->getData();
            if((*videoPtr1)==(*videoPtr2))
            {                
                cout << *videoPtr1 << endl;  
                break;
            }
        }
        temp=head2;        
    }

}
string VideoShare::getIndexTitle(LinkedList< Video> * AllFriendSubs,int index)  //OVERLOADED
{
    Node<Video> * head=AllFriendSubs->first();
    int i=0;
    while((i<index) && head)
    {
        
        head=head->getNext();
        i++;
    }
    string videoTitle=head->getData().getTitle();
    return videoTitle;
}
void VideoShare::bubbleSort(LinkedList< Video> * AllFriendSubs,int size)  //OVERLOADED
{    
    Node<Video> * head=AllFriendSubs->first();    
    bool sorted = false ;
    for ( int i = 0; ( i < size-1) && !sorted; i++) 
    {
        sorted = true;
        for ( int j=1; j <= size-i-1; j++)
        {
            if (this->getIndexTitle(AllFriendSubs,j-1) > this->getIndexTitle(AllFriendSubs,j) ) 
            {                
                AllFriendSubs->swap(j,j-1);
                sorted = false ;    
            }
        }
    }
}
void VideoShare::printFriendSubscriptions(const string & userName)
{
    User * user=getUsernameNodePtr(userName); 
    LinkedList< User* > * UserFriends=user->getFriends();
    if(UserFriends->getLength()==0) return;   // Userin friendi olmama durumu
    Node<User*> * UserFriendHead=UserFriends->first();
    User * UserFriend=UserFriendHead->getData();
    LinkedList<Video *> * UserFriendSubs;
    Node<Video*> * UserFriendSubsHead;
    Node<Video> * AllFriendSubsHead=this->AllFriendSubs.getHead();
    Node<Video> * allFirst=this->AllFriendSubs.first();
    while(UserFriendHead)
    {
        UserFriend=UserFriendHead->getData();
        UserFriendSubs=UserFriend->getSubscriptions();
        UserFriendSubsHead=UserFriendSubs->getHead();
        if(!(UserFriendSubsHead->getNext()))  // Friendin subsi olmama durumu
        {
            UserFriendHead=UserFriendHead->getNext();
            continue;            
        }
        UserFriendSubsHead=UserFriendSubsHead->getNext();
        while(UserFriendSubsHead)
        {
            Video newVideo=*(UserFriendSubsHead->getData());
            this->AllFriendSubs.insertNode(AllFriendSubsHead,newVideo);
            UserFriendSubsHead=UserFriendSubsHead->getNext();
        }
        UserFriendHead=UserFriendHead->getNext();        
    }
    int size=AllFriendSubs.getLength();
    if(size==1) return;
    this->bubbleSort(&(AllFriendSubs),size);
    //this->AllFriendSubs.print();
    allFirst=this->AllFriendSubs.first();
    while(allFirst->getNext())  // duplicate elimination
    {
        if(allFirst->getData()==allFirst->getNext()->getData()){}
        else
        {
            cout << allFirst->getData();
        }
        allFirst=allFirst->getNext();
    }
    cout << allFirst->getData() << endl;
}
bool VideoShare::isConnected(const string & userName1, const string & userName2)
{
    User * user1=getUsernameNodePtr(userName1); 
    User * user2=getUsernameNodePtr(userName2); 

    LinkedList< User* > * UserFriends=user1->getFriends();
    Node<User*> * UserFriendHead=UserFriends->first();
    return this->findConnection(user1,user2,Friends);
}

bool VideoShare::findConnection(User * user1,User * user2,LinkedList<User*> &Friends)
{
    if((Friends.findNode(user1))) return false;
    Node<User*> * UserFriendHead=user1->getFriends()->first();
    Node<User*> * FriendsHead=Friends.getHead();
    if(user1->getUsername()==user2->getUsername()) return true;
    Friends.insertNode(FriendsHead,user1);
    //if(!(user1->getFriends()->findNode(user2))) {cout << "FIST"<< endl;return false;}    
    while(UserFriendHead)
    {
        if(findConnection(UserFriendHead->getData(),user2,Friends)) return true;
        UserFriendHead=UserFriendHead->getNext();
    }
    cout << "LAST" << endl;
    return false;    

}
/*void VideoShare::printFriendSubscriptions(const string & userName)
{
    User * user=getUsernameNodePtr(userName); 
    LinkedList< User* > * UserFriends=user->getFriends();
    if(UserFriends->getLength()==0) return;   // Userin friendi olmama durumu
    Node<User*> * UserFriendHead=UserFriends->first();
    User * UserFriend=UserFriendHead->getData();
    if(UserFriends->getLength()==1)  // 1 tane friend olma durumu
    {
        if(!(UserFriend->getSubscriptions()->first())) return;  // 1 friend with no subs
        this->sortingFirstFriendSubs(UserFriend->getSubscriptions());
        this->sortedFirstFriendSubs.print();  //1 friend with subs
        return;
    }
    Node<User*> * SecondFriendHead=UserFriendHead->getNext();
    Node<User*> * Temp_SecondFriendHead=SecondFriendHead;  
    this->sortingFirstFriendSubs(UserFriend->getSubscriptions());   
    Node< Video* > * SortedFirstFriendSubsHead=this->sortedFirstFriendSubs.getHead();
    Node<Video*> * SecondFriendSubsHead;
    int FriendNoSubsCheck;
    int OneFriendCheck;
    
    if(!(SortedFirstFriendSubsHead->getNext())) return;  // Ilk friendin subsi olmama durumu
    SortedFirstFriendSubsHead=SortedFirstFriendSubsHead->getNext();
    while(SortedFirstFriendSubsHead)   //en az iki friend var
    {
        bool all=false;
        Video FriendVideo=*(SortedFirstFriendSubsHead->getData());
        while(Temp_SecondFriendHead)
        {
            FriendNoSubsCheck=Temp_SecondFriendHead->getData()->getSubscriptions()->getLength();
            if(FriendNoSubsCheck==0) return;
            SecondFriendSubsHead=Temp_SecondFriendHead->getData()->getSubscriptions()->first();
            all=false;
            while(SecondFriendSubsHead)
            {               
                if(FriendVideo==*(SecondFriendSubsHead->getData()))
                {
                    all=true;
                    break;
                }

                SecondFriendSubsHead=SecondFriendSubsHead->getNext();
            }
            if(!all) break;
            Temp_SecondFriendHead=Temp_SecondFriendHead->getNext();
        }
        if(all){cout << FriendVideo;}
        Temp_SecondFriendHead=SecondFriendHead;
        SortedFirstFriendSubsHead=SortedFirstFriendSubsHead->getNext();      
    }
}*/