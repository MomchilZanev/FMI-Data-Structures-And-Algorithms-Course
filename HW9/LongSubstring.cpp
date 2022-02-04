#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string firstLine, secondLine;
    std::cin >> firstLine >> secondLine;

    if (firstLine.size() < secondLine.size())
    {
        std::string temp = firstLine;
        firstLine = secondLine;
        secondLine = temp;
    }

    int firstLength = firstLine.size(), secondLength = secondLine.size();

    //    a   s   a   s           0   1   2   3
    //s | 0 | 1 | 0 | 1 |     0 | 0 | 2 | 0 | 3 |
    //a | 1 | 0 | 2 | 0 | ==> 1 | 1 | 0 | 3 | 0 |
    //s | 0 | 2 | 0 | 3 |     2 % 2 = 0   
    //a | 1 | 0 | 3 | 0 |     3 & 2 = 1
    int** diagonalSubstringMapV4 = new int* [2];
    diagonalSubstringMapV4[0] = new int[secondLength]();
    diagonalSubstringMapV4[1] = new int[secondLength]();

    int longestCommonSubstring = 0;
    bool rowSwitch = 0;
    for (int i = 0; i < firstLength; ++i)
    {
        for (int j = 0; j < secondLength; ++j)
        {
            if (firstLine[i] == secondLine[j])
            {
                int leftDiag = (i > 0 && j > 0) ? diagonalSubstringMapV4[!rowSwitch][j - 1] : 0;
                diagonalSubstringMapV4[rowSwitch][j] = leftDiag + 1;

                longestCommonSubstring = std::max(longestCommonSubstring, leftDiag + 1);
            }
            else
            {
                diagonalSubstringMapV4[rowSwitch][j] = 0;
            }
        }
        rowSwitch = !rowSwitch;
    }

    std::cout << longestCommonSubstring;

    //delete[] diagonalSubstringMapV4[0];
    //delete[] diagonalSubstringMapV4[1];
    //delete[] diagonalSubstringMapV4;

    return 0;
}