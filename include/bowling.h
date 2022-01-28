#ifndef __BOWLING_H__
#define __BOWLING_H__
#include <vector>
using namespace std;

// Note to myself : Need to transform this basic function as an object as Class Player {Name,Rolls,Frame,Score and methods)

vector<char> RollsInput(void);
vector<int> RollsToNumbers(vector<char> Rollschar); // convert char vector of symbols "X", "/", "-", "4" char... to an int vector.
bool RollsLegalityCheck(vector<int> Rolls); // check 
vector<int> FramesScore(vector<int> Rolls);

#endif
