#include <algorithm>
#include <iostream>
#include <vector>

class Road
{
public:
    Road(const int index, const int city1, const int city2, const long effort, const long gain);
    bool operator<(const Road& rhs) const;

    int getIndex() const;
    int getCity1() const;
    int getCity2() const;
    long getEffort() const;
    long getGain() const;
private:
    int index;
    int city1;
    int city2;
    long effort;
    long gain;
};

Road::Road(const int index, const int city1, const int city2, const long effort, const long gain)
    :index(index), city1(city1), city2(city2), effort(effort), gain(gain)
{ }

bool Road::operator<(const Road& rhs) const
{
    if (this->getEffort() < rhs.getEffort())
    {
        return true;
    }
    else if (this->getEffort() == rhs.getEffort())
    {
        return this->getGain() > rhs.getGain();
    }

    return false;
}

int Road::getIndex() const
{
    return this->index;
}

int Road::getCity1() const
{
    return this->city1;
}

int Road::getCity2() const
{
    return this->city2;
}

long Road::getEffort() const
{
    return this->effort;
}

long Road::getGain() const
{
    return this->gain;
}

int findRoot(int* parent, const int city)
{
    if (parent[city] == city)
    {
        return city;
    }

    return parent[city] = findRoot(parent, parent[city]);
}

void kruskal(std::vector<Road>& roads, int* parent, std::vector<int>& result, const int N)
{
    std::sort(roads.begin(), roads.end());

    int roadsBuilt = 0;
    for (const auto& road : roads)
    {
        if(roadsBuilt == N - 1)
        {
            break;
        }
        const int root1 = findRoot(parent, road.getCity1());
        const int root2 = findRoot(parent, road.getCity2());

        if (root1 != root2)
        {
            parent[root2] = root1;
            result.push_back(road.getIndex());
            ++roadsBuilt;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    int* parent = new int[N];
    for (int i = 0; i < N; ++i)
    {
        parent[i] = i;
    }

    std::vector<Road> roads;
    for (int i = 0; i < M; ++i)
    {
        int city1, city2;
        long effort, gain;
        std::cin >> city1 >> city2 >> effort >> gain;
        --city1;
        --city2;
        roads.push_back(Road(i + 1, city1, city2, effort, gain));
    }

    std::vector<int> result;
    kruskal(roads, parent, result, N);

    for (const int index : result)
    {
        std::cout << index << '\n';
    }

    delete[] parent;

    return 0;
}