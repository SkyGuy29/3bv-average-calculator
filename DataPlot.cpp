#include "DataPlot.h"


void DataPlot::insert(int newNum)
{
    bool inserted = false;

    for (auto & i : data)
    {
        if (i.num == newNum)
        {
            i.mult++;
            inserted = true;
        }
    }

    if (!inserted)
    {
        data.emplace_back(newNum);
    }

    sorted = false;
}


int DataPlot::total() const
{
    int total = 0;

    for (const auto i: data)
    {
        total += i.mult;
    }

    return total;
}


double DataPlot::mean() const
{
    double sum = 0, total = 0;

    for (const auto i : data)
    {
        sum += i.num * i.mult;
        total += i.mult;
    }

    return sum / total;
}


int DataPlot::median()
{
    double count = 0;
    const int tot = total();

    if (!sorted)
        sort();

    for (const auto i : data)
    {
        if (count + i.mult < tot / 2)
            count += i.mult;
        else
            return i.num;
    }
}


double DataPlot::percentage(const int xVal)
{
    const int med = median();
    double sum = 0;

    if (!sorted)
        sort();

    if (xVal <= med)
    {
        for (const auto i : data)
        {
            if (i.num <= xVal)
            {
                sum += i.mult;
            }
            else
                return sum / total();
        }
    }
    else
    {
        for (const auto i : data)
        {
            if (i.num >= xVal)
            {
                sum += i.mult;
            }
        }
        return sum / total();
    }
}