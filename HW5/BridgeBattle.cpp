#include <iostream>
#include <list>

int main()
{
    int N;
    std::cin >> N;

    std::list<int> bridge;
    for (int i = 0; i < N; ++i)
    {
        int currentWarrior;
        std::cin >> currentWarrior;
        bridge.push_back(currentWarrior);
    }

    std::list<int> groupL;
    std::list<int> groupR;
    while (!bridge.empty())
    {
        while (!bridge.empty() && bridge.front() >= 0)
        {
            groupL.push_back(bridge.front());
            bridge.pop_front();
        }
        while (!bridge.empty() && bridge.front() < 0)
        {
            groupR.push_front(bridge.front());
            bridge.pop_front();
        }

        if (groupR.empty())
        {
            break;
        }

        while (!groupL.empty() && !groupR.empty())
        {
            if (std::abs(groupL.back()) == std::abs(groupR.back()))
            {
                groupL.pop_back();
                groupR.pop_back();
            }
            else if (std::abs(groupL.back()) > std::abs(groupR.back()))
            {
                groupR.pop_back();
            }
            else
            {
                groupL.pop_back();
            }
        }

        while (!groupR.empty())
        {
            std::cout << groupR.back() << ' ';
            groupR.pop_back();
        }
    }

    for (const auto warrior : groupL)
    {
        std::cout << warrior << ' ';
    }
    std::cout << '\n';

    return 0;
}