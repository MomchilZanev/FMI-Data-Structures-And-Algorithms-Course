#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <set>

void getSortedStrings(std::vector<std::string>& sortedStrings, const int N)
{
    for (int i = 0; i < N; ++i)
    {
        std::string input;
        std::cin >> input;
        sortedStrings[i] = input;
    }
}

void getAlphabet(std::map<char, std::set<char>>& alphabet, std::vector<std::string>& sortedStrings, const int N)
{
    for (int i = 0; i < N - 1; ++i)
    {
        std::string current = sortedStrings[i];
        std::string next = sortedStrings[i + 1];
        int minLength = std::min(current.length(), next.length());

        for (int j = 0; j < minLength; ++j)
        {
            if (current[j] != next[j])
            {
                char first = current[j];
                char second = next[j];

                alphabet[first].insert(second);

                break;
            }
        }
    }
}

void printSortedAlphabet(const std::list<char>& sortedAlphabet)
{
    auto it = sortedAlphabet.rbegin();
    while (it != sortedAlphabet.rend())
    {
        std::cout << *it << ' ';
        ++it;
    }
}

void topologicalSort(std::map<char, std::set<char>>& alphabet, std::unordered_map<char, bool>& visited, std::list<char>& sortedAlphabet, const char letter)
{
    visited[letter] = true;

    for (const auto child : alphabet[letter])
    {
        if (!visited[child])
        {
            topologicalSort(alphabet, visited, sortedAlphabet, child);
        }
    }

    sortedAlphabet.push_back(letter);
}

void sortAlphabet(std::map<char, std::set<char>>& alphabet, std::list<char>& sortedAlphabet)
{
    std::unordered_map<char, bool> visited;
    for (const auto vertex : alphabet)
    {
        char letter = vertex.first;
        if (!visited[letter])
        {
            topologicalSort(alphabet, visited, sortedAlphabet, letter);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::string> sortedStrings(N);
    getSortedStrings(sortedStrings, N);

    std::map<char, std::set<char>> alphabet;
    getAlphabet(alphabet, sortedStrings, N);

    std::list<char> sortedAlphabet;
    sortAlphabet(alphabet, sortedAlphabet);

    printSortedAlphabet(sortedAlphabet);

    return 0;
}