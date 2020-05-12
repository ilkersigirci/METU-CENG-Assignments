void VideoShare::printFriendSubscriptions(const string & userName) // TODO: eksik basma hatasini cozme
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
}


/* SON CALISAN*/


void VideoShare::printFriendSubscriptions(const string & userName) // TODO: duplicate basmayi coz
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
   /*  if(UserFriends->getLength()==1)  // 1 tane friend olma durumu
    {
        if(!(UserFriend->getSubscriptions()->first())) return;  // 1 friend with no subs
        //this->sortingAllFriendSubs(UserFriend->getSubscriptions()); // eski sort
        this->AllFriendSubs=*(UserFriend->getSubscriptions()); // sorting
        int size=AllFriendSubs.getLength(); // sorting
        if(size==1) return; // sorting
        this->bubbleSort(&(AllFriendSubs),size); // sorting
        // FIXME: duplicate eleme yap
        this->AllFriendSubs.print();  //1 friend with subs
        return;
    }    */ 
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
    this->AllFriendSubs.print();
}