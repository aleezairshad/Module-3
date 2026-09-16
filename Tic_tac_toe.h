#pragma once

class Tic_tac_toe
{
private:
	static const int SIZE = 3; // Size of the Tic-Tac-Toe board
	char board[SIZE][SIZE]; // 2D array to represent the Tic-Tac-Toe board

public:
	Tic_tac_toe(); // Constructor to initialize the board
	void resetBoard(); // Reset the board to its initial state
	bool checkDraw() const; // Check if the game is a draw
	char checkWinner() const; // Check if there's a winner
	bool checkillegalMove(int row, int col) const; // Check if a move is illegal
	void setCellValue(int r, int c); // Set the value of a cell on the board
	char getCellValue(int r, int c) const; // Get the value of a cell on the board
	void computerMove(); // Make a move for the computer
	void displayBoard() const; // Display the current state of the board

};