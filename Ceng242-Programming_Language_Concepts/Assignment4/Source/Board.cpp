#include"Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Board::Board(uint _size, std::vector<Player*>* _players, Coordinate chest) : chest(chest){
    this->size = _size;
    this->players = _players;
}
Board::~Board(){}
bool Board::isCoordinateInBoard(const Coordinate& c){
    if( (c.x >= 0 && c.x < getBoardSize()) && (c.y >= 0 && c.y < getBoardSize()) ) return true;
	else return false;
}
bool Board::isPlayerOnCoordinate(const Coordinate& c){
    if(isCoordinateInBoard(c) == false) return false;
    for(Player *player : *players){
		if(player->getCoord() == c) return true;
	}
    return false;
}
Player* Board::operator [](const Coordinate& c){
	if(isCoordinateInBoard(c) == false) return nullptr;
    if(isPlayerOnCoordinate(c) == false) return nullptr;
	for(Player *player : *players){
		if(player->getCoord() == c) return player;
	}
	return nullptr;
}
Coordinate Board::getChestCoordinates(){ return chest;}
void Board::printBoardwithID(){printBoard(0);}
void Board::printBoardwithClass(){printBoard(1);}
//////////////////////////////////////////////
uint Board::getBoardSize(){ return size;}
void Board::printBoard(int select){
    for(uint y = 0; y < getBoardSize(); y++){
        for (uint x = 0; x < getBoardSize(); x++){
            Coordinate coord(x,y);
            Player* currentPlayer = (*this)[coord];
            std::string print;

            if(currentPlayer != nullptr ){ //&& currentPlayer->isDead() == false
                if(select == 0) print = currentPlayer->getBoardID();
                else print = currentPlayer->getClassAbbreviation();    
            }    
            else if (getChestCoordinates() == coord) print = "Ch";
            else print = "__";
            std::cout << print << " ";
            //if(x != getBoardSize()-1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}