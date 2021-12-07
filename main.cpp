/*
Author: Aoun Hussain
Class: ECE 6122-A
Last Date Modified: Thur, Sep 23, 2021
Description: This is the cpp source file for the solution of problem 2, lab 1.
             It outputs the number of black squares left on a white square grid
             to a text file when the ant takes the given the number of moves
             according to some standard rules as defined in problem 2.
*/

/*
 References:
 https://en.wikipedia.org/wiki/Langton%27s_ant
 https://www.cplusplus.com/reference/set/set/find/
 https://www.cplusplus.com/reference/unordered_map/unordered_map/
 https://euler.stephan-brumme.com/349/
 https://stackoverflow.com/questions/7576953/c-auto-keyword-why-is-it-magic
*/

#include <cctype>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

bool is_numeric(const string &strIn, unsigned long &nInputNumber)
{
    /*
    Checks if the argument is numeric and returns true/false accordingly
    */

    bool bRC = all_of(strIn.begin(), strIn.end(), [](unsigned char c)
    {
        return ::isdigit(c);                      // http://www.cplusplus.com/reference/algorithm/all_of/
    }                                             // https://www.geeksforgeeks.org/lambda-expression-in-c/
    );                                            // http://www.cplusplus.com/reference/cctype/isdigit/
    if (bRC)
    {
        nInputNumber = stoul(strIn);              // https://www.cplusplus.com/reference/string/stoul/
        return true;
    }
    else
    {
        return false;
    }

}

unsigned long langtonAnt(const unsigned long &moves)
{
    /* Calculates the number of black squares left after
     given number of moves of the ant in an all white square grid
     The ant starts at the middle of the board and in the forward direction.
    */

    // sufficient squares for all major computations
    long size = 256;

    // ant coordinates, can be negative values
    long xCord = size / 2;
    long yCord = size / 2;

    bool w = false; // white
    bool b = true; // black

    // 1D bool vector array where pos = y * Size + x;
    std::vector<bool> squareGrid(size * size, w);

    // direction can be from 0-3 as indexes of movements in x and y
    //starting with forward direction
    long dir = 0;

    // delta movement when ant moves forward, left, backward, right
    long delX[] = { 0, +1,  0, -1 };
    long delY[] = { +1,  0, -1,  0 };

    // number of black squares
    long cnt = 0;

    // number of steps taken
    unsigned long steps = 0;

    while (steps < moves)
    {
        //move one step
        long pos = yCord * size + xCord;

        if (squareGrid[pos] == w) // if ant is on a white square
        {
            // change color
            squareGrid[pos] = b;
            cnt++;

            // move clockwise
            dir = (dir + 4 - 1) % 4; // adding 4 to avoid negative indexes
        }
        else // if ant is on a black square
        {
            // change color
            squareGrid[pos] = w;
            cnt--;

            // move counter-clockwise
            dir = (dir + 1) % 4;
        }

        xCord += delX[dir];
        yCord += delY[dir];
        steps++;
    }

    return cnt;
}


int main(int argc, char* argv[]){
    /*
    main function to call all functions and check for invalid inputs
     and write output to file
    */

    if (argc == 2)
    {
        unsigned long moves{ 0 };
        unsigned long nSquares{ 0 };
        string strInput(argv[1]);
        bool bIsValid = is_numeric(strInput, moves);
        if (bIsValid)
        {
            // perform function with nInputNumber
            nSquares = langtonAnt(moves);

            ofstream myfile ("output2.txt");
            if (myfile.is_open())
            {
                myfile << to_string(nSquares) << "\n";
                myfile.close();
            }
            else cout << "Unable to open file";
        }
        else
        {
            cout << "Invalid Input" <<endl;
            ofstream myfile ("output2.txt");
            if (myfile.is_open())
            {
                myfile << "Invalid Input" << "\n";
                myfile.close();
            }
            else cout << "Unable to open file";
        }


    }
    else
    {
        cout << "Invalid Input" <<endl;
        ofstream myfile ("output2.txt");
        if (myfile.is_open())
        {
            myfile << "Invalid Input" << "\n";
            myfile.close();
        }
        else cout << "Unable to open file";
    }

    return 0;
}

