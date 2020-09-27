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
    
    
    //board.clean();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
