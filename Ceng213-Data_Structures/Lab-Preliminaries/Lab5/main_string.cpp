#include "tree.hpp"

#include <iostream>
#include <string>

using namespace std;
/*
 *  Return number of common characters 
 *  in two strings str1 and str2
 *  using Tree data structure
 *
 */

std::string
buildCharacterCountTree(const std::string & s,
                        Tree<char, size_t> & tree)
{
  std::string unique_keys;

  for(int i = 0; i < s.size(); ++i){
    try { 
        tree.find(s[i]);
        tree.modify(s[i],tree.find(s[i]) + 1);
    } catch (ItemNotFound e) {
      tree.insert(s[i], 1);
      unique_keys += s[i];
    }
  }
  return unique_keys;
}

size_t
commonCharacterCount(const std::string & inp1,
                     const std::string & inp2)
{
  Tree<char, size_t> x1, x2;
  string a1,a2;
  size_t result = 0;
  
  
  a1 = buildCharacterCountTree(inp1,x1);
  a2 = buildCharacterCountTree(inp2,x2);
  for(int i = 0; i < a1.size(); ++i){
    try {
      x1.find(a1[i]);
      try{
        x2.find(a1[i]);
        result += min(x1.find(a1[i]), x2.find(a1[i]));
        continue;
      }
      catch(ItemNotFound e) {
        continue;
      }
    }
    catch (ItemNotFound e){
      continue;
    }
  }
  return result;
}
                            

int main(void)
{
  Tree<char, size_t> occurrences1, occurrences2;
  std::string inp1("ankaraaaa"), inp2("adiyaman");
  std::string keys1, keys2;
  
  keys1 = buildCharacterCountTree(inp1, occurrences1);
  keys2 = buildCharacterCountTree(inp2, occurrences2);

  std::cout << occurrences1 << std::endl;
  std::cout << occurrences2 << std::endl;

  //unique characters in each string
  std::cout << keys1 << " " << keys2 << "\n" << std::endl;

  std::cout << "Number of common character occurrences between "
            << inp1 << " and " << inp2 << " is "
            << commonCharacterCount(inp1, inp2) 
            << "." << std::endl;
  
  return 0;
}
