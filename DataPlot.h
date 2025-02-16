#pragma once
#include <algorithm>
#include <vector>
#include <fstream>
#include "Difficulty.hpp"


struct NumMult
{
    int num, mult;

    NumMult(int newNum, int newMult = 1) : num(newNum), mult(newMult) {}
};


class DataPlot
{
public:
    void load(Difficulty);
    void insert(int newNum);
    int minimum() { if (!sorted) sort(); return data[0].num; }
    int q1();
	int median();
    double mean() const;
    int q3();
    int maximum() { if (!sorted) sort(); return data[data.size() - 1].num; }
    int total() const;
    double percentage(int xVal);
    void save(Difficulty) const;

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

