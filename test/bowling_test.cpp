#include "gtest/gtest.h"
#include <bowling.h>
#include <vector>
#include <iostream>
using namespace std;


TEST(Bowling, RollsInput) //Asking rolls of the player
{
    RollsInput();

    ASSERT_TRUE(true) << "voila";
}


TEST(Bowling, RollsConvertToNumbers) //My first test in to convert character and symbols entry to a vector for number, dealing with Strike "X", Spare "/", or miss "-"
{
    vector<char> test = { 'X','4','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect
    bool is_equal = false;

    for (int i = 0; i < test.size(); i++)
    {

        if (predict[i] == groundtruth[i])
        {
            is_equal =true;
        }
        else
        { 
            is_equal = false;
            break;
        }
    }

    ASSERT_TRUE(is_equal) << "Wrong number sequence";      //Note to myself : Bad way to make a test, need to get more precise intel with EXPECT_EQ(predict[i], groundtruth[i]) and error message.
}


TEST(Bowling, RollsFormatErrorDetection) //Dealing with format error, getting a "404" for bad value, and an error message.
{
    vector<char> test = { 'X','F','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect
    bool is_equal = false;

    for (int i = 0; i < test.size(); i++)
    {

        if (predict[i] == groundtruth[i])
        {
            is_equal = true;
        }
        else
        {
            is_equal = false;
            break;
        }
    }

    ASSERT_FALSE(is_equal) << "Don't detect input errors" ;
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

TEST(Bowling, FramesScoreCalculator)
{

    vector<int> test = { 10,10,10,10,10,10,10,10,10,10,10,10 }; // perfect score -> 300
    vector<int> predict = FramesScore(test);
    vector<int> groundtruth = { 30,  30,  30, 30,  30, 30,30,30,30,30 };

    bool is_equal = false;

    for (int i = 0; i < groundtruth.size(); i++)
    {

        if (predict[i] == groundtruth[i])
        {
            is_equal = true;
        }
        else
        {
            is_equal = false;
            break;
        }
    }

    ASSERT_TRUE(is_equal) << "Bad Frames scores compute ";

}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
