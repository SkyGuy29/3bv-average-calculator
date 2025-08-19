#include "DataPlot.h"
#include "Field.h"
#include <iostream>
#include <cmath>


int main()
{
    Field field;
    DataPlot data;
    int input = 0;
    char charInput;
	double percentage, marginOfError;

    data.load(field.getDifficulty());

    do
    {
		std::cout << field.getSizeX() << 'x' << field.getSizeY()
			<< ", " << field.getMines() << " mines\n\n";

        std::cout << "Choose an option:\n"
            << "0: exit\n"
            << "1: change difficulty\n"
            << "2: generate boards\n"
            << "3: print stats\n"
            << "4: find probability\n\n"
            << "choose: ";
        std::cin >> charInput;
        std::cout << '\n';

		switch (charInput)
		{
			case '0':
				break;
			case '1':
				std::cout << "Choose a difficulty:\n"
				    << "0: Beginner (9x9/10)\n"
				    << "1: Intermediate (16x16/40)\n"
				    << "2: Expert (30x16/99)\n"
				    << "3: Google minesweeper hard (24x20/99)\n"
				    << "4: Evil (30x20/130)\n"
				    << "5: Custom\n\n"
					<< "choose: ";
				std::cin >> input;
				std::cout << '\n';
                if (input != COUNT)
					field.setDifficulty(static_cast<Difficulty>(input));
                else
                {
					int sizeX, sizeY, mines;
					std::cout << "Enter size X: ";
					std::cin >> sizeX;
					std::cout << "Enter size Y: ";
					std::cin >> sizeY;
					std::cout << "Enter number of mines: ";
					std::cin >> mines;

					//field.setCustom(sizeX, sizeY, mines);

                    //todo:
                    // - finish custom
                    // - opening distribution
                    // - zini distribution 
				}
				data.load(field.getDifficulty());
				break;
			case '2':
                std::cout << "How many boards to generate? Current total: "
					<< data.total() << "\n";
				std::cin >> input;

                if (input > 0)
				{
                    std::cout << "\nGenerating " << input << " boards. Closing now will not save.\n";

                    for (int i = 1; i <= input; i++)
                    {
                        field.reset();
                        data.insert(field.find3BV());
                        if (i % (input / 20) == 0)
	                        std::cout << '#'; //progress bar
                    }

                    std::cout << "\n\n";

                	data.save(field.getDifficulty());
				}
                else if (input == 0)
                {
                    std::cout << "\nNo boards generated.\n";
                    break;
                }
                else
                {
					std::cout << "\nInvalid input.\n\n";
                    break;
                }
			case '3':
                std::cout << "Total boards checked: " << data.total()
                    << "\nmin 3bv: " << data.minimum()
                    << "\nq1: " << data.q1()
                    << "\nmedian: " << data.median()                                    
                    << "\nmean: " << data.mean()
					<< "\nstandard deviation: " << data.stdDev()
                    << "\nq3: " << data.q3()
                    << "\nmax 3bv: " << data.maximum()
                    << "\n\n";
				break;
            case '4':
                std::cout << "3bv: ";
                std::cin >> input;
                percentage = data.percentage(input);
                std::cout << percentage * 100 << "% chance! (" << percentage <<")\n";
                std::cout << "this board has a 1 in " << 1 / percentage << " chance of generating.\n";

                marginOfError = 2.576 * sqrt(percentage * (1 - percentage) / data.total());
                std::cout << "99% confidence interval:\n"
                    << '(' << percentage - marginOfError << ", " << percentage + marginOfError << ")\n\n";
                break;
			default:
				std::cout << "Invalid input.\n\n";
				break;
		}

    } while (charInput != '0');
}