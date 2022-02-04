#include <iostream>
#include <vector>
#include <list>

void getInput(int& N, int& d, std::vector<int>& arr)
{
    std::cin >> N >> d;

    for (int i = 0; i < N; ++i)
    {
        int num;
        std::cin >> num;
        arr.push_back(num);
    }
}

void clearLargerElements(const std::vector<int>& arr, std::list<int>& indexSubArr, const int index)
{
    while ((!indexSubArr.empty()) && arr[index] <= arr[indexSubArr.back()])
    {
        indexSubArr.pop_back();
    }
}

void clearElementsOutsideSubArr(std::list<int>& indexSubArr, const int currentSubArrStart)
{
    while ((!indexSubArr.empty()) && indexSubArr.front() < currentSubArrStart)
    {
        indexSubArr.pop_front();
    }
}

long getMinSum(const std::vector<int>& arr, const int N, const int d)
{
    long minSum = 0;
    std::list<int> indexSubArr;
    for (int i = 0; i < N; ++i)
    {
        int currentSubArrStart = std::max(0, i + 1 - d);
        clearElementsOutsideSubArr(indexSubArr, currentSubArrStart);

        clearLargerElements(arr, indexSubArr, i);

        indexSubArr.push_back(i);

        if (!indexSubArr.empty() && i >= d - 1)
        {
            minSum += arr[indexSubArr.front()];
        }
    }

    return minSum;
}

int main()
{
    int N, d;
    std::vector<int> arr;
    getInput(N, d, arr);

    long minSum = getMinSum(arr, N, d);
    std::cout << minSum;

    return 0;
}