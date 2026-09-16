#include "Tic_tac_toe.h"
#include <iostream>
#include <iomanip>

using namespace std;

//precondition: None
//postcondition: Initializes the Tic-Tac-Toe board to an empty state
Tic_tac_toe::Tic_tac_toe()  // Constructor to initialize the board
{
	resetBoard();
}

//precondition: None
//postcondition: Resets the Tic-Tac-Toe board to an empty state
void Tic_tac_toe::resetBoard() 
{
	for (int row = 0; row < SIZE; ++row) 
	{
		for (int col = 0; col < SIZE; ++col) 
		{
			board[row][col] = ' ';
		}
	}
}

//precondition: None
//postcondition: Checks if the game is a draw (no empty cells left)
bool Tic_tac_toe::checkDraw() const 
{
	for (int row = 0; row < SIZE; ++row) 
	{
		for (int col = 0; col < SIZE; ++col) 
		{
			if (board[row][col] == ' ') 
			{
				return false;
			}
		}
	}
	return true;
}

//precondition: None
//postcondition: Checks if there's a winner and returns the winning player's symbol ('X' or 'O'), or ' ' if no winner
char Tic_tac_toe::checkWinner() const 
{
	// Check rows
	for (int row = 0; row < SIZE; ++row) 
	{
		if (board[row][0] != ' ' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) 
		{
			return board[row][0]; // Return the winning player's symbol
		}
	}
	// Check columns
	for (int col = 0; col < SIZE; ++col) 
	{
		if (board[0][col] != ' ' && board[0][col] == board[1][col] && board[1][col] == board[2][col]) 
		{
			return board[0][col]; // Return the winning player's symbol
		}
	}
	// Check diagonals from top-left to bottom-right 
	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
	{
		return board[0][0];
	}
	// Check diagonals from top-right to bottom-left
	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
	{
		return board[0][2]; // Return the winning player's symbol
	}
	return ' '; // No winner
}

//precondition: None
//postcondition: Checks if a move is illegal (out of bounds or cell already occupied)
bool Tic_tac_toe::checkillegalMove(int row, int col) const 
{
	return (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ');
}

//precondition: int r and int c are valid indices for the board
//postcondition: Sets the value of a cell on the board to 'X' if the move is legal
void Tic_tac_toe::setCellValue(int r, int c) 
{
	if (!checkillegalMove(r, c)) // Check if the move is legal
	{
		board[r][c] = 'X'; // Assuming player is 'X'
	}
}

//precondition: int r and int c are valid indices for the board
//postcondition: Returns the value of a cell on the board
char Tic_tac_toe::getCellValue(int r, int c) const 
{
	if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) // Check if indices are valid
	{
		return board[r][c]; // Return the value of the cell
	}
	return ' '; // Return space for invalid indices
}

//precondition: None
//postcondition: Makes a move for the computer ('O') based on a simple strategy
void Tic_tac_toe::computerMove() 
{
	int bestRow = -1; // Initialize bestRow to -1 (no move found yet)
	int bestCol = -1; // Initialize bestCol to -1 (no move found yet)
	const int NEGATIVE_ONE = -1; 
	const int ONE = 1;

	// Check if COMPUTER can win in the next move
	for (int row = 0; row < SIZE; ++row) 
	{
		for (int col = 0; col < SIZE; ++col) 
		{
			if (board[row][col] == ' ') 
			{
				board[row][col] = 'O'; // Assuming computer is 'O'
				if (checkWinner() == 'O') 
				{
					bestRow = row;
					bestCol = col;
					board[row][col] = ' '; // Undo move
					break; // Exit inner loop if a winning move is found
				}
				board[row][col] = ' '; // Undo move
			}
		}
		if (bestRow != NEGATIVE_ONE)  
		{
			break; // Exit outer loop if a winning move is found
		}
	}

	if (bestRow == NEGATIVE_ONE) // If no winning move found, check if PLAYER can win in the next move
	{
		// Check if PLAYER can win in the next move and block it
		for (int row = 0; row < SIZE; ++row) 
		{
			for (int col = 0; col < SIZE; ++col) 
			{
				if (board[row][col] == ' ') 
				{
					board[row][col] = 'X'; // Assuming player is 'X'
					if (checkWinner() == 'X') 
					{
						bestRow = row;
						bestCol = col;
						board[row][col] = ' '; // Undo move
						break; // Exit inner loop if a blocking move is found
					}
					board[row][col] = ' '; // Undo move
				}
			}
			if (bestRow != NEGATIVE_ONE) 
			{
				break; // Exit outer loop if a blocking move is found
			}
		}
	}

	const int TWO = 2;
	// Take center
	if (bestRow == NEGATIVE_ONE && board[SIZE / TWO][SIZE / TWO] == ' ')
	{
		bestRow = SIZE / TWO;
		bestCol = SIZE / TWO;
	}

	const int FOUR = 4, ZERO = 0;
	// Take a corner
	if (bestRow == NEGATIVE_ONE) 
	{
		int corners[FOUR][TWO] = { {0, 0}, {0, SIZE - ONE}, {SIZE - ONE, 0}, {SIZE - ONE, SIZE - ONE} }; // Define the four corners of the board
		for (int i = 0; i < FOUR; ++i) 
		{
			int row = corners[i][ZERO];
			int col = corners[i][ONE];
			if (board[row][col] == ' ') 
			{
				bestRow = row;
				bestCol = col;
				break; // Exit loop if a corner is found
			}
		}
	}

	// Take a side
	if (bestRow == NEGATIVE_ONE) 
	{
		int sides[FOUR][TWO] = { {0, 1}, {1, 0}, {1, SIZE - ONE}, {SIZE - ONE, 1} }; // Define the four sides of the board
		for (int i = 0; i < FOUR; ++i) 
		{
			int row = sides[i][ZERO];
			int col = sides[i][ONE];
			if (board[row][col] == ' ') 
			{
				bestRow = row;
				bestCol = col;
				break; // Exit loop if a side is found
			}
		}
	}

	if (bestRow != NEGATIVE_ONE) 
	{
		board[bestRow][bestCol] = 'O'; // Assuming computer is 'O'
	}
}

//precondition: None
//postcondition: Displays the current state of the Tic-Tac-Toe board with Unicode characters for better visualization
void Tic_tac_toe::displayBoard() const
{
	const int THREE = 3, TWO = 2, ONE = 1;
	// Unicode characters for drawing the board
	const char RIGHT_DIVIDER = char(185);
	const char SIDE_DIVIDER = char(186);
	const char TOP_RIGHT_CORNER = char(187);
	const char BOTTOM_RIGHT_CORNER = char(188);
	const char BOTTOM_LEFT_CORNER = char(200);
	const char TOP_LEFT_CORNER = char(201);
	const char BOTTOM_DIVIDER = char(202);
	const char TOP_DIVIDER = char(203);
	const char LEFT_DIVIDER = char(204);
	const char DIVIDER = char(205);
	const char CENTER_DIVIDER = char(206);

	cout << "\n\t\t\t Tic-Tac-Toe\n";

	// Top
	cout << "\t\t\t" << TOP_LEFT_CORNER;
	// Draw the top border of the board
	for (int col = 0; col < SIZE; col++)
	{
		cout << string(THREE, DIVIDER); // Draw the horizontal divider
		if (col < SIZE - ONE)
		{
			cout << TOP_DIVIDER; // Draw the top divider between columns
		}
	}

	cout << TOP_RIGHT_CORNER << '\n'; // End of top border
	// Draw the board
	for (int row = 0; row < SIZE; row++)
	{
		cout << "\t\t\t" << SIDE_DIVIDER;

		for (int col = 0; col < SIZE; col++)
		{
			cout << " " << board[row][col] << " " << SIDE_DIVIDER;
		}
		cout << '\n';
		// Divider between rows
		if (row < SIZE - ONE)
		{
			cout << "\t\t\t" << LEFT_DIVIDER; // Start of row divider

			for (int col = 0; col < SIZE; col++)
			{
				cout << string(THREE, DIVIDER); // Draw the horizontal divider

				if (col < SIZE - ONE)
				{
					cout << CENTER_DIVIDER; // Draw the center divider between columns
				}
			}

			cout << RIGHT_DIVIDER << '\n';
		}
	}

	// Bottom
	cout << "\t\t\t" << BOTTOM_LEFT_CORNER;

	for (int col = 0; col < SIZE; col++)
	{
		cout << string(THREE, DIVIDER); // Draw the bottom border of the board

		if (col < SIZE - ONE)
		{
			cout << BOTTOM_DIVIDER; // Draw the bottom divider between columns
		}
	}
	cout << BOTTOM_RIGHT_CORNER << '\n'; // End of bottom border
}

