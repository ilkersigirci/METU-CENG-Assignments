#include"Game.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Game::Game(uint maxTurnNumber, uint boardSize, Coordinate chest) : board(Board(boardSize,&players,chest)){
	turnNumber = 1;
	this->maxTurnNumber = maxTurnNumber;	
}
Game::~Game(){
	for(Player* player : players) delete player;
	players.clear();
}
void Game::addPlayer(int id, int x, int y, Team team, std::string cls){
	int i = 0;
	Player* player;
	if     (cls == "ARCHER" ) player = new Archer(id,x,y,team);
	else if(cls == "FIGHTER") player = new Fighter(id,x,y,team);
	else if(cls == "PRIEST" ) player = new Priest(id,x,y,team);
	else if(cls == "SCOUT"  ) player = new Scout(id,x,y,team);
	else if(cls == "TANK"   ) player = new Tank(id,x,y,team);
	//players.push_back(player);	
	for(Player* temp : players){
		if(id > temp->getID()) i++;		
	}
	players.insert(players.begin()+i, player);
}
bool Game::isGameEnded(){
	Coordinate chestCoord = board.getChestCoordinates();
	int tempTurn = turnNumber - 1; //FIXME: dogru mu
	int barbarianNum = 0, knightNum = 0;
	if (tempTurn == maxTurnNumber){
		std::cout << "Game ended at turn "<< maxTurnNumber << ". Maximum turn number reached. Knight victory." << std::endl;
		return true;
	}
	for(Player* player : players){
		if (player->getTeam() == BARBARIANS){
			barbarianNum++;
			if(player->getCoord() == chestCoord){
				std::cout << "Game ended at turn "<< tempTurn << ". Chest captured. Barbarian victory." << std::endl;
				return true;
			}
		}
		else if (player->getTeam() == KNIGHTS) knightNum++;
	}
	if(barbarianNum == 0){
		std::cout << "Game ended at turn "<< tempTurn << ". All barbarians dead. Knight victory." << std::endl;
		return true;
	}
	if(knightNum == 0){
		std::cout << "Game ended at turn "<< tempTurn << ". All knights dead. Barbarian victory." << std::endl;
		return true;
	}	
	return false;
}
void Game::playTurn(){
	std::cout << "Turn " << turnNumber << " has started." << std::endl;
	std::vector<Player*> tempPlayers;
	for(Player *player : players) tempPlayers.push_back(player);
	for(Player *player : tempPlayers){
		if(player) playTurnForPlayer(player);
	} 
	turnNumber++;
}
Goal Game::playTurnForPlayer(Player* player){
	if(player->isDead()){
		removePlayer(player);
		std::cout << "Player " << player->getBoardID() << " has died." << std::endl;
		return NO_GOAL;
	}
	std::vector<Goal> priority = player->getGoalPriorityList();
	for(Goal goal : priority){
		if(goal == NO_GOAL) return NO_GOAL;
		else if(goal == ATTACK){
			std::vector<Coordinate> attackable = player->getAttackableCoordinates();
			std::vector<Player *> enemies;
			for(Coordinate coord : attackable){
				Player* tempPlayer = board[coord];
				if(tempPlayer != nullptr && tempPlayer->getTeam() != player->getTeam()) enemies.push_back(tempPlayer);
			}
			if(enemies.size() == 0) continue;
			Player* lowestPlayer = enemies[0];
			for(Player* p : enemies){
				int currID = p->getID();
				if(lowestPlayer->getID() > currID) lowestPlayer = p;
			}
			player->attack(lowestPlayer);
			return ATTACK;
		}
		else if(goal == HEAL){
			std::vector<Coordinate> healable = player->getHealableCoordinates();
			std::vector<Player *> allies;
			for(Coordinate coord : healable){
				Player* tempPlayer = board[coord];
				if(tempPlayer != nullptr && tempPlayer->getTeam() == player->getTeam()){
					allies.push_back(tempPlayer);
					player->heal(tempPlayer);
				} 
			}
			if(allies.size() == 0) continue;
			return HEAL;
		}
		else{ //MOVE
			std::vector<Coordinate> moveable = player->getMoveableCoordinates();
			std::vector<Coordinate> validMove;
			std::vector<Player*> enemies;
			std::vector<Player*> allies;
			std::vector<int> distances;
			int distance = 0, index = 0;			
			Coordinate playerCoord = player->getCoord();
			for(Coordinate c : moveable){ // set valid moves
				if(board.isPlayerOnCoordinate(c) || !board.isCoordinateInBoard(c)) continue;
				validMove.push_back(c);
			}
			if(validMove.size() == 0) continue;
			for(Player* singlePlayer : players){ // set enemies and allies
				if(singlePlayer == player || singlePlayer == nullptr) continue;
				if(singlePlayer->getTeam() != player->getTeam()) enemies.push_back(singlePlayer);
				else allies.push_back(singlePlayer);
			}
			if(goal == CHEST){		
				Coordinate chestCoord = board.getChestCoordinates();				
				if(playerCoord == chestCoord) continue;
				int currentDistance = chestCoord - playerCoord;
				Coordinate moveCoord = whereToMove(validMove, chestCoord);					
				if(moveCoord.x == -10) continue;
				int resultDistance = moveCoord - chestCoord;
				if(resultDistance >= currentDistance) continue;
				player->movePlayerToCoordinate(moveCoord);
				return CHEST;
			}			
			else if(goal == TO_ENEMY){
				int flag = 0, distance;				
				std::vector<int> closestDistances;
				if(enemies.size() == 0) continue;
				for(Coordinate c : moveable){ //If an enemy is in the squares that the player can move
					for(Player* singleEnemy : enemies){
						if(singleEnemy->getCoord() == c){
							flag = 1;
							break;
						} 
					}
					if(flag) break;
				}
				if(flag) continue;
				for(Player* p : enemies){ //set enemy distances
					distance = playerCoord - p->getCoord();
					distances.push_back(distance);
				}
				Coordinate closestEnemy = getClosestCoord(player,distances,enemies);
				int currentDistance = closestEnemy - playerCoord;
				Coordinate moveCoord = whereToMove(validMove, closestEnemy);
				if(moveCoord.x == -10) continue;
				int resultDistance = moveCoord - closestEnemy;
				if(resultDistance >= currentDistance) continue;
				player->movePlayerToCoordinate(moveCoord);
				return TO_ENEMY;
			}
			else if(goal == TO_ALLY){
				int flag = 0, distance;				
				std::vector<int> closestDistances;
				if(allies.size() == 0) continue;
				for(Coordinate c : moveable){ //If an enemy is in the squares that the player can move
					for(Player* singleAlly : allies){
						if(singleAlly->getCoord() == c){
							flag = 1;
							break;
						} 
					}
					if(flag) break;
				}
				if(flag) continue;
				for(Player* p : allies){ //set enemy distances
					distance = playerCoord - p->getCoord();
					distances.push_back(distance);
				}
				Coordinate closestAlly = getClosestCoord(player,distances,allies);
				int currentDistance = closestAlly - playerCoord;
				Coordinate moveCoord = whereToMove(validMove, closestAlly);
				if(moveCoord.x == -10) continue;
				int resultDistance = moveCoord - closestAlly;
				if(resultDistance >= currentDistance) continue;
				player->movePlayerToCoordinate(moveCoord);
				return TO_ALLY;
			}
		}
		
	}
	return NO_GOAL;	
}
////////////////////////////////////////////////////
const Board& Game::getBoard() const{return board;}
void  Game::removePlayer(Player *player){
	int i = 0;
	for(std::vector<Player*>::iterator it (players.begin()); it != players.end(); it++){
		if(*it == player){
			delete players[i];
			players.erase(it);
			break;
		}
		i++;
	}
}

Coordinate Game::getClosestCoord(Player* player, std::vector<int> distances, std::vector<Player*> myPlayers){
	int distance = distances[0], index = 0;
	for(int i = 0; i < distances.size(); i++){
		if(distance == distances[i]){
			if((myPlayers[index]->getID() > myPlayers[i]->getID())){ //lowestID
				distance = distances[i];
				index = i;
			}
		}
		else if(distance > distances[i]){
			distance = distances[i];
			index = i;
		}
	}
	return myPlayers[index]->getCoord();
}
Coordinate Game::whereToMove(std::vector<Coordinate> validMove,Coordinate c){
	int distance = validMove[0] - c;
	int index = 0;
	int tempDistance, minDistance = validMove[0] - c;
	for(Coordinate curr : validMove){
		tempDistance = curr - c;
		if(minDistance > tempDistance) minDistance = tempDistance;
	}
	//std::cout << "minDistance "<<minDistance << std::endl;
	for(Coordinate curr : validMove){
		tempDistance = curr - c;
		if(tempDistance == minDistance) return curr;
	}
	return Coordinate(-10,-10);
}