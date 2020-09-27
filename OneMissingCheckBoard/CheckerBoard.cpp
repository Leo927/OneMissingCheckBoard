#include "CheckerBoard.h"

int CheckerBoard::tileNo = 1;

CheckerBoard CheckerBoard::fromRT(int n, int missingX, int missingY)
{	
	int _size = n;
	if (_size <= 0)
	{
		cout << "Fatal error: invalid size\n";
		abort();
	}
	if (missingX > _size - 1 ||
		missingY > _size - 1)
	{
		cout << "Fatal error: invalid missing tile position\n";
		abort();
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
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
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
	cout << "range: " << range << endl;
	/*	
	* if the size is less than 2. return a 2d-array with target tile 0 and other tiles as 1.
	* Loop while range > 2
	* Determine which quarter the missing tile is within the range
	* 0 1
	* 2 3
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
	
	while (true)
	{
		//find which quarter it is
		Vector2 quarter;
		quarter.row = missingRow % range >= range / 2;
		quarter.col = missingCol % range >= range / 2;
		int dRow = quarter.row * (size - range);
		int dCol = quarter.col * (size - range);
		CheckerBoard temp =NULL;
		

		if (range <= 2)
		{
			for (int i = dRow; i < dRow+2; i++)
			{
				for (int j = dCol; j < dCol+2; j++)
				{
					grid[i][j] = tileNo;
				}
			}
			incTileNo();
			grid[missingRow][missingCol] = 0;
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (quarter.row != i || quarter.col != j)
				{
					int tempMisRow = (i + 1) % 2 * (range / 2 - 1);
					int tempMisCol = (j + 1) % 2 * (range / 2 - 1);
					temp = fromRT(range / 2, tempMisRow, tempMisCol);
					copyTile(temp, *this, i * (range / 2) + dRow, j * (range / 2) + dCol);					
				}
			}
		}

		//fill the missing center corners with a new RT
		fillCenterRT(dRow,dCol,missingRow,missingCol,range);


		range /= 2;
	}
	
}

void CheckerBoard::fillCenterRT(int dRow, int dCol, int missingRow, int missingCol, int range)
{
	for (int i = dRow + range / 2 - 1; i < dRow + range / 2 + 1; i++)
	{
		for (int j = dCol + range / 2 - 1; j < dCol + range / 2 + 1; j++)
		{
			grid[i][j] = tileNo;
		}
	}
	grid[missingRow][missingCol] = 0;
	incTileNo();
}




void CheckerBoard::incTileNo()
{
	tileNo = (tileNo + 1) % 9;
	if (tileNo <= 0)
		tileNo = 1;
}

void CheckerBoard::copyTile(const CheckerBoard& from, CheckerBoard& to, int dX, int dY)
{
	cout << "from tilemap: \n";
	from.print();
	cout << "to tilemap: " << "dX: " << dX << " | dCol: " << dY << endl;
	to.print();
	for (int i = 0; i < from.size; i++)
	{
		for (int j = 0; j < from.size; j++)
		{
			if(from.grid[i][j] != 0)
				to.grid[i + dX][j + dY] = from.grid[i][j];
		}
	}
	cout << "result:\n";
	to.print();
}
