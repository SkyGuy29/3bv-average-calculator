#include "Field.h"


Field::Field()
{
    srand(time(nullptr));

    diff = BEGINNER;
    sizeX = diffData[BEGINNER].sizeX;
    sizeY = diffData[BEGINNER].sizeY;
    mines = diffData[BEGINNER].mines;

    field = new int* [sizeX];
    for (int i = 0; i < sizeX; ++i) 
        field[i] = new int[sizeY];

    for (int i = 0; i < sizeX * sizeY; ++i)
        field[i / sizeY][i % sizeY] = 0;
}


Field::~Field()
{
    for (int i = 0; i < sizeX; ++i) 
        delete[] field[i];
    delete[] field;
}


void Field::setDifficulty(Difficulty diffic)
{
    if (diff == diffic) return; //no need to change if same difficulty

	diff = diffic;

	for (int i = 0; i < sizeX; ++i) 
        delete[] field[i];
    delete[] field;

	sizeX = diffData[diffic].sizeX;
    sizeY = diffData[diffic].sizeY;
    mines = diffData[diffic].mines;

    field = new int* [sizeX];
    for (int i = 0; i < sizeX; ++i) 
        field[i] = new int[sizeY];

    for (int i = 0; i < sizeX * sizeY; ++i)
        field[i / sizeY][i % sizeY] = 0;
}


void Field::reset() const
{
    init();
    label();
}


int Field::find3BV()
{
    int countClicks = 0;
    bool** marks = new bool* [sizeX]; //to track visited cells

    for (int i = 0; i < sizeX; ++i)
        marks[i] = new bool[sizeY];

    for (int i = 0; i < sizeX * sizeY; ++i)
        marks[i / sizeY][i % sizeY] = false;

    for (int i = 0; i < sizeX; ++i) 
        for (int j = 0; j < sizeY; ++j) 
            if (!marks[i][j]) //only check unvisited cells
                if (field[i][j] == 0) 
                {
                    //start a flood-fill for a region of 0s
                    countClicks++;
                    floodFillMark(marks, i, j);
                }
                else if (field[i][j] == 9) 
                    marks[i][j] = true; //mark it as visited

    for (int i = 0; i < sizeX * sizeY; i++)
        if (!marks[i / sizeY][i % sizeY])
            countClicks++; //0s revealed and mines marked, clicks left over

    for (int i = 0; i < sizeX; ++i) 
        delete[] marks[i];
    delete[] marks;

    return countClicks;
}


void Field::init() const
{
    for (int i = 0; i < sizeX * sizeY; i++)
        field[i / sizeY][i % sizeY] = 0;

    int coords[2];

    //mines are nines since 9 cant show up on a minesweeper grid
    for (int i = 0; i < mines; i++) //add this many mines to the board
    {
        do
        {
            coords[0] = rand() % sizeX; //random y value
            coords[1] = rand() % sizeY; //random x value
        } while (field[coords[0]][coords[1]] == 9); //prevent doubling up

        field[coords[0]][coords[1]] = 9;
    }
}


void Field::label() const
{
    for (int i = 0; i < sizeX * sizeY; i++) //for each cell
        if (field[i / sizeY][i % sizeY] == 9) //if mine
            for (int j = -1; j <= 1; j++) //check neighboring cells
                for (int k = -1; k <= 1; k++)
                    if ((j != 0 || k != 0) //not current cell, the mine 
                        && i / sizeY + j >= 0 && i % sizeY + k >= 0 //not out of bounds (low)
                        && i / sizeY + j < sizeX && i % sizeY + k < sizeY //not out of bounds (high)
                        && field[i / sizeY + j][i % sizeY + k] != 9) //neighbor is not a mine
                        field[i / sizeY + j][i % sizeY + k]++; //increase cell value by 1
}


void Field::floodFillMark(bool** marks, int a, int b)
{
    if (a < 0 || b < 0 || a >= sizeX || b >= sizeY) return; //out of bounds
    if (marks[a][b]) return; //already visited
    if (field[a][b] == 9) return; //ignore mines (this shouldn't ever happen I think)

    marks[a][b] = true; //mark current cell as visited

    if (field[a][b] == 0)
        for (int i = -1; i <= 1; ++i) //check all eight neighbors for 0s
            for (int j = -1; j <= 1; ++j)
                if (i != 0 || j != 0)  //skip the current cell
                    floodFillMark(marks, a + i, b + j); //if it is a 0, recurse
}