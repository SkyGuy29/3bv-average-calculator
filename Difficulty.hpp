#pragma once
#include <string>


struct Foo
{
    std::string fileName;
    int sizeX, sizeY, mines;
};


enum Difficulty
{
    BEGINNER,
    INTERMEDIATE,
    EXPERT,
    GOOG_HARD,
    COUNT
};


static const Foo diffData[COUNT] =
{
    {"beginner.txt", 9, 9, 10},
    {"intermediate.txt", 16, 16, 40},
    {"expert.txt", 30, 16, 99},
    {"googHard.txt", 24, 20, 99}
};
