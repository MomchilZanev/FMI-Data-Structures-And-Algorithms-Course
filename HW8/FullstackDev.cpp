#include <iostream>
#include <vector>
#include <map>
#include <set>

int getTaskIndex(const std::multimap<int, std::pair<int, int>>::iterator& taskIterator)
{
    return (*taskIterator).second.second;
}

int getTaskStartingTime(const std::multimap<int, std::pair<int, int>>::iterator& taskIterator)
{
    return (*taskIterator).second.first;
}

int getTaskDuration(const std::multimap<int, std::pair<int, int>>::iterator& taskIterator)
{
    return (*taskIterator).first;
}

int getFirstTask(const std::multimap<int, int>& startingTimes)
{
    return (*startingTimes.begin()).first;
}

void doTasksInSpecifiedOrder(std::multimap<int, std::pair<int, int>>& tasks, std::multimap<int, int>& startingTimes, std::vector<int>& result)
{
    long currentTime = 1;
    while (!tasks.empty())
    {
        currentTime = currentTime < getFirstTask(startingTimes) ? getFirstTask(startingTimes) : currentTime;
        auto top = tasks.begin();

        auto current = top;
        while (current != tasks.end() && getTaskStartingTime(current) > currentTime)
        {
            ++current;
        }
        top = current;

        int optimalTime = getTaskDuration(top);
        while (current != tasks.end() && getTaskDuration(current) == optimalTime)
        {
            if (getTaskIndex(current) < getTaskIndex(top))
            {
                top = current;
            }
            ++current;
        }

        currentTime += getTaskDuration(top);
        result.push_back(getTaskIndex(top));
        startingTimes.erase(getTaskStartingTime(top));
        tasks.erase(top);        
    }
}

void getTasks(std::multimap<int, std::pair<int, int>>& tasks, std::multimap<int, int>& startingTimes, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        int startingTime, duration;
        std::cin >> startingTime >> duration;

        tasks.insert({ duration, { startingTime, i } });
        startingTimes.insert({ startingTime, i });
    }
}

void printResult(const std::vector<int>& result)
{
    int size = result.size();
    for (int i = 0; i < size; ++i)
    {
        std::cout << result[i] << ' ';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::multimap<int, std::pair<int, int>> tasks;
    std::multimap<int, int> startingTimes;
    std::vector<int> result;

    getTasks(tasks, startingTimes, N);
    doTasksInSpecifiedOrder(tasks, startingTimes, result);
    printResult(result);

    return 0;
}