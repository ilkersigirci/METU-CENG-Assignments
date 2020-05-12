#include"Fighter.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Fighter::Fighter(uint id,int x, int y, Team team) : Player(id, x, y, team){setHP(400);}
int Fighter::getAttackDamage() const{return 100;}
int Fighter::getHealPower() const{ return 0;}
int Fighter::getMaxHP() const{return 400;}
std::vector<Goal> Fighter::getGoalPriorityList(){ return {ATTACK,TO_ENEMY,CHEST};}
const std::string Fighter::getClassAbbreviation() const{
    if(this->getTeam() == BARBARIANS) return "FI";
    else return "fi";
}
std::vector<Coordinate> Fighter::getAttackableCoordinates(){
    Coordinate myCoord = getCoord();
    std::vector<Coordinate> attackable;
    for(int i = -1; i <= 1; i++){ // horizontal first
        if(i == 0) continue;
        Coordinate coord1(i,0);
        attackable.push_back(myCoord+coord1);
    }
    for(int i = -1; i <= 1; i++){
        if(i == 0) continue;
        Coordinate coord1(0,i);
        attackable.push_back(myCoord+coord1);
    }                               
    return attackable;
}
std::vector<Coordinate> Fighter::getMoveableCoordinates(){
    Coordinate myCoord = getCoord();
    std::vector<Coordinate> moveable;
    for(int i = -1; i <= 1; i++){ // horizontal first
        if(i == 0) continue;
        Coordinate coord1(i,0);
        moveable.push_back(myCoord+coord1);
    }
    for(int i = -1; i <= 1; i++){
        if(i == 0) continue;
        Coordinate coord1(0,i);
        moveable.push_back(myCoord+coord1);
    }                               
    return moveable;
}
std::vector<Coordinate> Fighter::getHealableCoordinates(){ return {};}
