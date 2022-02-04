#include <iostream>
#include <vector>
#include <map>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, k;
    std::cin >> N >> k;

    std::vector<int> result(N);
    std::vector<int> numbers(N);
    for (int i = 0; i < N; ++i)
    {
        int number;
        std::cin >> number;
        numbers[i] = number;
        result[i] = -1;
    }

    std::multimap<int, int> container;
    for (int i = N - 1; i >= 0; --i)
    {
        int number = numbers[i];
        auto added = container.insert({ numbers[i], i });
        auto current = added;
        current.operator++();

        while (current != container.end())
        {
            int currentNumber = (*current).first;
            int currentIndex = (*current).second;
            if (currentNumber > number + k)
            {
                break;
            }
            if (currentNumber <= number + k && result[currentIndex] == -1)
            {
                result[currentIndex] = i;
                auto temp = current;
                temp.operator++();
                container.erase(current);
                current = temp;
                continue;
            }
            
            current.operator++();
        } 
    }

    for (int i = 0; i < N; ++i)
    {
        std::cout << result[i] << ' ';
    }

    return 0;
}