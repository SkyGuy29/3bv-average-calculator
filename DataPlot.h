#pragma once
#include <algorithm>
#include <vector>


struct NumMult
{
    int num, mult;

    NumMult(int newNum) : num(newNum), mult(1) {}
};


class DataPlot
{
public:
    void insert(int newNum);
    int minimum() { if (!sorted) sort(); return data[0].num; }
    int maximum() { if (!sorted) sort(); return data[data.size()].num; }
    int total() const;
    double mean() const;
    int median();
    double percentage(const int xVal);
    
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

