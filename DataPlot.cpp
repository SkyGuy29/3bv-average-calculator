#include "DataPlot.h"


void DataPlot::load(Difficulties diffic)
{
    std::ifstream file(difficultyData[diffic].fileName);
    int x, y;

    do
    {
        file >> x >> y;
        data.emplace_back(x, y);
    } while (!file.eof());
}

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


int DataPlot::q1()
{
    double count = 0;
    const int tot = total();

    if (!sorted)
        sort();

    for (const auto i : data)
    {
        if (count + i.mult < tot / 4)
            count += i.mult;
        else
            return i.num;
    }
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


int DataPlot::q3()
{
    double count = 0;
    const int tot = total();

    if (!sorted)
        sort();

    for (const auto i : data)
    {
        if (count + i.mult < tot / 4 * 3)
            count += i.mult;
        else
            return i.num;
    }
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

void DataPlot::save(Difficulties diffic) const
{
    std::ofstream file(difficultyData[diffic].fileName);

    for (const auto i : data)
    {
        file << i.num << ' ' << i.mult;
        if (i.num != data[data.size() - 1].num)
        {
            file << '\n';
        }
    }
}