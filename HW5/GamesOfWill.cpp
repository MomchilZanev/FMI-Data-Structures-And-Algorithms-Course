#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

int main()
{
    int N;
    std::cin >> N;

    std::vector<std::pair<int, int>> nearestSmallerNumber(N, std::pair<int, int>(-1, -1));
    std::vector<int> participants;
    for (int i = 0; i < N; ++i)
    {
        int participantHunger;
        std::cin >> participantHunger;
        participants.push_back(participantHunger);
    }

    std::list<std::pair<int, int>> temp;
    for (int i = 0; i < N; ++i)
    {
        while (!temp.empty() && temp.back().second >= participants[i])
        {
            temp.pop_back();
        }

        if (!temp.empty())
        {
            nearestSmallerNumber[i] = temp.back();
        }

        std::pair<int, int> newEntry(i, participants[i]);
        temp.push_back(newEntry);
    }

    std::vector<int> distanceToNearest(N);
    for (int i = 0; i < N; ++i)
    {
        if (nearestSmallerNumber[i].first == -1)
        {
            distanceToNearest[i] = 0;
        }
        else
        {
            distanceToNearest[i] = i - nearestSmallerNumber[i].first;
        }
    }

    std::sort(distanceToNearest.begin(), distanceToNearest.end());
    int distinctCount = 0;
    for (int i = 0; i < N; ++i)
    {
        while (i < N - 1 && distanceToNearest[i] == distanceToNearest[i + 1])
        {
            ++i;
        }

        distinctCount++;
    }

    std::cout << distinctCount - 1;

    return 0;
}