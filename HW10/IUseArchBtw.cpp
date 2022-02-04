#include <iostream>
#include <unordered_map>
#include <list>
#include <map>

bool isBroken(std::map<int, std::list<int>>& hierarchy, std::unordered_map<int, bool>& visited, std::unordered_map<int, bool>& currentParents, const int currentDistro)
{
    visited[currentDistro] = true;
    currentParents[currentDistro] = true;

    for (const auto& child : hierarchy[currentDistro])
    {
        if (!visited[child])
        {
            if (isBroken(hierarchy, visited, currentParents, child))
            {
                return true;
            }
        }

        if (currentParents[child])
        {
            return true;
        }
    }
    currentParents[currentDistro] = false;

    return false;
}

bool distroHierarchyBroken(std::map<int, std::list<int>>& hierarchy)
{
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, bool> currentParents;

    for (const auto& current : hierarchy)
    {
        int currentDistro = current.first;
        if (!visited[currentDistro])
        {
            if (isBroken(hierarchy, visited, currentParents, currentDistro))
            {
                return true;
            }
        }
    }

    return false;
}

void getDistroHierarchy(std::map<int, std::list<int>>& hierarchy, const int ribsCount)
{
    for (int i = 0; i < ribsCount; ++i)
    {
        int start, end;
        std::cin >> start >> end;
        hierarchy[start].push_back(end);
    }
}

void getRequests(const int requestsCount)
{
    for (int i = 0; i < requestsCount; ++i)
    {
        int E;
        std::cin >> E;

        std::map<int, std::list<int>> hierarchy;
        getDistroHierarchy(hierarchy, E);

        std::cout << distroHierarchyBroken(hierarchy) << ' ';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Q;
    std::cin >> Q;

    getRequests(Q);

    return 0;
}