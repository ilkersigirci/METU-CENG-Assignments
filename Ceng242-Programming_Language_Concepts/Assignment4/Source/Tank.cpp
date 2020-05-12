#include"Tank.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Tank::Tank(uint id,int x, int y, Team team) : Player(id, x, y, team){setHP(1000);}
int Tank::getAttackDamage() const{return 25;}
int Tank::getHealPower() const{ return 0;}
int Tank::getMaxHP() const{return 1000;}
std::vector<Goal> Tank::getGoalPriorityList(){ return {TO_ENEMY,ATTACK,CHEST};}
const std::string Tank::getClassAbbreviation() const{
    if(this->getTeam() == BARBARIANS) return "TA";
    else return "ta";
}
std::vector<Coordinate> Tank::getAttackableCoordinates(){
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
std::vector<Coordinate> Tank::getMoveableCoordinates(){
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
std::vector<Coordinate> Tank::getHealableCoordinates(){ return {};}
