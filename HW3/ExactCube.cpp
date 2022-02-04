#include <iostream>

long getLargestCubeLessThanOrEqualTo(long number)
{
    long result = 1;
    long step = 1;
    while (true)
    {
        step++;
        long tempResult = step * step * step;
        if (tempResult < number)
        {
            result = tempResult;
        }
        else if (tempResult == number)
        {
            result = tempResult;
            break;
        }
        else
        {
            break;
        }
    }
    return result;
}

int main()
{
    long mimisPoints;
    std::cin >> mimisPoints;

    int presentsBought = 0;
    while (mimisPoints > 0)
    {
        mimisPoints -= getLargestCubeLessThanOrEqualTo(mimisPoints);
        presentsBought++;
    }

    std::cout << presentsBought;

    return 0;
}