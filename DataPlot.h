#pragma once
#include <algorithm>
#include <vector>
#include <fstream>


struct NumMult
{
    int num, mult;

    NumMult(int newNum, int newMult = 1) : num(newNum), mult(newMult) {}
};


struct DiffData
{
    std::string fileName;
    int sizeX, sizeY, mines;
};


enum Difficulties
{
	BEGINNER,
    INTERMEDIATE,
    EXPERT,
    GOOG_HARD,
    COUNT
};


static const DiffData difficultyData[COUNT] =
{
    {"beginner.txt", 9, 9, 10},
    {"intermediate.txt", 16, 16, 40},
    {"expert.txt", 30, 16, 99},
    {"googHard.txt", 24, 20, 99}
};


class DataPlot
{
public:
    void load(Difficulties);
    void insert(int newNum);
    int minimum() { if (!sorted) sort(); return data[0].num; }
    int q1();
	int median();
    double mean() const;
    int q3();
    int maximum() { if (!sorted) sort(); return data[data.size() - 1].num; }
    int total() const;
    double percentage(int xVal);
    void save(Difficulties) const;

private:
    void sort()
    {
        std::sort(data.begin(), data.end(), [](const NumMult& a, const NumMult& b)
            {
                return a.num < b.num;
            }); //wasn't expecting to learn how to use a lambda today

        sorted = true;
    }
    std::vector<NumMult> data;
    bool sorted = true;
};

