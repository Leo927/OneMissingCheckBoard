#include "CheckerBoard.h"

int CheckerBoard::tileNo = 1;

struct CheckerBoard::Vector2
{
	int row;
	int col;
};

CheckerBoard CheckerBoard::fromRT(int n, int missingX, int missingY)
{	
	int _size = n;
	if (_size <= 0)
	{
		cout << "Fatal error: invalid size\n";
		return NULL;
	}
	if (missingX > _size - 1 ||
		missingY > _size - 1)
	{
		cout << "Fatal error: invalid missing tile position\n";
		return NULL;
	}
	CheckerBoard board = CheckerBoard(_size);
	board.generateRTTiling(missingX, missingY, _size);
	return board;
}


CheckerBoard::CheckerBoard(int n)
{
	this->size = n;
	
	for (int i = 0; i < this->size; i++)
	{	
		grid.push_back(vector<int>(size, 0));	
	}
}

int CheckerBoard::getSize() const
{
	return this->size;
}

void CheckerBoard::print() const
{
	int maxLength = log10(tileNo) + 2;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setw(maxLength)<< grid[i][j];
		}
		cout << endl;
	}
	tileNo = 1;
}

/*
CheckerBoard::~CheckerBoard()
{
	if (grid == nullptr )
		return;
	for (int i = 0; i < this->size; i++)
		delete grid[i];
	delete grid;
	grid = nullptr;
}
*/


void CheckerBoard::generateRTTiling(int missingRow, int missingCol, int range)
{
	//cout <<"range: "<<range << "  missingRow: " << missingRow << "  missingCol: " << missingCol << endl;
	/*	
	* if the size is less than 2. return a 2d-array with target tile 0 and other tiles as 1.
	* Loop while range > 2
	* Determine which quarter the missing tile is within the range
	* fill the other three quarters with tilemaps which have the center corner missing.
	* fill the three center missing corners with a new RT
	* update range=range/2
	* 
	*/	
	
	if (missingRow >= this->size ||
		missingCol >= this->size)
	{
		cout << "invalid missing tile position in generation\n";
		abort();
	}
	

	if (range <= 2)
	{
		fill2(missingRow, missingCol);
		return;
	}

	

	
	//cout << "range: " << range << endl;
	//find which quarter it is
	Vector2 quarter = findQuarter(missingRow, range, missingCol);

	int dRow = quarter.row * (size - range);
	int dCol = quarter.col * (size - range);

	fillCorners(quarter, range, dRow, dCol, missingRow, missingCol);

	//fill the missing center corners with a new RT
	fillCenterRT(dRow,dCol,quarter,range);
}

CheckerBoard::Vector2& CheckerBoard::findQuarter(int missingRow, int range, int missingCol)
{
	Vector2 quarter;
	quarter.row = missingRow % range >= size / 2;
	quarter.col = missingCol % range >= size / 2;
	return quarter;
}

void CheckerBoard::fill2(int missingRow, int missingCol)
{
	//cout << "fill 2 \n";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			grid[i][j] = tileNo;
		}
	}
	incTileNo();
	grid[missingRow][missingCol] = 0;
	return;
}

void CheckerBoard::fillCorners(CheckerBoard::Vector2& quarter, 
	int range, 
	int dRow, 
	int dCol, 
	int missingRow, 
	int missingCol)
{
	//cout << "fill Corners\n";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int tempMisRow = (i + 1) % 2 * (range / 2 - 1);
			int tempMisCol = (j + 1) % 2 * (range / 2 - 1);
			CheckerBoard temp = NULL;
			if (quarter.row != i || quarter.col != j)
				temp = fromRT(range / 2, tempMisRow, tempMisCol);
			else
				temp = fromRT(range / 2, missingRow % (range / 2), missingCol % (range / 2));
			copyTile(temp, *this, i * (range / 2) + dRow, j * (range / 2) + dCol);
		}
	}
}

void CheckerBoard::fillCenterRT(int dRow, int dCol, Vector2 quarter, int range)
{
	/*for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (quarter.row == i && quarter.col == j)
				continue;
			int absRow = dRow + (range / 2 - 1) + i;
			int absCol = dCol + (range / 2 - 1) + j;
			grid[absRow][absCol] = tileNo;
		}
	}
	incTileNo();
	*/
	//cout << "filling center\n";
	int absRow = dRow + (range / 2 - 1);
	int absCol = dCol + (range / 2 - 1);
	CheckerBoard temp = fromRT(2, quarter.row, quarter.col);
	copyTile(temp, *this, absRow, absCol);
}




void CheckerBoard::incTileNo()
{
	tileNo++;
}

void CheckerBoard::copyTile(const CheckerBoard& from, CheckerBoard& to, int dX, int dY)
{
	//if (from.size < to.size / 2)
		//return;
	/*cout << "from tilemap: \n";
	from.print();
	cout << "to tilemap: " << "dX: " << dX << " | dCol: " << dY << endl;
	to.print();*/
	for (int i = 0; i < from.size; i++)
	{
		for (int j = 0; j < from.size; j++)
		{
			if(from.grid[i][j] != 0)
				to.grid[i + dX][j + dY] = from.grid[i][j];
		}
	}
	/*cout << "result:\n";
	to.print();*/
}
