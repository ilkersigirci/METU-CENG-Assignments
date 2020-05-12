#include"Priest.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Priest::Priest(uint id,int x, int y, Team team) : Player(id, x, y, team){setHP(150);}
int Priest::getAttackDamage() const{return 0;}
int Priest::getHealPower() const{ return 50;}
int Priest::getMaxHP() const{return 150;}
std::vector<Goal> Priest::getGoalPriorityList(){ return {HEAL,TO_ALLY,CHEST};}
const std::string Priest::getClassAbbreviation() const{
    if(this->getTeam() == BARBARIANS) return "PR";
    else return "pr";
}
std::vector<Coordinate> Priest::getAttackableCoordinates(){ return {};}
std::vector<Coordinate> Priest::getMoveableCoordinates(){
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
std::vector<Coordinate> Priest::getHealableCoordinates(){
	Coordinate myCoord = getCoord();
    std::vector<Coordinate> healable;
    for(int i = -1; i <= 1; i++){ // horizontal first
        if(i == 0) continue;
        Coordinate coord1(i,0);
        healable.push_back(myCoord+coord1);
    }
    for(int i = -1; i <= 1; i++){
        if(i == 0) continue;
        Coordinate coord1(0,i);
        Coordinate coord2(i,i);
        Coordinate coord3(i,-i);
        healable.push_back(myCoord+coord1);
        healable.push_back(myCoord+coord2);
		healable.push_back(myCoord+coord3);
    }                               
    return healable;
}
