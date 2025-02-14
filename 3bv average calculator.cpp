#include <iostream>
#include <Windows.h>

//const int SIZEA = 24, SIZEB = 20, MINES = 99; //google minesweeper hard
const int SIZEA = 30, SIZEB = 16, MINES = 99; //microsoft minesweeper expert

void initField(int[][SIZEB]);
void labelField(int[][SIZEB]);
int find3BV(int[][SIZEB]);
void floodFillMark(int[][SIZEB], bool[][SIZEB], int, int);


int main()
{
    int field[SIZEA][SIZEB], count = 0, min = 2048, max = 0, temp = 0;
    long sum = 0;
    srand(time(0));

    std::cout << SIZEA << 'x' << SIZEB
        << ", " << MINES << " mines\n";
    
    for (int i = 0; i < 10000000; i++)
    {
        initField(field);
        /*
        if (count == 0)
        {
            std::cout << '\n';
            for (int i = 0; i < SIZEA * SIZEB; i++)
            {
                if (field[i / SIZEB][i % SIZEB] == 0)
                    std::cout << ' ';
                else
                    std::cout << field[i / SIZEB][i % SIZEB];
                if ((i + 1) % SIZEA == 0)
                    std::cout << '\n';
            }
        }
        */

        labelField(field);
        temp = find3BV(field);
        if (temp < min)
            min = temp;
        if (temp > max)
            max = temp;
        sum += temp;


        if ((i + 1) % 50000 == 0)
            std::cout << "\nBoards checked: " << i + 1
                << "\nmin 3bv: " << min << "\nmax 3bv: " << max
                << "\nAverage 3bv: " << (double)sum / (i + 1) << "\n";
        
    }
}


void initField(int field[][SIZEB])
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

void labelField(int field[][SIZEB])
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

int find3BV(int field[][SIZEB]) {
    int countClicks = 0, countUnmarks = 0;
    bool marks[SIZEA][SIZEB]{}; //to track visited cells

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
            countUnmarks++; //0s revealed and mines marked, clicks left over

    return countClicks + countUnmarks;
}


void floodFillMark(int field[][SIZEB], bool marks[][SIZEB], int a, int b) 
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