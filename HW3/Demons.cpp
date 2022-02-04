#include <vector>
#include <iostream>

struct Demon
{
    int defense;
    int attack;
    Demon(const int& defense, const int& attack)
    {
        this->defense = defense;
        this->attack = attack;
    }
};

inline bool demonLDefeatsDemonR(const Demon& demonL, const Demon& demonR)
{
    return demonL.attack > demonR.attack && demonL.defense > demonR.defense;
}

inline bool demonLIsWeakerThanDemonR(const Demon& demonL, const Demon& demonR)
{
    if (demonLDefeatsDemonR(demonR, demonL))
    {
        return true;
    }
    else if (demonLDefeatsDemonR(demonL, demonR))
    {
        return false;
    }

    return std::min(demonL.defense, demonL.attack) < std::min(demonR.defense, demonR.attack);
}

void merge(std::vector<Demon>& arr, const int& lFrom, const int& lTo, const int& rFrom, const int& rTo)
{
    std::vector<Demon> lArr;
    std::vector<Demon> rArr;

    for (int i = lFrom; i <= lTo; ++i)
    {
        lArr.push_back(arr[i]);
    }
    for (int i = rFrom; i <= rTo; ++i)
    {
        rArr.push_back(arr[i]);
    }

    int lIndex = 0, rIndex = 0, aIndex = lFrom;
    while (lIndex < lArr.size() && rIndex < rArr.size())
    {
        if (demonLIsWeakerThanDemonR(lArr[lIndex], rArr[rIndex]))
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

void mergeSort(std::vector<Demon>& arr, const int& from, const int& to)
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

int getMostDemonsDefeated(const std::vector<Demon>& demons, const int& n)
{
    std::vector<int> maxDemonsDefeated(n, 0);
    maxDemonsDefeated[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (demonLDefeatsDemonR(demons[i], demons[j]) && maxDemonsDefeated[j] > maxDemonsDefeated[i])
            {
                maxDemonsDefeated[i] = maxDemonsDefeated[j];
            }
        }
        ++maxDemonsDefeated[i];
    }

    int result = 0;
    for (int i = 0; i < n; ++i)
    {
        result = std::max(result, maxDemonsDefeated[i]);
    }

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Demon> demons;

    for (int i = 0; i < n; ++i)
    {
        int defense, attack;
        std::cin >> defense >> attack;
        Demon currentDemon(defense, attack);
        demons.push_back(currentDemon);
    }
    mergeSort(demons, 0, n - 1);

    printf("%d", getMostDemonsDefeated(demons, n));

    return 0;
}