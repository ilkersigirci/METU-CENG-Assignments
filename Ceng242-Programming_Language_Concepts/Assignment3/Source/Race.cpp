#include "Race.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
int Race::randomCarNum = 0;

Race::Race(std::string race_name){
    setAverageLaptime();
    setRaceName(race_name);
    setHead(NULL);
    setTail(NULL);
}
Race::Race(const Race& rhs){ // clears laptime of cars
    if(this != &rhs){
        setHead(NULL);
        setTail(NULL); 
        setRaceName(rhs.getRaceName());
        average_laptime = rhs.average_laptime;
        clearCarLL();
        Car* rhead = rhs.getHead();
        while(rhead)
        {            
            pushBackCar(*rhead,1);
            rhead=rhead->getNext();
        }        
    }
}
Race::~Race(){
    clearCarLL();
}
std::string Race::getRaceName() const{
    return race_name;
}
void Race::addCartoRace(){ // FIXME: delete newCar'a bak
    //pushBack ile ayni
    std::string randomName = "randomCar";
    randomName += std::to_string(randomCarNum); randomCarNum++;
    Car* newCar = new Car(randomName);
    addCartoRace(*newCar);
    delete newCar;

}
void Race::addCartoRace(Car& car){ 
    pushBackCar(car, 0);

}
int Race::getNumberOfCarsinRace(){
    Car* temp = getHead();
    if(!temp) return 0;
    int i = 1;
    while(temp != getTail()){
        temp = temp->getNext();
        i++;
    }
    return i;

}
void Race::goBacktoLap(int lap){

    Car* carTemp = getHead();
    if(!carTemp) return;
    int totalLap = carTemp->getNumberOfLaps();
    Laptime* carLaptimeHead = carTemp->getHead();
    if(!carLaptimeHead) return;    
    int left = totalLap - lap - 1;

    while(left){
        operator--();
        left--;
    } 
    orderCars();
}
void Race::operator++(){
    int carNum = getNumberOfCarsinRace();
    Car* temp = getHead();
    if(!carNum) return;
    for(int i = 0; i<carNum;i++){
        temp->Lap(getAverageLaptime());
        temp = temp->getNext();
    }
    orderCars();
    setScore();
}
void Race::operator--(){
    int carNum = getNumberOfCarsinRace();
    Car* temp = getHead();
    if(!carNum || !temp->getHead()) return;
    for(int i = 0; i<carNum;i++){
        temp->popBackLaptime();
        if(!temp->getHead()) return;
        temp = temp->getNext();
    }
    orderCars();
    setScore();
}
Car Race::operator[](const int car_in_position){
    Car* myHead = getHead();
    for(int i = 0; myHead;i++){
        if(i == car_in_position) return *myHead;

        myHead = myHead->getNext();
    }
}
Car Race::operator[](std::string driver_name){
    Car* myHead = getHead();
    while(myHead){
        if(driver_name == myHead->getDriverName()) return *myHead;
        myHead = myHead->getNext();
    }

}
Race& Race::operator=(const Race& rhs){
    if(this != &rhs){
        setHead(NULL);
        setTail(NULL); 
        setRaceName(rhs.getRaceName());
        average_laptime = rhs.average_laptime;
        clearCarLL();
        Car* rhead = rhs.getHead();
        while(rhead)
        {            
            pushBackCar(*rhead,0);
            rhead=rhead->getNext();
        }
        int carNum = getNumberOfCarsinRace();
        for(int i = 0; i < carNum; i++){
            name[i] = rhs.name[i];
            score[i] = rhs.score[i];
        }    
    }
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Race& race){
    int i = 0;
    int fastestIndex = race.getFastestIndex();
    std::string dash = "--";
    //int score[] = {25,18,15,12,10,8,6,4,2,1};
    Car* tempHead = race.getHead();
    if(tempHead->getNumberOfLaps() == 0) return os;

    for(i = 0; tempHead; i++){
        os << race.padding(i+1) << dash << *tempHead << dash;
        if(i == fastestIndex && (0 <= i && i < 10)) os << race.score[i]-1 << dash << "1";
        else os << race.score[i];
        os << std::endl;
        tempHead = tempHead->getNext();
    }
    return os;
}
/////////////////////////////////////////////////////////////////////

void Race::setRaceName(std::string name){
    race_name = name;
}
Car * Race::getHead() const{
    return head;
}
void Race::setHead(Car* newHead){
    this->head = newHead;
}
Car * Race::getTail() const{
    return tail;
}
void Race::setTail(Car* newTail){
    this->tail = newTail;

}
Laptime Race::getAverageLaptime() const{
    return average_laptime;
}
void Race::setAverageLaptime(){    
    int averageLaptime = Utilizer::generateAverageLaptime();
    average_laptime.setLaptime(averageLaptime);
}
void Race::setAverageLaptime(int laptime){    
    
    average_laptime.setLaptime(laptime);
}
void Race::clearCarLL(){
    Car* temp = getHead(), * temp2;
    if(!temp) return;
    while(getHead()) popBackCar();
}
void  Race::pushBackCar(Car& car, int clearLaptime){ //FIXME: dynamic yaptim
    //Car newCar = car;
    Car* newCar = new Car();
    *newCar = car;
    if(clearLaptime) newCar->clearLaptimeLL();    

    if(!getHead()){
        setHead(newCar);
        setTail(newCar);
    }
    else{        
        tail->setNext(newCar);
        setTail(newCar);
    }
}
void  Race::popBackCar(){
    Car* myHead = getHead();
    Car* myTail = getTail();
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


void Race::swap(int index1, int index2){   

    if (index1 == index2) return;  

    int carNum = getNumberOfCarsinRace(); 
    Car *preCar1 = NULL, *curCar1 = getHead();
    Car *preCar2 = NULL, *curCar2 = getHead();
    Car *temp;

    for(int i = 0;i<index1;i++)
    {
        preCar1 = curCar1;  
        curCar1 = curCar1->getNext();  
    }
    if (curCar1 == NULL) return;
    for(int i = 0;i<index2;i++)
    {
        preCar2 = curCar2;  
        curCar2 = curCar2->getNext();  
    }
    if (curCar2 == NULL)  return;

    if (preCar1 != NULL)  preCar1->setNext(curCar2);         
    else setHead(curCar2);  
        
    if (preCar2 != NULL)  preCar2->setNext(curCar1);          
    else setHead(curCar1);

    if(index1+1 == carNum) setTail(curCar2);
    if(index2+1 == carNum) setTail(curCar1);

    temp = curCar1->getNext();  
    curCar1->setNext(curCar2->getNext());  
    curCar2->setNext(temp); 
}


void Race::orderCars(){

    int minIndex;
    Car* cur1 = getHead();
    Car* cur2 = getHead();

    for (int i = 0; i < getNumberOfCarsinRace()-1; i++) {

        minIndex = i;
        for (int j = i+1; j < getNumberOfCarsinRace(); j++) {
            //if(!cur2) return;
            if ((*this)[j] < (*this)[minIndex]) {
                minIndex = j;
            }
        }
        swap(minIndex, i);
    }          
}
void Race::setScore(){
    int i = 0;
    int fastestIndex = getFastestIndex();
    int tempScore[] = {25,18,15,12,10,8,6,4,2,1};
    Car* tempHead = getHead();
    if(tempHead->getNumberOfLaps() == 0) return;

    for(i = 0; tempHead; i++){

        name[i] = tempHead->getDriverName();
        score[i] = 0;
        if(0 <= i && i < 10){            
            if(i == fastestIndex) score[fastestIndex]++;
            score[i] += tempScore[i];
        }
        tempHead = tempHead->getNext();
    }
}

int Race::getFastestIndex() const{
    int i = 0,fastestIndex = -1,fastestLaptime = 1000000,laptime;
    Car* tempHead = getHead();
    if(tempHead->getNumberOfLaps() == 0) return -1;

    for(i = 0; tempHead; i++){
        laptime = tempHead->getFastestLaptime().getLaptime();
        if(laptime < fastestLaptime){
            fastestLaptime = laptime;
            fastestIndex = i;
        }
        tempHead = tempHead->getNext();
    }
    return fastestIndex;
}
int Race::padding(int num) const{
    int carNum = 0;
    Car* temp = getHead();
    int carNumDigit = 0, numDigit = 0, tempNum = num;

    while(temp){
        carNum++;
        temp = temp->getNext();
    }
    if(!carNum) return 0;
    while(carNum){
        carNum = carNum / 10;
        carNumDigit++;
    }
    while(tempNum){
        tempNum = tempNum / 10;
        numDigit++;
    }
    for(int i = 0; i < carNumDigit - numDigit; i++){
        std::cout << "0"; 
    }
    //std::cout << num;
    return num;
}

int Race::getDriverIndex(std::string driverName) const{
    int i = 0;
    Car* temp = getHead();

    for (i = 0; temp; i++){
        if(temp->getDriverName() == driverName) return i;

        temp = temp->getNext();
    }
    return -1;
}
