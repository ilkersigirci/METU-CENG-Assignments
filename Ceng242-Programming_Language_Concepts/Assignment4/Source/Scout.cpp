#include"Scout.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Scout::Scout(uint id,int x, int y, Team team) : Player(id, x, y, team){setHP(125);}
int Scout::getAttackDamage() const{return 25;}
int Scout::getHealPower() const{ return 0;}
int Scout::getMaxHP() const{return 125;}
std::vector<Goal> Scout::getGoalPriorityList(){ return {CHEST,TO_ALLY,ATTACK};}
const std::string Scout::getClassAbbreviation() const{
    if(this->getTeam() == BARBARIANS) return "SC";
    else return "sc";
}
std::vector<Coordinate> Scout::getAttackableCoordinates(){
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
        Coordinate coord2(i,i);
        Coordinate coord3(i,-i);
        attackable.push_back(myCoord+coord1);
        attackable.push_back(myCoord+coord2);
		attackable.push_back(myCoord+coord3);
    }                               
    return attackable;
}
std::vector<Coordinate> Scout::getMoveableCoordinates(){
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
        Coordinate coord2(i,i);
        Coordinate coord3(i,-i);
        moveable.push_back(myCoord+coord1);
        moveable.push_back(myCoord+coord2);
		moveable.push_back(myCoord+coord3);
    }                               
    return moveable;
}
std::vector<Coordinate> Scout::getHealableCoordinates(){ return {};}
