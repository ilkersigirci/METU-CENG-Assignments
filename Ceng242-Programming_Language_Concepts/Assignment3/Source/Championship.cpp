#include "Championship.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/
Championship::Championship(){
}
Championship::Championship(const Championship& rhs){
    if(this != &rhs){
        races.clear();
        for (int i=0; i<rhs.races.size(); i++) //Deep copied
        races.push_back(rhs.races[i]); 
    }
}

Championship::~Championship(){
    for(int i = 0; i < races.size(); i++) delete races[i];
    //races.clear();
}

void Championship::addNewRace(Race& race){ //FIXME: dynamic olmasi mi lazim?
    Race* newRace = new Race("noRaceName");
    *newRace = race;
    races.push_back(newRace);
    totalNameScore();
    orderScore();
}

void Championship::addNewRace(std::string race_name){ //TODO: getAverageLaptime falan ne alaka?
    
    Race* newRace = new Race(*(races[0]));
    //newRace->setAverageLaptime(races[0]->getAverageLaptime().getLaptime());
    newRace->setAverageLaptime();
    newRace->setRaceName(race_name);
    races.push_back(newRace);
    totalNameScore();
    orderScore();
}

void Championship::removeRace(std::string race_name){
    int index = findRaceIndex(race_name);
    delete races[index];
    races.erase(races.begin() + index);
    totalNameScore();
    orderScore();
}

void Championship::addLap(std::string race_name){
    int index = findRaceIndex(race_name);
    ++(*(races[index]));
    totalNameScore();
    orderScore();
}   

Race& Championship::operator[](std::string race_name){
    int index = findRaceIndex(race_name);    
    return *(races[index]);
}

std::ostream& operator<<(std::ostream& os, const Championship& championship){
    if(championship.races.size() == 0) return os;
    Car* car0 = championship.races.front()->getHead();
    int carNum = 0;

    while(car0){
        carNum++;
        car0 = car0->getNext();
    }
    if(carNum == 0) return os;
    std::string dash = "--";

    for(int i = 0;i < carNum;i++){
        os << championship.padding(i+1) << dash << championship.upperLastName(championship.totalName[i]) << dash << championship.totalScore[i] << std::endl;
    }

    return os;
}

/////////////////////////////////////////////////////////

int Championship::findRaceIndex(std::string raceName){
    
    if(races.size() == 0) return -1;
    //Race * current = races.front();
    for(int i = 0;i < races.size();i++){
        if(races[i]->getRaceName() == raceName) return i;    
    }
}

int Championship::padding(int num) const{
    int carNum = 0;
    Car* temp = races[0]->getHead();
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
    return num;
}

void Championship::totalNameScore(){    
    if(races.size() == 0) return;
    int driverIndex;
    int carNum = races.front()->getNumberOfCarsinRace();
    if(carNum == 0) return;
    Race * currentRace;
    std::string driverName;

    Race* race0 = races.front();
    for(int i = 0;i < carNum;i++){
        totalName[i] = race0->name[i];
        totalScore[i] = 0;
    }

    for(int i = 0; i < carNum; i++){
        driverName = totalName[i];

        for(int j = 0;j < races.size();j++){
            currentRace = races[j];            
            driverIndex = currentRace->getDriverIndex(driverName);
            totalScore[i] += currentRace->score[driverIndex];            
        }
           
    }
}
std::string Championship::upperLastName(std::string driverName) const{
    int i = 0;
    std::string dash = "--";
    std::string sur = driverName;
    if(driverName == "") return "";
    char s0,s1,s2;
    std::string result = "000";
    for(i; sur[i] != ' '; i++);i++;
    if(97 <= sur[i] && sur[i  ] <= 122) s0 = sur[i  ]-32;
    else s0 = sur[i  ];
    if(97 <= sur[i+1] && sur[i+1] <= 122) s1 = sur[i+1]-32;
    else s1 = sur[i+1];
    if(97 <= sur[i+2] && sur[i+2] <= 122) s2 = sur[i+2]-32;
    else s2 = sur[i+2];
    
    result[0] = s0;result[1] = s1;result[2] = s2;
    
    return result;
}
void Championship::orderScore(){
    if(races.size() == 0) return;
    int carNum = races.front()->getNumberOfCarsinRace();
    if(carNum == 0) return;
    int flag = 1,tempScore;
    std::string tempName;


    for(int i = 1; (i <= carNum) && flag; i++)
    {
        flag = 0;
        for (int j = 0; j < (carNum -1); j++)
        {
            if (totalScore[j+1] > totalScore[j])
            { 
                tempScore = totalScore[j];
                totalScore[j] = totalScore[j+1];
                totalScore[j+1] = tempScore;

                tempName = totalName[j];
                totalName[j] = totalName[j+1];
                totalName[j+1] = tempName;
                flag = 1;
            }
        }
    }
}
