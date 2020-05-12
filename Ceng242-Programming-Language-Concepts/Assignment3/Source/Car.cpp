#include "Car.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Car::Car(std::string driver_name){
    //head = new Laptime();
    setDriverName(driver_name);
    setPerformance();
    setHead(NULL);
    setTail(NULL);
    setNext(NULL);
}
Car::Car(const Car& rhs){
   *this = rhs;
}
Car::~Car(){
    clearLaptimeLL();
}
std::string Car::getDriverName() const{
    return driver_name;
}
double Car::getPerformance() const{
    return performance;
}
void Car::addCar(Car *next){ //FIXME:dogru mu emin degilim
    setNext(next);
}
bool Car::operator<(const Car& rhs) const{
    return (getTotalLaptime() < rhs.getTotalLaptime());
}
bool Car::operator>(const Car& rhs) const{
    return (getTotalLaptime() > rhs.getTotalLaptime());
}
Laptime Car::operator[](const int lap) const{
    Laptime* myHead = getHead();
    for(int i = 0; myHead;i++){
        if(i == lap) return *myHead;
        myHead = myHead->getNext();
    }
    Laptime notFound; //FIXME: hatali olabilir
    return notFound;

}
void Car::Lap(const Laptime& average_laptime){ //FIXME: laptime olarak ne ekleyecegiz?
    int LaptimeVariance = Utilizer::generateLaptimeVariance(getPerformance());
    int parameterLaptime = average_laptime.getLaptime();
    parameterLaptime += LaptimeVariance;
    pushBackLaptime(parameterLaptime);
    //average_laptime.setLaptime(parameterLaptime); //FIXME:nereye ekleyecegiz?

}
std::ostream& operator<<(std::ostream& os, const Car& car){
    int i = 0;
    std::string dash = "--";
    std::string sur = car.getDriverName();
    char s0,s1,s2;
    for(i; sur[i] != ' '; i++);i++;
    if(97 <= sur[i] && sur[i  ] <= 122) s0 = sur[i  ]-32;
    else s0 = sur[i  ];
    if(97 <= sur[i+1] && sur[i+1] <= 122) s1 = sur[i+1]-32;
    else s1 = sur[i+1];
    if(97 <= sur[i+2] && sur[i+2] <= 122) s2 = sur[i+2]-32;
    else s2 = sur[i+2];

    os << s0 << s1 << s2 << dash << *(car.getTail()) << dash << car.getFastestLaptime() << dash << car.getTotalLaptime();// << std::endl;
    return os;
}

////////////////////////////////////////////////////////////

Car::Car(){
    setPerformance();
    setHead(NULL);
    setTail(NULL);
    setNext(NULL);
}
Car& Car::operator=(const Car& rhs){
    if (this != &rhs){
        setHead(NULL);
        setTail(NULL);        
        this->performance = rhs.getPerformance();
        setDriverName(rhs.getDriverName());
        setNext(rhs.getNext());       
        clearLaptimeLL();       
        const Laptime* rhead = rhs.getHead();
        while(rhead)
        {            
            pushBackLaptime(rhead->getLaptime());
            rhead = rhead->getNext();   
        }
        //std::cout << getNumberOfLaps() << std::endl; 
        
    }
    return *this;
}
Laptime * Car::getHead() const{
    return head;
}
void Car::setHead(Laptime* newHead){
    this->head = newHead;
}
Laptime * Car::getTail() const{
    return tail;
}
void Car::setTail(Laptime* newTail){
    this->tail = newTail;

}
void Car::setPerformance(){
    performance = Utilizer::generatePerformance();

}
void Car::setNext(Car * newNext){
    next = newNext;
}
Car * Car::getNext() const{
    return next;
}
void Car::setDriverName(std::string name){
    driver_name = name;
}
void Car::clearLaptimeLL(){
    Laptime* temp = getHead(), * temp2;
    if(!temp) return;
    while(getHead()) popBackLaptime();
    
}
void  Car::pushBackLaptime(const int& laptime){
    Laptime* newLaptime = new Laptime(laptime);
    if(!getHead()){
        setHead(newLaptime);
        setTail(newLaptime);
    }
    else{        
        tail->setNext(newLaptime);
        setTail(newLaptime);
    }
}
void  Car::popBackLaptime(){
    Laptime* myHead = getHead();
    Laptime* myTail = getTail();
    if(!myHead) return;
    if(myHead == myTail) {
        delete myHead;
        setHead(NULL);
        setTail(NULL);
        return;
    }
    while(myHead->getNext() != myTail){
        myHead = myHead->getNext();
    }    
    delete myHead->getNext();
    myHead->setNext(NULL);
    setTail(myHead);
}
Laptime Car::getTotalLaptime() const{ //FIXME: dynamic mi olmasi lazim?
    Laptime* myHead = getHead(), result;
    while(myHead){
        result + *myHead;
        myHead = myHead->getNext();
    }
    return result;
}
Laptime Car::getFastestLaptime() const{ //FIXME: dynamic mi olmasi lazim?
    Laptime* myHead = getHead(), max;
    while(myHead){
        if(*myHead > max) max = *myHead;
        myHead = myHead->getNext();
    }
    return max;
}
int Car::getNumberOfLaps() const{
    Laptime* temp = getHead();
    if(!temp) return 0;
    int i = 1;
    while(temp != getTail()){
        temp = temp->getNext();
        i++;
    }
    return i;

}