#include "bowling.h"
#include <vector>
using namespace std;
#include <iostream>
#include <cstring>


Player::Player()
{
    vector<char> rollsinput;
    bool Legal;
    do {
        Legal = true;
        rollsinput = RollsInput();
        setrolls(rollsinput);
        if (RollsLegalityCheck(rolls)==true)
        {
            computescore();
        }
        else
        {
            Legal = false;
            cout << "\n Illegals rolls ! \n Please start again : \n";

        }
    } while (Legal==false);

}

Player::Player(vector<char> rollsinput)
{
    bool Legal;

        setrolls(rollsinput);
        if (RollsLegalityCheck(rolls))
        {
            computescore();
        }
        else
        {
            cout << "\n Illegals rolls !";
        }

       
}

void Player::setrolls(vector<char> rollsInput)
{
    rolls = RollsToNumbers(rollsInput);
}

void Player::computescore(void)
{
    score = 0;
    frames = FramesScore(rolls);
    for (int i = 0; i < frames.size(); i++)
    {
        score += frames[i];
    }
}

void Player::seerolls()
{
    cout << "\n";
    cout << "Rolls du joueur N  :" << endl;
    for (int i = 0; i < rolls.size(); i++)
    {
        cout << "  " << rolls[i];
    }
}

void Player::seeframe()
{
    cout << "\n";
    cout << "Frame du joueur N  :" << endl;
    for (int i = 0; i < frames.size(); i++)
    {
        cout <<"  " << frames[i];
    }
}


void Player::seescore()
{
    cout << " \n Score = " << score << endl;
}

void Player::seeall()
{
    seerolls();
    seeframe();
    seescore();
}

int Player::getscore()
{
    return score;
}

vector<char> RollsInput(void) // ask for rolls 
{
    vector<char> Rolls;
    char Rollinput;
    for (int i = 0; i < 20; i++)
    {
        cout << "Results for rolls number " <<(i + 1) << " enter . y . to end your game " << endl;
        cin >> Rollinput;
        if (Rollinput == 'y')
        {
            break;
        }
        else{ Rolls.push_back(Rollinput); }
    }

    return Rolls;

} 

vector<int> RollsToNumbers(vector<char> RollsChar) // convert char vector of symbols "X", "/", "-", "4" char... to an int vector.
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

        else { cout << "Format Error !" << endl; Rolls.push_back(404);}   // dealing with format error

    }

    return Rolls;
}

bool RollsLegalityCheck(vector<int> Rolls) // Legality check of the rolls, numbers but i want to add better check, for example as first rolls : 4 and 8 isn't possible.
{
    if ((Rolls.size() < 21) && (Rolls.size() > 9))
    {
        return true;
    }
    else { return false; }
    
}

vector<int> FramesScore(vector<int> Rolls)
{
    int n = 0;
    vector<int> Frames;
    for (int i = 0; i < Rolls.size()-2; i++)
    {
        if (Rolls[i] == 10)
        {
            Frames.push_back(   10 + Rolls[i + 1] + Rolls[i + 2] );
        }
        else if ((Rolls[i] + Rolls[i + 1]) == 10)
        {
            Frames.push_back( 10 + Rolls[i + 2] );
            i++;
        }
        else
        {
            Frames.push_back( Rolls[i] + Rolls[i + 1] );
            i++;
        }
    }

    return Frames;

}
