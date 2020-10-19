#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <string>
/*
* need a static method that returns a checkerboard made of 
*/
using namespace std;
class CheckerBoard
{
private:
	vector<vector<int> > grid;
	int size;
	struct Vector2;
	static int tileNo;
	
public:
	
	/// <summary>
	/// create a checkerboard with 2^n by 2^n and one tile missing
	/// </summary>
	static CheckerBoard fromRT(int n, int missingX, int missingY);

	/// <summary>
	/// create a checkerboard and initialize them all to 0
	/// </summary>
	CheckerBoard(int n);

	int getSize() const;

	void print() const;


private:
	/// <summary>
	/// fill the grid with RT tiling 
	/// </summary>
	void generateRTTiling(int missingRow, int missingCol, int range);
	Vector2& findQuarter(int missingRow, int range, int missingCol);
	void fill2(int missingRow, int missingCol);
	void fillCorners(CheckerBoard::Vector2& quarter, int range, int dRow, int dCol, int missingX, int missingY);
	void fillCenterRT(int dRow, int dCol, Vector2 quarter, int range);
	static void incTileNo();
	static void copyTile(const CheckerBoard& from, CheckerBoard& to, int row, int col);
};

