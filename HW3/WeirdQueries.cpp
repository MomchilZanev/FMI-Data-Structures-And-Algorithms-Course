#include <iostream>
#include <vector>

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

int getIndexOfClosestNotGreaterThan(const std::vector<int>& arr, int from, int to, int val)
{
    if (val < arr[0])
    {
        return -1;
    }
    if (val >= arr[to])
    {
        return to;
    }

    int rightmostIndex = -1;

    while (from <= to)
    {
        int mid = (from + to) / 2;

        if (arr[mid] == val)
        {
            rightmostIndex = mid;
            from = mid + 1;
        }
        else if (arr[mid] < val)
        {
            if (mid < to && val < arr[mid + 1])
            {
                rightmostIndex = mid;
                break;
            }

            from = mid + 1;
        }
        else
        {
            if (mid > 0 && val > arr[mid - 1])
            {
                rightmostIndex = mid - 1;
                break;
            }

            to = mid - 1;
        }
    }

    return rightmostIndex;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> numbers;
    for (int i = 0; i < N; ++i)
    {
        int number;
        std::cin >> number;
        numbers.push_back(number);
    }
    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < Q; ++i)
    {
        int S, P;
        std::cin >> S >> P;
        std::pair<int, int> query(S, P);
        queries.push_back(query);
    }

    mergeSort(numbers, 0, N - 1);

    for (int i = 0; i < Q; ++i)
    {
        int S = queries[i].first;
        int P = queries[i].second;
        int j = getIndexOfClosestNotGreaterThan(numbers, 0, N - 1, queries[i].second);

        int tmp = j;
        while (j >= 0)
        {
            S -= numbers[j];
            if (S < 0)
            {
                break;
            }
            --j;
        }

        std::cout << tmp - j << '\n';
    }

    return 0;
}