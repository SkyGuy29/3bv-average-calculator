#include "DataPlot.h"
#include "Field.h"
#include <iostream>
#include <cmath>


int main()
{
    Field field;
    DataPlot data;
    int input = 0;
	double percentage, marginOfError;

    std::cout << SIZEA << 'x' << SIZEB
        << ", " << MINES << " mines\n";

    data.load(DIFF);

    for (int i = 1; i <= 1000000; i++)
    {
        field.reset();

        data.insert(field.find3BV());

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
    
    while (true)
    {
        std::cout << "\nhow rare is YOUR 3bv? \n3bv: ";
        std::cin >> input;
        percentage = data.percentage(input);
        std::cout << percentage * 100 << "% chance! (" << percentage <<")\n";

        marginOfError = 1.96 * sqrt(percentage * (1 - percentage) / data.total());

        std::cout << "95% confidence interval:\n"
    		<< '(' << percentage - marginOfError << ", " << percentage + marginOfError << ")\n";
    }
}