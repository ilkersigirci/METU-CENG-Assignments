#include"Archer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Archer::Archer(uint id,int x, int y, Team team) : Player(id, x, y, team){setHP(200);}
int Archer::getAttackDamage() const{return 50;}
int Archer::getHealPower() const{ return 0;}
int Archer::getMaxHP() const{return 200;}
std::vector<Goal> Archer::getGoalPriorityList(){
    std::vector<Goal> priority = {ATTACK};
    return priority;
}
const std::string Archer::getClassAbbreviation() const{
    if(this->getTeam() == BARBARIANS) return "AR";
    else return "ar";
}
std::vector<Coordinate> Archer::getAttackableCoordinates(){
    Coordinate myCoord = getCoord();
    std::vector<Coordinate> attackable;
    for(int i = -2; i <= 2; i++){ // horizontal first
        if(i == 0) continue;
        Coordinate coord1(i,0);
        attackable.push_back(myCoord+coord1);
    }
    for(int i = -2; i <= 2; i++){
        if(i == 0) continue;
        Coordinate coord1(0,i);
        attackable.push_back(myCoord+coord1);
    }                               
    return attackable;
}
std::vector<Coordinate> Archer::getMoveableCoordinates(){ return {};}
std::vector<Coordinate> Archer::getHealableCoordinates(){ return {};}
