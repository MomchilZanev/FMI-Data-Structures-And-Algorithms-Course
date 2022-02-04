#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merge(std::vector<int>& arr, int lFrom, int lTo, int rFrom, int rTo);
void mergeSort(std::vector<int>& arr, int from, int to);

int main() 
{
    int N;
    std::vector<int> presents;
    int K;

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        int present;
        std::cin >> present;
        presents.push_back(present);
    }
    std::cin >> K;

    mergeSort(presents, 0, presents.size() - 1);

    long result = 0;
    for (int i = 0; i < K; i++)
    {
        result += presents[i];
    }

    std::cout << result;

    return 0;
}

void mergeSort(std::vector<int>& arr, int from, int to)
{
    if (from >= to)
    {
        return;
    }

    int mid = (from + to) / 2;

    mergeSort(arr, from, mid);
    mergeSort(arr, mid + 1, to);

    merge(arr, from, mid, mid + 1, to);
}

void merge(std::vector<int>& arr, int lFrom, int lTo, int rFrom, int rTo)
{
    std::vector<int> lArr;
    std::vector<int> rArr;

    for (int i = lFrom; i <= lTo; i++)
    {
        lArr.push_back(arr[i]);
    }

    for (int i = rFrom; i <= rTo; i++)
    {
        rArr.push_back(arr[i]);
    }


    int lIndex = 0, rIndex = 0, aIndex = lFrom;
    while (lIndex < lArr.size() && rIndex < rArr.size())
    {
        if (lArr[lIndex] < rArr[rIndex])
        {
            arr[aIndex++] = lArr[lIndex++];
        }
        else
        {
            arr[aIndex++] = rArr[rIndex++];
        }
    }

    while (lIndex < lArr.size())
    {
        arr[aIndex++] = lArr[lIndex++];
    }

    while (rIndex < rArr.size())
    {
        arr[aIndex++] = rArr[rIndex++];
    }
}