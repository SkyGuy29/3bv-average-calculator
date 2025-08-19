#include "DataPlot.h"


void DataPlot::load(Difficulty diffic)
{
    data.clear();
    std::ifstream file("3bvData/" + diffData[diffic].fileName);
    unsigned x, y;

    do
    {
        file >> x >> y;
        data.emplace_back(x, y);
    } while (!file.eof());
}


void DataPlot::insert(unsigned newNum)
{
    bool inserted = false;

    for (auto & i : data)
        if (i.num == newNum)
        {
            i.mult++;
            inserted = true;
        }

    if (!inserted)
        data.emplace_back(newNum);

    sorted = false;
}


unsigned DataPlot::q1()
{
    double count = 0;
    const auto tot = total();

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


unsigned DataPlot::median()
{
    double count = 0;
    const auto tot = total();

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


double DataPlot::stdDev() const
{
    const double theMean = mean();
    double sum = 0;

    for (const auto i : data)
		sum += (i.num - theMean) * (i.num - theMean) * i.mult;

    return sqrt(sum / total());
}


unsigned DataPlot::q3()
{
    double count = 0;
    const auto tot = total();

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


unsigned long DataPlot::total() const
{
    unsigned long total = 0;

    for (const auto i: data)
        total += i.mult;

    return total;
}


double DataPlot::percentage(const unsigned xVal)
{
    const unsigned med = median();
    double sum = 0;

    if (!sorted)
        sort();

    if (xVal <= med) //lower bound
    {
        for (const auto i : data)
        {
            if (i.num <= xVal)
                sum += i.mult;
            else
                return sum / total();
        }
    }
    else //upper bound
    {
        for (const auto i : data)
            if (i.num >= xVal)
                sum += i.mult;
        
        return sum / total();
    }

    return -1;
}


void DataPlot::save(Difficulty diffic)
{
    if (!sorted)
        sort();

    std::ofstream file("3bvData/" + diffData[diffic].fileName);

    for (const auto i : data)
    {
        file << i.num << ' ' << i.mult;
        if (i.num != data[data.size() - 1].num)
            file << '\n';
    }
}