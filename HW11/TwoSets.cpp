#include <unordered_map>
#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <set>

class Edge
{
public:
    Edge(const int v1, const int v2, const int length);

    int getV1() const;
    int getV2() const;
    int getLength() const;
private:
    int v1;
    int v2;
    int length;
};

Edge::Edge(const int v1, const int v2, const int length)
    :v1(v1), v2(v2), length(length)
{ }

int Edge::getV1() const
{
    return this->v1;
}

int Edge::getV2() const
{
    return this->v2;
}

int Edge::getLength() const
{
    return this->length;
}

class EdgeWeightedGraph
{
public:
    EdgeWeightedGraph(const int T);
    void addEdge(const int v1, const int v2, const int length);

    long getShortestDistanceToT(const int sVertex);
    void findShortestDistancesFromT();
private:
    const int T;
    std::unordered_map<int, std::list<std::pair<int, int>>> vertices;
    std::unordered_map<int, long> distances;
};

EdgeWeightedGraph::EdgeWeightedGraph(const int T)
    :T(T)
{ }

void EdgeWeightedGraph::addEdge(const int v1, const int v2, const int length)
{
    this->vertices[v1].push_back({ v2, length });
    this->vertices[v2].push_back({ v1, length });
}

long EdgeWeightedGraph::getShortestDistanceToT(const int sVertex)
{
    return this->distances[sVertex];
}

void EdgeWeightedGraph::findShortestDistancesFromT()
{
    this->distances.clear();
    for (const auto& pair : this->vertices)
    {
        this->distances[pair.first] = LONG_MAX;
    }
    this->distances[this->T] = 0;

    std::set<std::pair<long, int>> container;
    container.insert({ 0, T });
    while (!container.empty())
    {
        int currentVertex = (*container.begin()).second;
        container.erase(container.begin());

        for (const auto& pair : this->vertices[currentVertex])
        {
            int childVertex = pair.first;
            int edgeLength = pair.second;
            if (this->distances[currentVertex] + edgeLength < this->distances[childVertex])
            {
                container.erase({ this->distances[childVertex], childVertex });
                this->distances[childVertex] = this->distances[currentVertex] + edgeLength;
                container.insert({ this->distances[childVertex], childVertex });
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    std::vector<Edge> edges;
    std::unordered_map<int, bool> ST;
    for (int i = 0; i < M; ++i)
    {
        int v1, v2, length;
        std::cin >> v1 >> v2 >> length;
        edges.push_back(Edge(v1, v2, length));
        ST[v1] = false;
        ST[v2] = false;
    }

    int K;
    std::cin >> K;
    for (int i = 0; i < K; ++i)
    {
        int tVertex;
        std::cin >> tVertex;
        ST[tVertex] = true;
    }

    const int T = -1;
    EdgeWeightedGraph graph(T);
    for (const Edge& edge : edges)
    {
        int v1 = edge.getV1();
        int v2 = edge.getV2();
        int length = edge.getLength();

        if (ST[v1] && ST[v2])
        {
            continue;
        }
        else if (ST[v1])
        {
            graph.addEdge(T, v2, length);
        }
        else if (ST[v2])
        {
            graph.addEdge(v1, T, length);
        }
        else
        {
            graph.addEdge(v1, v2, length);
        }
    }

    graph.findShortestDistancesFromT();

    int Q;
    std::cin >> Q;
    std::vector<long> result;
    for (int i = 0; i < Q; ++i)
    {
        int sVertex;
        std::cin >> sVertex;
        result.push_back(graph.getShortestDistanceToT(sVertex));
    }

    for (int i = 0; i < Q; ++i)
    {
        std::cout << result[i] << '\n';
    }

    return 0;
}