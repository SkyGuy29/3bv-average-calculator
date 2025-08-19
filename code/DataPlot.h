#pragma once
#include <algorithm>
#include <vector>
#include <fstream>
#include "Difficulty.hpp"


struct NumMult
{
    unsigned num, mult;

    explicit NumMult(const unsigned newNum, const unsigned newMult = 1) : num(newNum), mult(newMult) {}
};


class DataPlot
{
public:
    void load(Difficulty);
    void insert(unsigned newNum);
    unsigned minimum() { if (!sorted) sort(); return data[0].num; }
    unsigned q1();
	unsigned median();
    double mean() const;
    double stdDev() const;
    unsigned q3();
    unsigned maximum() { if (!sorted) sort(); return data[data.size() - 1].num; }
    unsigned long total() const;
    double percentage(unsigned xVal);
    void save(Difficulty);

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

