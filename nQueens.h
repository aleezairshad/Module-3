#pragma once
class nQueens
{
private:
	int size;
	char** board;
	int numberOfExistingQueens;
public:
	nQueens(int n);
	~nQueens();
	int getSize() const;
	void display() const;
	int placeQueen(int row, int column);
	bool removeQueen(int row, int column);
	int isConflict(int row, int col) const;
	bool solved() const;
};

