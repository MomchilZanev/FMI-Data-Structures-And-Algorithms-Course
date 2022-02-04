#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    
    string studentsRow;    
    char variant;
    vector<int> distances;    
    cin >> studentsRow >> variant;
    
    for(int i = 0; i < studentsRow.length(); i++)
    {
        if(studentsRow[i] == variant)
        {
            distances.push_back(0);
            continue;
        }
        
        int leftDistance = 0;
        int rightDistance = 0;
        
        bool reaches = false;
        for(int j = i - 1; j >= 0; j--)
        {
            leftDistance++;
            if(studentsRow[j] == variant)
            {
                reaches = true;
                break;
            }
        }
        if(!reaches)
        {
            leftDistance = INT_MAX;
        }
        
        reaches = false;        
        for(int j = i + 1; j < studentsRow.length(); j++)
        {
            rightDistance++;
            if(studentsRow[j] == variant)
            {
                reaches = true;
                break;
            }
        }
        if(!reaches)
        {
            rightDistance = INT_MAX;
        }
        
        distances.push_back(min(leftDistance, rightDistance));
    }
    
    for (int i = 0; i < distances.size(); i++) {
        cout << distances[i] << ' ';
    }
    cout << endl;
    return 0;
}