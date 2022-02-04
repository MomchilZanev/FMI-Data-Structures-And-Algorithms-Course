#include <iostream>
#include <list>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    auto graph = new std::list<int>[N];
    auto degree = new int[N];
    std::fill(degree, degree + N, 0);
    for (int i = 0; i < N - 1; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        ++degree[a];
        ++degree[b];
    }

    int verticesCount = N;
    std::list<int> leaves;
    for (int i = 0; i < N; ++i)
    {
        if (degree[i] == 1)
        {
            leaves.push_back(i);
        }
    }

    while (verticesCount != (int)leaves.size())
    {
        int currentLayer = leaves.size();
        verticesCount -= currentLayer;

        for (int i = 0; i < currentLayer; ++i)
        {
            int leaf = leaves.front();
            leaves.pop_front();
            degree[leaf] = 0;

            for (const auto adj : graph[leaf])
            {
                if (degree[adj] > 0)
                {
                    --degree[adj];

                    if (degree[adj] == 1)
                    {
                        leaves.push_back(adj);
                    }

                    break;
                }
            }
        }
    }

    leaves.sort();
    for (const auto root : leaves)
    {
        std::cout << root << ' ';
    }

    delete[] graph;
    delete[] degree;

    return 0;
}