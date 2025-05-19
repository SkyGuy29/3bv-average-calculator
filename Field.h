#pragma once
#include "Difficulty.hpp"
#include <time.h>



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
	int find3BV();
	void saveBoard();
private:
	void init() const;
	void label() const;
	void floodFillMark(bool**, int, int);
	int** field;
	Difficulty diff = BEGINNER;
	int sizeX, sizeY, mines;
};