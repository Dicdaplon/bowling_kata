#include "gtest/gtest.h"
#include <bowling.h>
#include <vector>
#include <iostream>
using namespace std;



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

    ASSERT_TRUE(is_equal);
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

    ASSERT_FALSE(is_equal);
}  

TEST(Bowling, RollsLenghterrorDetection) //checking the legality of consistancy of Rolls number (max 20, vector is the same size than the entry)
{
    vector<char> test = { 'X','4','1','3','1','4','/','4' };
    vector<int> predict = RollsToNumbers(test); //The result i get
    vector<int> groundtruth = { 10,4,1,3,1,4,6,4 }; // The result i expect



    ASSERT_TRUE(test.size()==groundtruth.size());
}



int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
