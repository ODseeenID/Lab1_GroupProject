#pragma once
#include <string>
#include <vector>

struct InputData {
    std::string text;
    std::string pattern;
};

struct Result {
    std::vector<int> positions; 
    int count;          
    long long comparisons;  
    double time_ms;   
};