#include"Player.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Player::Player(uint id,int x, int y, Team team) : id(id), coordinate(Coordinate(x,y)){
    this->team = team;
}
//Player::~Player(){}
uint Player::getID() const{
    return id;
}
const Coordinate& Player::getCoord() const{
    return coordinate;
}
int Player::getHP() const{
    return HP;
}
void Player::setHP(int hp){
    this->HP = hp;
}
Team Player::getTeam() const{
    return team;
}
std::string Player::getBoardID(){
    uint myID = getID();
    std::string result = "";
    if(myID / 10 == 0) result += "0";
    std::string boardID = std::to_string(myID);
    result += boardID;
    return result;
}
bool Player::attack(Player *enemy){ //TODO: can eksiye dusecek mi?
    int attDam = getAttackDamage();
    int finalHP = enemy->getHP() - attDam;
    enemy->setHP(finalHP);
    std::string print = "Player " + getBoardID() + " attacked Player " + enemy->getBoardID() + " (" + std::to_string(attDam) + ")";
    std::cout << print << std::endl;
    return enemy->isDead();
}
void Player::heal(Player *ally){
    int healPow = getHealPower();
    int maxHP = ally->getMaxHP();
    int finalHP = ally->getHP() + healPow;
    if(finalHP >= maxHP) ally->setHP(maxHP);
    else ally->setHP(finalHP);
    std::string print = "Player " + getBoardID() + " healed Player " + ally->getBoardID();
    std::cout << print << std::endl;
}
void Player::movePlayerToCoordinate(Coordinate c){
    std::cout << "Player " << getBoardID() << " moved from " << getCoord() << " to " << c << std::endl;
    setCoord(c);
}
bool Player::isDead() const{
    if(getHP() > 0) return false;
    else return true;
}
void Player::setCoord(Coordinate coor){
    this->coordinate.x = coor.x;
    this->coordinate.y = coor.y;
}