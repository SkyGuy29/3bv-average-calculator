#pragma once
#include "Difficulty.hpp"
#include <time.h>


struct BoardStats
{
	unsigned bbbv, ops;

	BoardStats() = default;
};

class Field
{
public:
	Field();
	~Field();

	void setDifficulty(Difficulty);
	Difficulty getDifficulty() const { return diff; }
	int getSizeX() const { return sizeX; }
	int getSizeY() const { return sizeY; }
	int getMines() const { return mines; }

	void reset() const;
	BoardStats findStats();
	void saveBoard();
private:
	void floodFillMark(bool**, int, int);
	short** field;
	Difficulty diff = BEGINNER;
	int sizeX, sizeY, mines;
};