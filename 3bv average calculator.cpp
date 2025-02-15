#include "DataPlot.h"
#include <Windows.h>
#include <iostream>

Difficulties DIFF = INTERMEDIATE;
const int SIZEA = difficultyData[DIFF].sizeX, SIZEB = difficultyData[DIFF].sizeY, MINES = difficultyData[DIFF].mines;


void initField(int**);
void labelField(int**);
int find3BV(int**);
void floodFillMark(int**, bool**, int, int);


int main()
{
    int** field = new int*[SIZEA];
    int input = 0;
    DataPlot data;
    srand(time(0));

    for (int i = 0; i < SIZEA; ++i) 
        field[i] = new int[SIZEB];

    for (int i = 0; i < SIZEA * SIZEB; ++i)
        field[i / SIZEB][i % SIZEB] = 0;


    std::cout << SIZEA << 'x' << SIZEB
        << ", " << MINES << " mines\n";

    data.load(DIFF);

    for (int i = 1; i <= 1000000; i++)
    {
        initField(field);
        labelField(field);

        data.insert(find3BV(field));

        if (i % 50000 == 0)
        {
            std::cout << "\nBoards checked: " << data.total()
				<< "\nmin 3bv: " << data.minimum()
        		<< "\nq1: " << data.q1()
        		<< "\nmedian: " << data.median()                                    
				<< "\nmean: " << data.mean()
                << "\nq3: " << data.q3()
                << "\nmax 3bv: " << data.maximum()
                << "\n";
        }
    }

    data.save(DIFF);

    for (int i = 0; i < SIZEA; ++i) 
        delete[] field[i];
    delete[] field;
    
    while (true)
    {
        std::cout << "\nhow rare is YOUR 3bv? \n3bv: ";
        std::cin >> input;
        std::cout << data.percentage(input) * 100 << "% chance!\n";
    }
}


void initField(int** field)
{
    for (int i = 0; i < SIZEA * SIZEB; i++)
        field[i / SIZEB][i % SIZEB] = 0;

    int coords[2];

    //mines are nines since 9 cant show up on a minesweeper grid
    for (int i = 0; i < MINES; i++)
    {
        do
        {
            coords[0] = rand() % SIZEA;
            coords[1] = rand() % SIZEB;
        } while (field[coords[0]][coords[1]] == 9); //prevent doubling up

        field[coords[0]][coords[1]] = 9;
    }
}

void labelField(int** field)
{
    for (int i = 0; i < SIZEA * SIZEB; i++)
        if (field[i / SIZEB][i % SIZEB] == 9) //if mine
            for (int j = -1; j <= 1; j++) //check neighboring cells
                for (int k = -1; k <= 1; k++)
                    if ((j != 0 || k != 0) //not current cell, the mine 
                        && i / SIZEB + j >= 0 && i % SIZEB + k >= 0 //not out of bounds
                        && i / SIZEB + j < SIZEA && i % SIZEB + k < SIZEB //not out of bounds
                        && field[i / SIZEB + j][i % SIZEB + k] != 9) //neighbor is not a mine
                        field[i / SIZEB + j][i % SIZEB + k]++; //increase cell value by 1
}


int find3BV(int** field)
{
    int countClicks = 0;
    bool** marks = new bool* [SIZEA]; //to track visited cells

    for (int i = 0; i < SIZEA; ++i)
        marks[i] = new bool[SIZEB];

    for (int i = 0; i < SIZEA * SIZEB; ++i)
        marks[i / SIZEB][i % SIZEB] = false;


    for (int i = 0; i < SIZEA; ++i) 
    {
        for (int j = 0; j < SIZEB; ++j) 
        {
            if (!marks[i][j]) 
            { //only check unvisited cells
                if (field[i][j] == 0) 
                {
                    //start a flood-fill for a region of 0s
                    countClicks++;
                    floodFillMark(field, marks, i, j);
                }
                else if (field[i][j] == 9) 
                    marks[i][j] = true; //mark it as visited
            }
        }
    }

    for (int i = 0; i < SIZEA * SIZEB; i++)
        if (!marks[i / SIZEB][i % SIZEB])
            countClicks++; //0s revealed and mines marked, clicks left over

    for (int i = 0; i < SIZEA; ++i) 
        delete[] marks[i];
    delete[] marks;

    return countClicks;
}


void floodFillMark(int** field, bool** marks, int a, int b) 
{
    if (a < 0 || b < 0 || a >= SIZEA || b >= SIZEB) return; //out of bounds
    if (marks[a][b]) return; //already visited
    if (field[a][b] == 9) return; //ignore mines

    marks[a][b] = true; //mark current cell as visited

    if (field[a][b] == 0)
        //recursively check all 8 neighbors for 0s
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                if (i != 0 || j != 0)  //skip the current cell
                    floodFillMark(field, marks, a + i, b + j);
}



/*
Count3BV:

  For each empty ("0") cell C:
    If C has already been marked, continue.
    Mark C. Add 1 to your 3BV count.
    Call FloodFillMark(C).
  For each non-marked, non-mine cell:
    Add 1 to your 3BV count.

FloodFillMark(C):

  For every non-marked neighbor N of C (diagonal and orthogonal):
    Mark N.
    If N is an empty cell, call FloodFillMark(N).
*/