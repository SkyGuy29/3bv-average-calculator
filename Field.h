#pragma once
#include "Difficulty.hpp"
#include <time.h>



class Field
{
public:
	Field();
	~Field();
	void setDifficulty(Difficulty);
	void reset() const;
	int find3BV();
	void saveBoard();
private:
	void init() const;
	void label() const;
	void floodFillMark(bool**, int, int);
	int** field;
	int sizeX, sizeY, mines;
};