#include"Game.h"
#include"InputParser.h"
#include<iostream>


int main(){

  // g++ -std=c++11 main.cpp Laptime.cpp  Car.cpp Race.cpp Championship.cpp -o Test -ggdb3
  // valgrind --log-file="test.txt" ./Test
  
  //valgrind --leak-check=full ./testGame < ./gameInputs/case3.inp > ./gameOutputs/my3.out

  Game *game = InputParser::parseGame();
  Board *board = game->getBoard();
  std::cout << "Board with ID" << std::endl;
  board->printBoardwithClass();
  std::cout << "Board with ID" << std::endl;
  board->printBoardwithID();
  while(!game->isGameEnded()){
    game->playTurn();
    board->printBoardwithClass();
    std::cout << "--------------" << std::endl;
    board->printBoardwithID();


  }
}
