#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    vector<int> outfitNumbers;
    
    cin >> N;
    int number;
    while(cin >> number)
    {
        if(number > 0)
        {
            outfitNumbers.push_back(number);
        }        
    }    
    
    vector<bool> usedNumbers(N);
    usedNumbers[0] = true;
    
    for (int i = 0; i < outfitNumbers.size(); i++)
    {
        if(outfitNumbers[i] >= 0 && outfitNumbers[i] < N)
        {
            usedNumbers[outfitNumbers[i]] = true;
        }
    }
    
    int unusedNumber = N + 1;
    for (int i = 0; i < N; i++)
    {
        if(!usedNumbers[i])
        {
            unusedNumber = i;
            break;
        }
    }
    
    cout << unusedNumber;
    
    return 0;
}