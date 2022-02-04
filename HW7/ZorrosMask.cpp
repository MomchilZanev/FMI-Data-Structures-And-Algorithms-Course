#include <iostream>
#include <set>

void addSubMasks(const unsigned number, std::set<unsigned>& submasks)
{
    for (int i = number; i >= 0; --i)
    {
        if ((number | i) == number)
        {
            submasks.insert(i);
        }
    }
}

int main()
{
    int N;
    std::cin >> N;
    std::set<unsigned> submasks;

    for (int i = 0; i < N; ++i)
    {
        unsigned number;
        std::cin >> number;
        addSubMasks(number, submasks);
    }

    std::cout << submasks.size();

    return 0;
}