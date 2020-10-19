// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.




/*
* Input: integer n, and position of a tile
* Output: A Tile maping of the checkerboard made with right triominoes
* 
* Classes:
*   1. Checkerboard
*   2. Displayer, currently using only console and txt. maybe use .csv
*/
#include <iostream>
#include <math.h> 
#include "CheckerBoard.h"


int main()
{
    string command;
    while (command !="exit")
    {
        cout << "please enter a command:\n";
        cout << "   build: build the tilemap with right triminoes\n";
        cout << "   exit: exit the program\n";
        cin >> command;
        if (command == "build")
        {
            int n;
            int row;
            int col;
            cout << "please enter n, row of the missing tile, col of the missing tile\n";
            cout << "seperated by space\n";
            cin >> n;
            cin >> row;
            cin >> col;
            CheckerBoard board = CheckerBoard::fromRT(pow(2,n), row, col);
            board.print();
        }
    }
    
    
}


