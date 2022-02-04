#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

void countingSort(std::vector<int>& arr);

int main() 
{
    int N;    
    std::string input;

    std::cin >> N;
    std::cin >> input;

    std::vector<int> numbers;
    for (int i = 0; i < N; i++)
    {
        char current = input[i];
        int dec = (int)current;

        if (dec >= 48 && dec <= 57)
        {
            numbers.push_back(dec - 48 + 1);
        }
        else if (dec >= 97 && dec <= 122)
        {
            numbers.push_back(dec - 97 + 11);
        }
        else if (dec >= 65 && dec <= 90)
        {
            numbers.push_back(dec - 65 + 37);
        }
    }

    countingSort(numbers);

    for (int i = 0; i < N; i++)
    {
        int num = numbers[i];

        if (num >= 1 && num <= 10)
        {
            std::cout << (char)(num + 48 - 1);
        }
        else if (num >= 11 && num <= 36)
        {
            std::cout << (char)(num + 97 - 11);
        }
        else if (num >= 37 && num <= 62)
        {
            std::cout << (char)(num + 65 - 37);
        }
    }

    return 0;
}

void countingSort(std::vector<int>& arr) 
{
    std::vector<int> map(62, 0);

    for (int num : arr) 
    {
        map[num - 1]++;
    }

    int index = 0;

    for (int num = 0; num < 62; num++) 
    {
        while (map[num] > 0) 
        {
            arr[index++] = num + 1;
            map[num]--;
        }
    }
}