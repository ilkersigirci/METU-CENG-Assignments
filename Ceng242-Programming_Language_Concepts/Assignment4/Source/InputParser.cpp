#include"InputParser.h"
#include <sstream>
#include <string>
#include <vector>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

/*
6                        -> board size
3 3                      -> coordinates of chest
29                       -> maximum turn number
2                        -> # players
ID of the player, class of the player, team of the player, x coordinate, y coordinate
12 ARCHER BARBARIAN 3 5 
11 FIGHTER KNIGHT 1 1

@returns Pointer to the Dynamically allocated Game object
* 
* Game(uint maxTurnNumber, uint boardSize, Coordinate chest);
* void addPlayer(int id, int x, int y, Team team, std::string cls);
*/

Game* InputParser::parseGame(){ //FIXME: destructor olacak mi?
    std::string line;
    std::vector<std::string> result;
    while(std::getline(std::cin, line)){        
        std::istringstream iss(line);
        for(std::string s; iss >> s;) result.push_back(s);            
    }
    int boardSize = std::stoi(result[0]);
    Coordinate chestCoord(std::stoi(result[1]), std::stoi(result[2]));
    int maxTurnNum = std::stoi(result[3]);
    int numPlayers = std::stoi(result[4]);
    int id,x,y;
    Team team;
    std::string tempTeam;
    std::string cls;
    Game* game = new Game(maxTurnNum, boardSize, chestCoord);
    for(int i = 0; i < numPlayers;i++){
        id = std::stoi(result[5*i+5]);
        cls  = result[5*i+6];
        tempTeam = result[5*i+7];
        x  = std::stoi(result[5*i+8]);
        y  = std::stoi(result[5*i+9]);
        if(tempTeam == "BARBARIAN") team = BARBARIANS;
        else if(tempTeam == "KNIGHT") team = KNIGHTS;
        game->addPlayer(id,x,y,team,cls);
    }
    return game;
}
