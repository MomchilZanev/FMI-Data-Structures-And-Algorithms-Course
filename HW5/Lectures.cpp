#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() 
{
    std::string input;
    std::cin >> input;

    std::vector<int> characterMap(128, 0);
    std::vector<int> characterIndexMap(128);

    for (int i = 0; i < input.size(); ++i)
    {
        characterMap[(int)input[i]]++;
        characterIndexMap[(int)input[i]] = i;
    }

    std::vector<int> result;
    for (int i = 0; i < 128; ++i)
    {
        if (characterMap[i] == 1)
        {
            result.push_back(characterIndexMap[i]);
        }
    }

    std::sort(result.begin(), result.end());
    for (const int index : result)
    {
        std::cout << index << ' ';
    }

    return 0;
}