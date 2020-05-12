#include "tree.hpp"

#include <iostream>

int main( )
{ 
  Tree<char, int> bst1;

  bst1.insert('a', 5);

  //basic runtime error management
  try { 
    std::cout << bst1.find('a') << std::endl;
  } catch (ItemNotFound e) {
    std::cerr << "Key \'a\' does not exist" << std::endl;
  }

  bst1.insert('a', 7);

  try {
    std::cout << bst1.find('a') << std::endl;
  } catch (ItemNotFound e) {
    std::cerr << "Key \'a\' does not exist" << std::endl;
  }

  bst1.insert('b', 8);

  try {
    std::cout << bst1.find('b') << std::endl;
  } catch (ItemNotFound e) {
    std::cerr << "Key \'b\' does not exist" << std::endl;
  }
  std::cout << bst1 << std::endl;  

  Tree<float, float> bst2;

  bst2.insert(6,6);
  bst2.insert(3,3);
  bst2.insert(8,8);
  bst2.insert(2,2);
  bst2.insert(5,5);
  bst2.insert(7,7);
  bst2.insert(13,13);
  bst2.insert(1,1);
  bst2.insert(27,27);
  bst2.modify(27,186);
  bst2.modify(8,452);

  std::cout << bst2 << std::endl;
  
  return 0;
}
