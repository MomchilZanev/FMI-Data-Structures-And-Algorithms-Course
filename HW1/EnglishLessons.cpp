#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    
    string word;    
    int N;
    char S;  
    cin >> word >> N >> S;
    
    int wordLength = word.length();    
    int symbolOccurrencesInWord = 0;    
    for(int i = 0; i < wordLength; i++)
    {
        if(S == word[i])
        {
            symbolOccurrencesInWord++;
        }
    }
    
    int totalOccurrences = (N / wordLength) * symbolOccurrencesInWord;
    int remainderSymbols = N % wordLength;    
    for(int i = 0; i < remainderSymbols; i++)
    {
        if(S == word[i])
        {
            totalOccurrences++;
        }
    }
    
    cout << totalOccurrences;
    
    return 0;
}