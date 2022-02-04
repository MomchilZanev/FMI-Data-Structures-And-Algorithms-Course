#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

double  calculateMedian(std::multimap<int, int>& population, std::multimap<int, int>::iterator& middle, const int income)
{
    double median;
    if (population.size() == 1)
    {
        middle = population.begin();
        median = (double)(*middle).first;
    }
    else if (population.size() % 2 == 0)
    {
        if (income < (*middle).first)
        {
            --middle;
        }
        auto next = middle;
        ++next;
        median = (double)(*middle).first + ((double)(*next).first - (double)(*middle).first) / 2;
    }
    else
    {
        if (income >= (*middle).first)
        {
            ++middle;
        }
        median = (double)(*middle).first;
    }

    return median;
}

void doStatistics(std::multimap<int, int>& population, std::vector<double>& results, const int N)
{
    int income;
    std::cin >> income;
    population.insert({ income, 0 });
    results[0] = income;
    auto middle = population.begin();
    for (int i = 1; i < N; ++i)
    {
        std::cin >> income;
        population.insert({ income, i });

        results[i] = calculateMedian(population, middle, income);
    }
}

void printResults(const std::vector<double>& results, const int N)
{
    std::cout << std::fixed << std::setprecision(1);

    for (int i = 0; i < N; ++i)
    {
        std::cout << results[i] << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);    

    int N;
    std::cin >> N;
    
    std::multimap<int, int> population;
    std::vector<double> results(N);

    doStatistics(population, results, N);
    printResults(results, N);

    return 0;
}