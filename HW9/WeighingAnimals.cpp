#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

long bsGetGreaterThanCount(const std::vector<long>& arr, const long lowerBound)
{
    long from = 0, to = arr.size() - 1;
    long resultIndex = -1;

    while (from <= to)
    {
        long middle = from + (to - from) / 2;

        if (arr[middle] > lowerBound)
        {
            to = middle - 1;
            resultIndex = middle;
        }
        else
        {
            from = middle + 1;
        }
    }

    return resultIndex == -1 ? 0 : arr.size() - resultIndex;
}

long bsGetSmallerThanCount(const std::vector<long>& arr, const long upperBound)
{
    long from = 0, to = arr.size() - 1;
    long resultIndex = -1;

    while (from <= to)
    {
        long middle = from + (to - from) / 2;

        if (arr[middle] < upperBound)
        {
            from = middle + 1;
            resultIndex = middle;
        }
        else
        {
            to = middle - 1;
        }
    }

    return resultIndex + 1;
}

long getTripletsCount(std::unordered_map<long, std::vector<long>>& animals, const long K)
{
    long tripletsCount = 0;
    auto currentIt = animals.begin();
    while (currentIt != animals.end())
    {
        long first = (*currentIt).first;
        long second = first * K;
        long third = second * K;

        bool secondExists = animals.count(second) > 0;
        bool thirdExists = animals.count(third) > 0;
        if (secondExists && thirdExists)
        {
            std::sort(animals[first].begin(), animals[first].end());
            std::sort(animals[third].begin(), animals[third].end());
            for (const auto y : animals[second])
            {
                long smallerThanYCount = bsGetSmallerThanCount(animals[first], y);
                long greaterThanYCount = bsGetGreaterThanCount(animals[third], y);

                tripletsCount += smallerThanYCount * greaterThanYCount;
            }
        }

        ++currentIt;
    }

    return tripletsCount;
}

void getAnimals(std::unordered_map<long, std::vector<long>>& animals, const long N)
{
    for (long i = 0; i < N; ++i)
    {
        long weight;
        std::cin >> weight;

        animals[weight].push_back(i);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long N, K;
    std::cin >> N >> K;

    std::unordered_map<long, std::vector<long>> animals;

    getAnimals(animals, N);
    std::cout << getTripletsCount(animals, K);

    return 0;
}