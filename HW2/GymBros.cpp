#include <cmath> 
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

struct GoodFella
{
    int index;

    short weightDiameter;
    short timeToMove;
};

void merge(std::vector<GoodFella>& arr, int lFrom, int lTo, int rFrom, int rTo);
void mergeSort(std::vector<GoodFella>& arr, int from, int to);

int main() 
{
    int N;
    std::cin >> N;

    std::vector<GoodFella> goodFellas;
    for (int i = 0; i < N; i++)
    {
        short di, ti;
        std::cin >> di >> ti;
        GoodFella fella;
        fella.index = i + 1;
        fella.weightDiameter = di;
        fella.timeToMove = ti;

        goodFellas.push_back(fella);
    }

    mergeSort(goodFellas, 0, goodFellas.size() - 1);

    for (const auto& fella : goodFellas)
    {
        std::cout << fella.index << ' ';
    }

    return 0;
}

double getEfficiency(GoodFella& fella)
{
    double radius = (double)fella.weightDiameter / 2;
    return (radius * radius) / (double)fella.timeToMove;
}

bool LIsMoreEfficientThanR(GoodFella& lFella, GoodFella& rFella)
{
    if (getEfficiency(lFella) < getEfficiency(rFella))
    {
        return false;
    }
    else if (getEfficiency(lFella) > getEfficiency(rFella))
    {
        return true;
    }

    if (lFella.weightDiameter < rFella.weightDiameter)
    {
        return false;
    }
    else if (lFella.weightDiameter > rFella.weightDiameter)
    {
        return true;
    }

    return true;
}

void mergeSort(std::vector<GoodFella>& arr, int from, int to)
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

void merge(std::vector<GoodFella>& arr, int lFrom, int lTo, int rFrom, int rTo)
{
    std::vector<GoodFella> lArr;
    std::vector<GoodFella> rArr;

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
        if (LIsMoreEfficientThanR(lArr[lIndex], rArr[rIndex]))
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