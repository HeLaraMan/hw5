#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

//checks if formulated string is valid
bool isValid(std::string& s,  const std::set<std::string>& dict){
 return dict.find(s) != dict.end();
}

bool strContains(std::string str1, const std::string& str2){
 for(int i = 0; i < str2.length(); i++){
  size_t found = str1.find(str2[i]);
  if(found == std::string::npos){
    return false;
  }
  str1[found] = '-';
 }

  return true;
}

void wordGenerator(std::string& current, const std::string& fixed, const std::string& floating, std::string& floatingChars,
    const std::set<std::string>& dict, std::set<std::string>& wordSet, int pos, int empty){
      if(empty == 0){
        if(isValid(current, dict) && strContains(current,floating)){
          wordSet.insert(current);
        }
        return;
      }

      if(fixed[pos] != '-'){
        wordGenerator(current, fixed, floating, floatingChars, dict, wordSet, pos+1,empty);
      } else if(empty == floatingChars.length()){
         for(char c : floatingChars){
            current[pos] = c;
            size_t found = floatingChars.find(c);
            if(found != std::string::npos){
              floatingChars.erase(found,1);
            }
           wordGenerator(current, fixed, floating, floatingChars, dict, wordSet, pos+1,empty-1);
           return;
        }
        } else if (empty != 0){
          for(char c = 'a'; c <= 'z'; c++){
             size_t found = floatingChars.find(c);
            current[pos] = c;
            if(found != std::string::npos){
              floatingChars.erase(found,1);
            }
           wordGenerator(current, fixed, floating, floatingChars, dict, wordSet, pos+1,empty-1);
        }

         }  
         
        
      }

      




// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  std::set<std::string> wordSet;
  std::string start = in;
  std::string floatingChars = floating;
  int empty = 0;

  for(int i = 0; i < start.length();i++){
    if(start[i] == '-'){
      empty++;
    }
  }
  wordGenerator(start, in,floating,floatingChars, dict, wordSet, 0,empty);
  return wordSet;
}

// Define any helper functions here
