#ifndef __BOWLING_H__
#define __BOWLING_H__
#include <vector>
#include <cstring>
using namespace std;


class Player {
	public:

		Player(vector<char>); // directly enter the rolls
		Player::Player(); // call the input() function to ask rolls to the user
		void setrolls(vector<char>); // assign rolls from input
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


vector<char> RollsInput(void); //ask user for rolls
vector<int> RollsToNumbers(vector<char> Rollschar); //convert char rolls to int vector
bool LastFrameCalculator(vector<int> Rolls);
bool RollsLegalityCheck(vector<int> Rolls);  //check and deal with bad rolls.
vector<int> FramesScore(vector<int> Rolls);

#endif
