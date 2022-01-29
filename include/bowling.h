#ifndef __BOWLING_H__
#define __BOWLING_H__
#include <vector>
#include <cstring>
using namespace std;

// Note to myself : Need to transform this basic functions as an object as Class Player {Name,Rolls,Frame,Score and methods)
class Player {
	public:

		Player(vector<char>);
		Player::Player();
		void setrolls(vector<char>);
		void computescore();
		void seerolls();
		void seeframe();
		void seescore();
		void seeall();
		int getscore();
	private:
		vector<int> rolls;
		vector<int> frames;
		int score;


};


vector<char> RollsInput(void);
vector<int> RollsToNumbers(vector<char> Rollschar); // convert char vector of symbols "X", "/", "-", "4" char... to an int vector.
bool RollsLegalityCheck(vector<int> Rolls); // check 
vector<int> FramesScore(vector<int> Rolls);

#endif
