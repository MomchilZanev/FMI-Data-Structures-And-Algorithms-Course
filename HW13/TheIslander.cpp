#include <iostream>

const int GRAPH_SIZE = (int)1e5;

void resetParent(int parent[GRAPH_SIZE])
{
    for (int i = 0; i < GRAPH_SIZE; ++i)
    {
        parent[i] = i;
    }
}

void resetDegree(int degree[GRAPH_SIZE])
{
    for (int i = 0; i < GRAPH_SIZE; ++i)
    {
        degree[i] = 0;
    }
}

int findRoot(int parent[GRAPH_SIZE], const int v)
{
    if (parent[v] == v)
    {
        return v;
    }

    return parent[v] = findRoot(parent, parent[v]);
}

void connect(int parent[GRAPH_SIZE], int degree[GRAPH_SIZE], const int v1, const int v2, int& components)
{
    const int root1 = findRoot(parent, v1);
    const int root2 = findRoot(parent, v2);

    ++degree[v1];
    ++degree[v2];

    if (root1 != root2)
    {
        parent[root2] = root1;
        --components;
    }
}

//0 - no eulerian path, 1 - eulerian path , 2 - eulerian cycle
int isEulerian(int degree[GRAPH_SIZE], const int componentsCount)
{
    if (componentsCount != 1)
    {
        return 0;
    }

    int odd = 0;
    for (int i = 0; i < GRAPH_SIZE; ++i)
    {
        if (degree[i] % 2 != 0)
        {
            ++odd;
        }
    }

    if (odd > 2 || odd == 1)
    {
        return 0;
    }

    return odd == 0 ? 2 : 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Q;
    std::cin >> Q;

    int parent[GRAPH_SIZE];
    int degree[GRAPH_SIZE];
    for (int i = 0; i < Q; ++i)
    {
        int N, M;
        std::cin >> N >> M;

        resetParent(parent);
        resetDegree(degree);
        int components = N;
        for (int j = 0; j < M; ++j)
        {
            int a, b;
            std::cin >> a >> b;
            connect(parent, degree, a, b, components);
        }

        int eulerian = isEulerian(degree, components);
        switch (eulerian)
        {
        case 1:
            std::cout << "epath" << '\n';
            break;
        case 2:
            std::cout << "ecycle" << '\n';
            break;
        default:
            std::cout << "none" << '\n';
            break;
        }
    }

    return 0;
}