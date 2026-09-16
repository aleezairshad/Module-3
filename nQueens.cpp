#include "nQueens.h"
#include <iostream>
using namespace std;

nQueens::nQueens(int n)
{
	//create 2D array
	numberOfExistingQueens = 0;
	size = n;
	board = new char* [n];
	for (int i = 0; i < n; i++)
	{
		board[i] = new char[n];
	}

	//fill it with empty signs (based on prof Q's executable it is '-')
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = '-';
		}
	}
}

int nQueens::getSize() const
{
	return size;
}

void nQueens::display() const
{
	cout << "\n\t" << char(201) << string((size * 2 - 1), char(205)) << char(187);
	for (int i = 0; i < size; i++)
	{
		cout << "\n\t" << char(186);
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j];

			if (j < size - 1)
			{
				cout << char(179);
			}
		}
		cout << char(186);
	}
	cout << "\n\t" << char(200) << string((size * 2 - 1), char(205)) << char(188) << "\n";
}

int nQueens::isConflict(int row, int col) const
{
	//check directly that position
	if (board[row][col] == 'Q')
	{
		return 1;
	}
	//check row
	for (int i = 0; i < size; i++)
	{
		if (board[row][i] == 'Q')
		{
			return 2;
		}
	}
	//check column
	for (int i = 0; i < size; i++)
	{
		if (board[i][col] == 'Q')
		{
			return 3;
		}
	}
	//check diagonal (4 directions to check)
	//these 2 variables are for increment and decrement (stepping thru the array to check)
	int r = 0;
	int c = 0;
	//upper-left
	r = row - 1;
	c = col - 1;
	while (r >= 0 && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}
		r--;
		c--;
	}

	//upper-right
	r = row - 1;
	c = col + 1;

	while (r >= 0 && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r--;
		c++;
	}

	//lower-left
	r = row + 1;
	c = col - 1;

	while (r < size && c >= 0)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c--;
	}

	//lower-right
	r = row + 1;
	c = col + 1;

	while (r < size && c < size)
	{
		if (board[r][c] == 'Q')
		{
			return 4;
		}

		r++;
		c++;
	}

	return 0;
}

int nQueens::placeQueen(int row, int col)
{
	int conflictType = isConflict(row - 1, col - 1);
	if (conflictType != 0)
	{
		return conflictType;
	}
	else
	{
		numberOfExistingQueens++;
		board[row - 1][col - 1] = 'Q';
		return 0;
	}
}

bool nQueens::removeQueen(int row, int col)
{
	if (board[row - 1][col - 1] == 'Q')
	{
		numberOfExistingQueens--;
		board[row - 1][col - 1] = '-';
		return true;
	}
	else
	{
		return false;
	}
}

bool nQueens::solved() const
{
	if (numberOfExistingQueens == size)
		return true;
	else
		return false;
}

nQueens::~nQueens()
{
	for (int i = 0; i < size; i++)
	{
		delete[] board[i]; //delete the small array inside big array
	}
	delete[] board; //delete the big board at last
}