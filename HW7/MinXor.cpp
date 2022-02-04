#include <iostream>
#include <set>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    const unsigned TEN_POW_OF_NINE = 1000000000;

    int Q;
    std::cin >> Q;
    
    std::set<unsigned> elements{ 0 };
    unsigned minXor = TEN_POW_OF_NINE;    
    for (int i = 0; i < Q; ++i)
    {
        unsigned element;
        std::cin >> element;
        auto insertionRes = elements.insert(element);

        if (insertionRes.second == true)
        {
            auto addedIt = insertionRes.first;
            auto beforeAddedIt = addedIt;
            auto afterAddedIt = addedIt;

            --beforeAddedIt;
            ++afterAddedIt;

            minXor = std::min(minXor, *beforeAddedIt ^ *addedIt);

            if (afterAddedIt != elements.end())
            {
                minXor = std::min(minXor, *afterAddedIt ^ *addedIt);
            }
        }

        std::cout << minXor << '\n';
    }

    return 0;
}