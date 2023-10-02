#include<vector>
#include <climits>
#include<iostream>

template <typename T>
std::vector<T> slice(const std::vector<T>& arr, int start, int end = INT_MAX) {
    int len = static_cast<int>(arr.size());
    int from = (start >= 0) ? start : std::max(len + start, 0);
    int to = (end >= 0) ? end : std::max(len + end, 0);

    std::cout<<"from "<<from<<" to "<<to<<std::endl;

    if (from >= len || from >= to) {
        return std::vector<T>();
    }

    to = std::min(to, len);
    
    return std::vector<T>(arr.begin() + from, arr.begin() + to);
}