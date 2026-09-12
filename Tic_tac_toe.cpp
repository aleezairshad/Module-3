#include "Tic_tac_toe.h"
#include <iostream>
#include <iomanip>

using namespace std;

// precondition: None
// postcondition: Initializes the Tic-Tac-Toe board and statistics
Tic_tac_toe::Tic_tac_toe()
{
    resetBoard();
    gamesPlayed = 0;
    fastestTime = 0;
    slowestTime = 0;
    totalTime = 0;
    fastestMoves = 0;
    slowestMoves = 0;
}

// precondition: None
// postcondition: Resets the Tic-Tac-Toe board to its initial state
void Tic_tac_toe::resetBoard()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            board[row][col] = ' ';
        }
    }
}

// precondition: row and col are valid indices for the board
// postcondition: Places the player's mark on the board if the move is valid
bool Tic_tac_toe::makeMove(int row, int col, char player)
{
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
    {
        return false; // Invalid move
    }
    if (board[row][col] != ' ')
    {
        return false; // Square already owned
    }
    board[row][col] = player;
    return true; // Move successful
}

// precondition: None
// postcondition: Returns true if the board is full (no empty spaces),
bool Tic_tac_toe::isBoardFull() const
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

// precondition: player is either 'X' (human) or 'O' (computer)
// postcondition: Returns true if the specified player has won the game,
bool Tic_tac_toe::checkWin(char player) const
{
    // Check rows
    for (int row = 0; row < SIZE; row++)
    {
        bool win = true;

        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] != player)
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            return true;
        }
    }

	// Check columns
    for (int col = 0; col < SIZE; col++)
    {
        bool win = true;

        for (int row = 0; row < SIZE; row++)
        {
            if (board[row][col] != player)
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            return true;
        }
    }

    // Check diagonal from top-left to bottom-right
	bool win = true; // Reset win flag for diagonal check
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][i] != player)
        {
            win = false;
            break;
        }
    }

    if (win)
    {
        return true;
    }

    // Check diagonal from top-right to bottom-left
    win = true; // Reset win flag for diagonal check
	const int ONE = 1; // Constant to represent the value 1
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][SIZE - ONE - i] != player)
        {
            win = false;
            break;
        }
    }

    if (win)
    {
        return true;
    }

    return false;
}

// precondition: None
// postcondition: Determines the computer's move based on a simple AI strategy
void Tic_tac_toe::computerMove(char player)
{
    int bestRow = -1;
    int bestCol = -1;
    const int NEGATIVE_ONE = -1;
	const int ONE = 1;

    // Check if COMPUTER can win in the next move
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == ' ')
            {
                board[row][col] = player;

                if (checkWin(player))
                {
                    bestRow = row;
                    bestCol = col;

                    board[row][col] = ' ';
                    break;
                }

                board[row][col] = ' ';
            }
        }

        if (bestRow != NEGATIVE_ONE)
        {
            break;
        }
    }

    // Check if HUMAN can win in the next move and block it
    if (bestRow == NEGATIVE_ONE)
    {
        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                if (board[row][col] == ' ')
                {
                    board[row][col] = 'X';

                    if (checkWin('X'))
                    {
                        bestRow = row;
                        bestCol = col;

                        board[row][col] = ' ';
                        break;
                    }

                    board[row][col] = ' ';
                }
            }

            if (bestRow != NEGATIVE_ONE)
            {
                break;
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
	const int FOUR = 4;
    // Take a corner
    if (bestRow == NEGATIVE_ONE)
    {
		int cornerRows[FOUR] = { 0, 0, SIZE - ONE, SIZE - ONE }; // Define the row indices of the four corners of the board
		int cornerCols[FOUR] = { 0, SIZE - ONE, 0, SIZE - ONE }; // Define the column indices of the four corners of the board

		int availableRows[FOUR]{}; // Array to store the row indices of available corners
		int availableCols[FOUR]{}; // Array to store the column indices of available corners
		int count = 0; // Counter to keep track of the number of available corners
		// Check for available corner positions
        for (int i = 0; i < FOUR; i++)
        {
            if (board[cornerRows[i]][cornerCols[i]] == ' ')
            {
                availableRows[count] = cornerRows[i];
                availableCols[count] = cornerCols[i];
                count++;
            }
        }
		// If there are available corners, select one randomly
        if (count > 0)
        {
            int random = rand() % count;

            bestRow = availableRows[random];
            bestCol = availableCols[random];
        }
    }

    // Take a side
    if (bestRow == NEGATIVE_ONE)
    {
        int sideRows[FOUR] = { 0, SIZE / TWO, SIZE / TWO, SIZE - ONE };

        int sideCols[FOUR] = { SIZE / TWO, 0, SIZE - ONE, SIZE / TWO };

        int availableRows[FOUR]{};
        int availableCols[FOUR]{};
        int count = 0;
		// Check for available side positions
        for (int i = 0; i < FOUR; i++)
        {
			// Check if the side position is empty
            if (board[sideRows[i]][sideCols[i]] == ' ')
            {
				availableRows[count] = sideRows[i]; // Store the available row index
				availableCols[count] = sideCols[i]; // Store the available column index
                count++;
            }
        }

        if (count > 0)
        {
            int random = rand() % count;

			bestRow = availableRows[random]; // Select a random available side position
			bestCol = availableCols[random]; // Select a random available side position
        }
    }

    // Make the move
    if (bestRow != NEGATIVE_ONE)
    {
		board[bestRow][bestCol] = player; // Place the computer's mark on the board
    }
}

// precondition: None
// postcondition: Displays the current state of the Tic-Tac-Toe board
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
        cout << string(THREE, DIVIDER);

        if (col < SIZE - ONE)
        {
            cout << TOP_DIVIDER;
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

// precondition: gameTime is the time taken for the game in seconds
// postcondition: Updates the game statistics with the provided game time and number of moves
void Tic_tac_toe::updateStatistics(int gameTime, int moves)
{
	const int ONE = 1;
	gamesPlayed++; // Increment the number of games played
	totalTime += gameTime; // Add the game time to the total time

    if (gamesPlayed == ONE)
    {
        fastestTime = gameTime;
        slowestTime = gameTime;

        fastestMoves = moves;
        slowestMoves = moves;
    }
    else
    {
        if (gameTime < fastestTime)
        {
            fastestTime = gameTime;
            fastestMoves = moves;
        }

        if (gameTime > slowestTime)
        {
            slowestTime = gameTime;
            slowestMoves = moves;
        }
    }
}

// precondition: None
// postcondition: Displays the game statistics, including the number
// of games played, fastest and slowest times, and average time
void Tic_tac_toe::displayStatistics() const
{
	const int ONE = 1, ZERO = 0;
	// Check if any games have been played
    if (gamesPlayed == ZERO)
    {
        cout << "\n\tNo game statistic collected.\n";
        return;
    }
    cout << "\n\tGame statistics:\n\n";

    // Display the number of games played
    if (gamesPlayed == ONE)
    {
        cout << "\t1 game of Tic-Tac-Toe was played.\n";
    }
    else
    {
        cout << "\t" << gamesPlayed << " games of Tic-Tac-Toe were played.\n";
    }

    // Display fastest and slowest games
    cout << "\t\tThe fastest time was " << fastestTime << " seconds in " << fastestMoves << " moves.\n";
    cout << "\t\tThe slowest time was " << slowestTime << " seconds in " << slowestMoves << " moves.\n";

	double averageTime = 0.0; // Variable to store the average time of the games played

    // Calculate average time
    if (gamesPlayed > ZERO)
    {
        averageTime = static_cast<double>(totalTime) / gamesPlayed;
    }
	// Display average time
    cout << "\t\tThe average time was " << averageTime << " second(s).\n";
}
