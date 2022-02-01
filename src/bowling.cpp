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
    cout << "Rolls of the player  :" << endl;
    for (int i = 0; i < rolls.size(); i++)
    {
        cout << "  " << rolls[i];
    }
}

void Player::seeframe()
{
    cout << "\n";
    cout << "Score per frames :" << endl;
    for (int i = 0; i < frames.size(); i++)
    {
        cout <<"  " << frames[i];
    }
}

void Player::seescore()
{
    cout << " \n\n     Final Score = " << score << "\n\n" << endl;
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
    for (int i = 0; i < 21; i++)
    {
        cout << "\n Please enter results for rolls number " <<(i + 1) << " or all your rolls at once, " << " enter . y . to end your game " << endl;
        cout << "accepted : Strike -> X, Spare -> /, or numbers :" << endl;
        cin >> Rollinput;

        if(Rollinput == ('y'))
        {
            break;
        }
        else{ Rolls.push_back(Rollinput); }
    }
    cout << "\n\n\n Thank you ! Computing your rolls..." << endl;
    return Rolls;

} 

vector<int> RollsToNumbers(vector<char> RollsChar) // convert char vector of symbols "X", "/", "-", "4" char... to an int vector.
{

    vector<int> Rolls;
    for (int i = 0; i < RollsChar.size(); i++)
    {

        if (RollsChar[i] == 'X' || RollsChar[i] == 'x')
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

bool LastFrameCalculator(vector<int> Rolls) //test the legality of the rolls after the 10th frame
{
    int FrameNumber =0;
    int Roll_ten_position;

    for (int i = 0; i < Rolls.size(); i++)
    {
        if (FrameNumber == 10) { break; }
        else if (Rolls[i] == 10) { FrameNumber++; }
        else { FrameNumber++;  i++; }

        Roll_ten_position = i;
    }


    int RollsRemain = Rolls.size() - Roll_ten_position - 1;   //consider to number of rolls after the 10th and take a decision on the legality.

    if (Rolls[Roll_ten_position] == 10 && RollsRemain == 2)
    {
        return true;
    }
    else if ((Rolls[Roll_ten_position] + Rolls[Roll_ten_position - 1]) == 10  && RollsRemain == 1)
    {
        return true;
    }
    else if((Rolls[Roll_ten_position] + Rolls[Roll_ten_position - 1]) < 10 && RollsRemain == 0)
    { 
        return true;
    }
    else { return false; }


}
bool RollsLegalityCheck(vector<int> Rolls) // Legality check of the rolls (size and bad input)
{
    for (int i = 0; i < Rolls.size(); i++)   //check the bad entry, as unknown characters
    {
        if (Rolls[i] == 404)
        {
            return false;
        }
        else
        { }
    }

    if ((Rolls.size() < 22) && (Rolls.size() > 9)) //check rolls legality
    {
        ;
    }
    else {return false; }


    if (LastFrameCalculator(Rolls) == true) { return true; } // test the legality of the rolls after the 10th frame
    else { return false; }

   

    //an update can be to check the following number that is impossible -> 6 and 8 on the same frame.

}

vector<int> FramesScore(vector<int> Rolls)
{
    vector<int> Frames;
    if (RollsLegalityCheck(Rolls) == true)
    {
        for (int i = 0; i < Rolls.size() - 1; i++)
        {

            if (Rolls[i] == 10)
            {
                Frames.push_back(10 + Rolls[i + 1] + Rolls[i + 2]);
            }
            else if ((Rolls[i] + Rolls[i + 1]) == 10)
            {

                Frames.push_back(10 + Rolls[i + 2]);
                i++;
            }
            else
            {
                Frames.push_back(Rolls[i] + Rolls[i + 1]);
                i++;
            }
            if (Frames.size() == 10)
            {
                break;
            }
            else {}



        }
        return Frames;
    }
    else
    {
        cout << "Format Error !" << endl;
        Frames.push_back(0);
        return Frames;
    }

}
