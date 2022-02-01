#include "gtest/gtest.h"
#include <bowling.h>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

//Function was wrote separetely to ease TDD approach and called in methods inside a class "Player" (if the code evolve and need to handle multiple players...)


// TEST SET

TEST(SuggestedTestCases, TestCases) //Convert character and symbols entry to a vector for number, dealing with Strike "X", Spare "/", or miss "-"
{
    vector<char> rollstest;
    vector<Player> Players;
    int groundtruth;
    int predict;

    
    rollstest = { 'X', 'X', 'X', 'X', 'X', 'X', 'X' , 'X', 'X', 'X', 'X', 'X' };
    Players.push_back(rollstest);
    groundtruth = 300;
    predict = Players[0].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


    rollstest = { '5','/',  '5','/',  '5', '/',  '5', '/',   '5', '/',   '5', '/',   '5', '/',   '5','/',  '5','/',  '5','/',   '5' };
    Players.push_back(rollstest);
    groundtruth = 150;
    predict = Players[1].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


    rollstest = { '9','-',  '9','-',   '9','-',   '9','-',  '9','-',  '9','-' , '9','-',  '9','-',  '9','-',  '9','-' };
    Players.push_back(rollstest);
    groundtruth =90;
    predict = Players[2].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;


}

// Input, case handle, user side test.
TEST(BowlingInputError, RollsConvertToNumbers) //Convert character and symbols entry to a vector for number, dealing with Strike "X", Spare "/", or miss "-"
{
    vector<char> test = { 'X','4','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect

    for (int i = 0; i < test.size(); i++)
    {

        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", input = " << test[i] << " is convert to " << predict[i] << " and Should be " << groundtruth[i];
    }

    test = { 'x','4','1','3','1','4','/','4' }; //minor handle
    predict = RollsToNumbers(test); //The result i get
    groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect

    for (int i = 0; i < test.size(); i++)
    {

        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", input = " << test[i] << " is convert to " << predict[i] << " and Should be " << groundtruth[i];
    }


    test = { '5','/','5','/', '5', '/', '5', '/', '5', '/', '5', '/', '5', '/','5','/','5','/','5','/','5' };
    predict = RollsToNumbers(test); //The result i get
    groundtruth = { 5,5, 5,5, 5,5, 5,5, 5,5 ,5,5 ,5,5 ,5,5 ,5,5, 5,5 , 5 }; // The result i expect

    for (int i = 0; i < test.size(); i++)
    {

        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", input = " << test[i] << " is convert to " << predict[i] << " and Should be " << groundtruth[i];
    }

    
}


TEST(BowlingInputError, RollsFormatErrorDetection) //Dealing with format error, getting a "404" for bad value, and an error message.
{
    vector<char> test = { 'X','F','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect

    EXPECT_EQ(predict[1], 404) << "error at case 1, input = F, should have give us 404" ;



}  


TEST(BowlingInputError, LastFrameCalculator)  //check that we can detect wrong rolls (can be improved)
{
    vector<int> Rolls;
    int predict;
    int groundtruth;


    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10,    4,6 }; //only one roll after strike at 10th frame
    ASSERT_TRUE(LastFrameCalculator(Rolls)) << "Strike with 2 extra strike detected as bad";

    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10,    4 }; //only one roll after strike at 10th frame
    ASSERT_FALSE(LastFrameCalculator(Rolls)) << "Strike with 1 extra strike detected as good";


    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10 }; //only one roll after strike at 10th frame
    ASSERT_FALSE(LastFrameCalculator(Rolls)) << "Strike with 0 extra strike detected as good";



    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 6,4,    1 }; //only one roll after strike at 10th frame
    ASSERT_TRUE(LastFrameCalculator(Rolls)) << "Spare with 1 extra strike detected as bad";

    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 6,4,    1,4 }; //only one roll after strike at 10th frame
    ASSERT_FALSE(LastFrameCalculator(Rolls)) << "Spare with 2 extra strike detected as good";


    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 1,3 }; //only one roll after strike at 10th frame
    ASSERT_TRUE(LastFrameCalculator(Rolls)) << "No extra rolls considered as bad";

    Rolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 1,3,   4,6 }; //only one roll after strike at 10th frame
    ASSERT_FALSE(LastFrameCalculator(Rolls)) << "Illegal extra rolls considered as good";



    Rolls ={ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    ASSERT_TRUE(LastFrameCalculator(Rolls)) << "Good rolls ending with spare is considered illegal";

    

}

TEST(BowlingInputError, RollsLegalityCheckTrue) //checking the legality of consistancy of Rolls number (between ]10, 20[  and input)
{
   
    vector<int> GoodRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 4,6, 4};
    ASSERT_TRUE(RollsLegalityCheck(GoodRolls)) << "Good rolls ending with spare identified as illegal";

    GoodRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10, 4, 6};
    ASSERT_TRUE(RollsLegalityCheck(GoodRolls)) << "Good rolls ending with strike identified as illegal";

    GoodRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 1,2 };
    ASSERT_TRUE(RollsLegalityCheck(GoodRolls)) << "Good rolls identified as illegal";
}

TEST(BowlingInputError, RollsLegalityCheckFalse)  
{


    vector<int> BadRolls = { 10, 4,1, 3,1, 4 };  //too short
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "A bad rolls (too short) is identified as legal...";

    BadRolls = { 10, 4,1, 3,1, 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 4,6, 4 }; //too long
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "A bad rolls (too short) is identified as legal...";



    BadRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10, 4 }; //only one roll after strike at 10th frame
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "don't detect illegal set of rolls after strikes at 10th";

    BadRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 10 }; //no roll after strike at 10th frame
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "don't detect illegal set of rolls after strikes at 10th";

    BadRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 6,4 };  //no rolls after spare at 10th frame
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "don't detect illegal set, no rolls after Spare at 10th";

    BadRolls = { 10, 4,1, 3,1, 4,6, 10, 10, 4,2 ,3,6, 8,1, 6,4 ,1,2};  //2 rolls after spare at 10th frame
    ASSERT_FALSE(RollsLegalityCheck(BadRolls)) << "don't detect illegal set of rolls after Spare at 10th";

}


// Score calculation test.

TEST(BowlingScoreCalculator, FramesScoreCalculator)  // Frames score calculator
{

    vector<char> test = { '3','2', 'X', '3','4', 'X', '4','/', '4','/', '7','2', '1','0', '1','2', '3','5' };
    vector<int> predict = FramesScore(RollsToNumbers(test)); //The result i get
    vector<int> groundtruth = { 5,17,7,20,14,17,9,1,3,8 }; // The result i expect

    for (int i = 0; i < groundtruth.size(); i++)
    {
        EXPECT_EQ(predict[i], groundtruth[i]) << "error at case " << i << ", predict = " << predict[i] <<  "and Should be " << groundtruth[i];
    }


}


TEST(BowlingScoreCalculator, VariousScoreCalculation)  //a LOT of score verification in different situations.
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

    rollstest = { '2','6','X','3','/','4','2','7','/','X','6','3','X','X','5','3' };
    Players.push_back(rollstest);
    groundtruth = 147;
    predict = Players[4].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;

    rollstest = { '2','6','X','3','/','4','2','7','/','X','6','3','X','3','4', 'X','4','/'};
    Players.push_back(rollstest);
    groundtruth = 140;
    predict = Players[5].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;

    rollstest = { '2','6','X','3','/','4','2','7','/','X','6','3','X','X','4','6','4' };
    Players.push_back(rollstest);
    groundtruth = 154;
    predict = Players[6].getscore();
    EXPECT_EQ(predict, groundtruth) << "Wrong score calculation, should get" << groundtruth << " but give" << predict << endl;
}


// Direct Input test, need user to be tested, feel free to comment to this test when working on the code.
TEST(BowlingInputTest, RollsInput) //Asking rolls of the player
{
    cout << "\nTo test this part, \n please enter a bad sequence (unknown symbols, inferior to 9 or superior to 20), \nand right after a good sequence" << endl;
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
