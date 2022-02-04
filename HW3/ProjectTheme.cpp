#include <vector>
#include <iostream>

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

int getClosest(int num1, int num2, int val)
{
    int diff1 = std::abs(num1 - val);
    int diff2 = std::abs(num2 - val);
    if (diff1 < diff2)
    {
        return num1;
    }
    else if (diff1 == diff2)
    {
        return num1 <= num2 ? num1 : num2;
    }

    return num2;
}

int findClosestInDifficulty(std::vector<int>& arr, int from, int to, int val)
{
    if (val <= arr[0])
    {
        return arr[0];
    }
    if (val >= arr[to])
    {
        return arr[to];
    }


    while (from <= to)
    {
        int mid = (from + to + 1) / 2;

        if (arr[mid] == val)
        {
            return arr[mid];
        }

        if (arr[mid] < val)
        {
            if (mid < to && val < arr[mid + 1])
            {
                return getClosest(arr[mid + 1], arr[mid], val);
            }

            from = mid + 1;
        }
        else
        {
            if (mid > 0 && val > arr[mid - 1])
            {
                return getClosest(arr[mid - 1], arr[mid], val);
            }

            to = mid - 1;
        }
    }

    return false;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> subjectDifficulties;
    std::vector<int> teamSkills;
    for (int i = 0; i < n; i++)
    {
        int val;
        std::cin >> val;
        subjectDifficulties.push_back(val);
    }
    for (int i = 0; i < m; i++)
    {
        int val;
        std::cin >> val;
        teamSkills.push_back(val);
    }

    mergeSort(subjectDifficulties, 0, n - 1);

    for (int i = 0; i < m; i++)
    {
        int currentTeamSkill = teamSkills[i];

        int val = findClosestInDifficulty(subjectDifficulties, 0, n - 1, currentTeamSkill);

        std::cout << val << '\n';
    }

    return 0;
}