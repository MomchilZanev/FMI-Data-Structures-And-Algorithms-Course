#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

void merge(std::vector<std::pair<std::string, int>>& arr, int lFrom, int lTo, int rFrom, int rTo);
void mergeSort(std::vector<std::pair<std::string, int>>& arr, int from, int to);

int main() 
{
    int N;
    std::vector<std::pair<std::string, int>> timestamps;

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        std::string time;
        std::string date;
        std::cin >> time;
        std::cin >> date;
        std::string dateTime = time.append(" ");
        dateTime = dateTime.append(date);
        std::pair<std::string, int> pair(dateTime, i + 1);
        timestamps.push_back(pair);
    }

    mergeSort(timestamps, 0, timestamps.size() - 1);

    for (int i = 0; i < N; i++)
    {
        std::cout << timestamps[i].second << '\n';
    }

    return 0;
}

bool lIsBeforeR(std::string& l, std::string& r)
{
    int lYear = std::stoi(l.substr(15, 4));
    int lMonth = std::stoi(l.substr(12, 2));
    int lDay = std::stoi(l.substr(9, 2));
    int lHours = std::stoi(l.substr(0, 2));
    int lMinutes = std::stoi(l.substr(3, 2));
    int lSeconds = std::stoi(l.substr(6, 2));

    int rYear = std::stoi(r.substr(15, 4));
    int rMonth = std::stoi(r.substr(12, 2));
    int rDay = std::stoi(r.substr(9, 2));
    int rHours = std::stoi(r.substr(0, 2));
    int rMinutes = std::stoi(r.substr(3, 2));
    int rSeconds = std::stoi(r.substr(6, 2));

    if (lYear < rYear)
    {
        return true;
    }
    else if (lYear > rYear)
    {
        return false;
    }

    if (lMonth < rMonth)
    {
        return true;
    }
    else if (lMonth > rMonth)
    {
        return false;
    }

    if (lDay < rDay)
    {
        return true;
    }
    else if (lDay > rDay)
    {
        return false;
    }

    if (lHours < rHours)
    {
        return true;
    }
    else if (lHours > rHours)
    {
        return false;
    }

    if (lMinutes < rMinutes)
    {
        return true;
    }
    else if (lMinutes > rMinutes)
    {
        return false;
    }

    if (lSeconds < rSeconds)
    {
        return true;
    }
    else if (lSeconds > rSeconds)
    {
        return false;
    }

    return true;
}

void mergeSort(std::vector<std::pair<std::string, int>>& arr, int from, int to)
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

void merge(std::vector<std::pair<std::string, int>>& arr, int lFrom, int lTo, int rFrom, int rTo)
{
    std::vector<std::pair<std::string, int>> lArr;
    std::vector<std::pair<std::string, int>> rArr;

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
        if (lIsBeforeR(lArr[lIndex].first, rArr[rIndex].first))
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