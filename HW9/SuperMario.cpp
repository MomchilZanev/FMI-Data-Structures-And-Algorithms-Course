#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    int N;
    std::cin >> N;
    
    std::vector<int> keys(N);
    for (int i = 0; i < N; ++i)
    {
        int key;
        std::cin >> key;
        keys[i] = key;
    }

    unsigned brokenDoors = 0;
    std::unordered_map<int, int> keysMap;
    for (int i = 0; i < N; ++i)
    {
        int door;
        std::cin >> door;

        ++keysMap[keys[i]];

        if (keysMap[door] >= 1)
        {
            --keysMap[door];
        }
        else
        {
            ++brokenDoors;
        }
    }

    std::cout << brokenDoors;

    return 0;
}