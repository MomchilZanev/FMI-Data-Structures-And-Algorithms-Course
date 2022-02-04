#include <iostream>
#include <climits>
#include <list>
#include <set>

class EdgeWeightedDigraph
{
public:
    EdgeWeightedDigraph(const int verticesCount);
    ~EdgeWeightedDigraph();

    void addEdge(const int from, const int to, const int weight);

    std::pair<long, int> shortestPathsLengthAndCount(const int startingVertex, const int targetVertex);
private:
    int verticesCount;
    std::list<std::pair<int, int>>* vertices;
};

EdgeWeightedDigraph::EdgeWeightedDigraph(const int verticesCount)
    :verticesCount(verticesCount), vertices(new std::list<std::pair<int, int>>[verticesCount])
{ }

EdgeWeightedDigraph::~EdgeWeightedDigraph()
{
    delete[] this->vertices;
}

void EdgeWeightedDigraph::addEdge(const int from, const int to, const int weight)
{
    vertices[from - 1].push_back({ to - 1, weight });
}

std::pair<long, int> EdgeWeightedDigraph::shortestPathsLengthAndCount(const int startingVertex, const int targetVertex)
{
    long* distances = new long[this->verticesCount];
    std::fill(distances, distances + this->verticesCount, LONG_MAX);
    long* pathsCount = new long[this->verticesCount];

    distances[startingVertex] = 0;
    pathsCount[startingVertex] = 1;

    std::set<std::pair<long, int>> container;
    container.insert({ 0, startingVertex });

    while (!container.empty())
    {
        int currentVertex = (*container.begin()).second;
        container.erase(container.begin());

        for (const auto& pair : this->vertices[currentVertex])
        {
            int childVertex = pair.first;
            int edgeWeight = pair.second;
            if (distances[currentVertex] + edgeWeight < distances[childVertex])
            {
                container.erase({ distances[childVertex], childVertex });
                distances[childVertex] = distances[currentVertex] + edgeWeight;
                container.insert({ distances[childVertex], childVertex });
                pathsCount[childVertex] = pathsCount[currentVertex];
            }
            else if (distances[currentVertex] + edgeWeight == distances[childVertex])
            {
                pathsCount[childVertex] += pathsCount[currentVertex];
                pathsCount[childVertex] %= (long)(1e9 + 7);
            }
        }
    }

    int shortestPathsCount = pathsCount[targetVertex];

    long shortestPath = distances[targetVertex] == LONG_MAX ? -1 : distances[targetVertex];
    delete[] distances;
    delete[] pathsCount;
    return { shortestPath, shortestPathsCount };
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    EdgeWeightedDigraph graph(N);
    for (int i = 0; i < M; ++i)
    {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    int startingVertex = 0;
    int targetVertex = N - 1;

    const auto result = graph.shortestPathsLengthAndCount(startingVertex, targetVertex);
    std::cout << result.first << ' ' << result.second;

    return 0;
}