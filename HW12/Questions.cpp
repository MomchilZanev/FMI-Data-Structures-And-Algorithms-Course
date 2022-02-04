#include <iostream>

int findRoot(int* parent, const int v)
{
    if (parent[v] == v)
    {
        return v;
    }

    return parent[v] = findRoot(parent, parent[v]);
}

void connect(int* parent, const int v1, const int v2)
{
    const int root1 = findRoot(parent, v1);
    const int root2 = findRoot(parent, v2);

    if (root1 != root2)
    {
        parent[root2] = root1;
    }
}

bool areConnected(int* parent, const int v1, const int v2)
{
    const int root1 = findRoot(parent, v1);
    const int root2 = findRoot(parent, v2);

    return root1 == root2;
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

    for (int i = 0; i < M; ++i)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        connect(parent, v1, v2);
    }

    int Q;
    std::cin >> Q;

    for (int i = 0; i < Q; ++i)
    {
        int requestType, v1, v2;
        std::cin >> requestType >> v1 >> v2;
        --v1;
        --v2;
        if (requestType == 1)
        {
            std::cout << areConnected(parent, v1, v2);
        }
        else
        {
            connect(parent, v1, v2);
        }
    }

    delete[] parent;

    return 0;
}