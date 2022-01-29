#include "gtest/gtest.h"
#include <bowling.h>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;




TEST(Bowling, RollsConvertToNumbers) //My first test in to convert character and symbols entry to a vector for number, dealing with Strike "X", Spare "/", or miss "-"
{
    vector<char> test = { 'X','4','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect

    for (int i = 0; i < test.size(); i++)
    {

        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", input = " << test[i] << " is convert to " << predict[i] << " and Should be " << groundtruth[i];
    }

    
}


TEST(Bowling, RollsFormatErrorDetection) //Dealing with format error, getting a "404" for bad value, and an error message.
{
    vector<char> test = { 'X','F','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect

    EXPECT_EQ(predict[1], 404) << "error at case 1, input = F, should have give us 404" ;



}  

TEST(Bowling, RollsLenghtErrorDetection) //checking the legality of consistancy of Rolls number (max 20, vector is the same size than the entry)
{
    vector<char> test = { 'X','4','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect



    ASSERT_TRUE(test.size()==groundtruth.size() && test.size()<20);   //note to myself : i may create a separate function to check the roll legality.
}

TEST(Bowling, RollsLegalityCheckTrue) //checking the legality of consistancy of Rolls number (max 20, vector is the same size than the entry)
{
    vector<int> GoodRolls = { 10, 4,1, 3,1, 4,6, 4, 10, 10, 5,4, 6,3, 10, 1, 2 };
    ASSERT_TRUE(RollsLegalityCheck(GoodRolls)) << "Identify a good rolls array as illegal";
}

TEST(Bowling, RollsLegalityCheckFalse) 
{
    vector<int> GoodRolls = { 10, 4,1, 3,1, 4,6, 4, 10, 10, 5,4, 6,3, 10, 1, 2, 4, 3, 4 ,2 };
    ASSERT_FALSE(RollsLegalityCheck(GoodRolls)) << "Identify an illegal rolls array as legal";

}

/*TEST(Bowling, FramesScoreCalculator)
{

    vector<char> test = { '3','2','X','3','4','X','4','/','4','/','7','2','1','0','1','2','3','5' };
    vector<int> predict = FramesScore(RollsToNumbers(test)); //The result i get
    vector<int> groundtruth = { 5,17,7,20,14,17,9,1,3,8 }; // The result i expect

    for (int i = 0; i < groundtruth.size(); i++)
    {

        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", predict = " << predict[i] <<  "and Should be " << groundtruth[i];
    }


}
*/

TEST(Bowling, VariousScoreCalculation)
{
    vector<char> rollstest ;
    int groundtruth ; //final score we should get
    int predict ;
    vector<Player> Players;

    rollstest = { 'X','X','X','X','X','X','X' ,'X','X','X','X','X' };
    Players.push_back(rollstest);
    groundtruth = 300;
    predict = Players[0].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


    rollstest = { '-','-','-','-','-','-','-' ,'-','-','-','-','-', '-','-','-','-','-','-','-' ,'-'};
    Players.push_back(rollstest);
    groundtruth = 0;
    predict = Players[1].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


    // various bowling score, checked on https://www.bowlinggenius.com/
    rollstest = { '4','5','5','4','0','4','4','3','7','/','7','2','X','3','4','X','5','/' ,'7'};
    Players.push_back(rollstest);
    groundtruth = 116;
    predict = Players[2].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


    rollstest = { '3','2','X','3','4','X','4','/','4','/','7','2','1','0','1','2','3','5' };
    Players.push_back(rollstest);
    groundtruth = 101;
    predict = Players[3].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;
}

TEST(Bowling, RollsInput) //Asking rolls of the player
{
    cout << "to test this part, \n please enter a bad sequence (unknown symbols, inferior to 9 or superior to 20), \n and right after a good sequence" << endl;
    Player Bob;
    Bob.getscore();
    Bob.seeall();

    ASSERT_TRUE(true);
}


int main(int argc, char ** argv)
{


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
