#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

class Road
{
public:
    Road(const int city1, const int city2, const int optimalSpeed);
    bool operator<(const Road& rhs) const;

    int getCity1() const;
    int getCity2() const;
    int getOptimalSpeed() const;
private:
    int city1;
    int city2;
    int optimalSpeed;
};

Road::Road(const int city1, const int city2, const int optimalSpeed)
    :city1(city1), city2(city2), optimalSpeed(optimalSpeed)
{ }

bool Road::operator<(const Road& rhs) const
{
    return this->getOptimalSpeed() < rhs.getOptimalSpeed();
}

int Road::getCity1() const
{
    return this->city1;
}

int Road::getCity2() const
{
    return this->city2;
}

int Road::getOptimalSpeed() const
{
    return this->optimalSpeed;
}

int findRoot(int* parent, const int city)
{
    if (parent[city] == city)
    {
        return city;
    }

    return parent[city] = findRoot(parent, parent[city]);
}

void resetParent(int* parent, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        parent[i] = i;
    }
}

bool kruskal(std::vector<Road>& roads, int* parent, int& minSpeed, int& maxSpeed, const int N)
{
    int components = N;

    resetParent(parent, N);
    for (const auto& road : roads)
    {
        const int root1 = findRoot(parent, road.getCity1());
        const int root2 = findRoot(parent, road.getCity2());

        if (root1 != root2)
        {
            parent[root2] = root1;
            --components;

            minSpeed = std::min(minSpeed, road.getOptimalSpeed());
            maxSpeed = std::max(maxSpeed, road.getOptimalSpeed());
        }

        if (components == 1)
        {
            break;
        }
    }

    return components == 1;
}

std::pair<int, int> getClosestSpeeds(std::vector<Road>& roads, const int N)
{
    int minDiff = INT_MAX;
    int resultMinSpeed = -1;
    int resultMaxSpeed = -1;

    int* parent = new int[N];
    while (!roads.empty())
    {
        int minSpeed = INT_MAX;
        int maxSpeed = INT_MIN;
        if (!kruskal(roads, parent, minSpeed, maxSpeed, N))
        {
            break;
        }

        int newDiff = maxSpeed - minSpeed;
        if (newDiff < minDiff)
        {
            resultMinSpeed = minSpeed;
            resultMaxSpeed = maxSpeed;
            minDiff = newDiff;
        }

        roads.erase(roads.begin());
    }
    delete[] parent;

    return { resultMinSpeed, resultMaxSpeed };
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<Road> roads;
    for (int i = 0; i < M; ++i)
    {
        int city1, city2, optimalSpeed;
        std::cin >> city1 >> city2 >> optimalSpeed;

        roads.push_back(Road(--city1, --city2, optimalSpeed));
    }

    std::sort(roads.begin(), roads.end());
    std::pair<int, int> result = getClosestSpeeds(roads, N);

    std::cout << result.first << ' ' << result.second;

    return 0;
}