#pragma once


class Tic_tac_toe
{
private:
	static const int SIZE = 3;
	char board[SIZE][SIZE];

	int gamesPlayed; // Number of games played
	int fastestTime; // Fastest game time in seconds
	int slowestTime; // Slowest game time in seconds
	int totalTime; // Total game time in seconds

	int fastestMoves; // Fewest moves in a game
	int slowestMoves; // Most moves in a game

public:
	Tic_tac_toe(); // Constructor to initialize the board and statistics
	void displayBoard() const; // Function to display the current state of the board
	bool makeMove(int row, int col, char player); // Function to make a move on the board
	
	void resetBoard(); // Function to reset the board for a new game
	void computerMove(char player); // Function for the computer to make a move

	bool checkWin(char player) const; // Function to check if the specified player has won
	bool isBoardFull() const; // Function to check if the board is full

	void updateStatistics(int gameTime, int moves); // Function to update the game statistics
	void displayStatistics() const; // Function to display the game statistics

};