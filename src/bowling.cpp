#include "bowling.h"
#include <vector>
using namespace std;
#include <iostream>

bool foo()
{
    return true;
}

vector<int> RollsToNumbers(vector<char> RollsChar)
{

    vector<int> Rolls;
    for (int i = 0; i < RollsChar.size(); i++)
    {

        if (RollsChar[i] == 'X')
        {
            Rolls.push_back(10);
        }

        else if (RollsChar[i] == '/')
        {

            int Sndstrike = 10-(RollsChar[i-1]-48);  //replacement of "/" by the value of the roll.
            Rolls.push_back(Sndstrike);
        }

        else if (RollsChar[i] == '-')
        {
            Rolls.push_back(0);  
        }

        else if (( RollsChar[i]-48 >= 0 ) && ( RollsChar[i]- 48 < 11))  //simply convert to number, can deal set of number only (like "10" for strike) as well as symbol (like "X" for a strike)
        {
            Rolls.push_back(RollsChar[i]-48);
        }

        else { cout << "Format Error !" << endl; Rolls.push_back(404); break; }   // dealing with format error

    }

    return Rolls;
}
