#include <vector>
#include <climits>
#include <iostream>

template <typename T>
std::vector<T> slice(const std::vector<T> &arr, int start, int end = INT_MAX)
{
    int len = static_cast<int>(arr.size());
    int from = (start >= 0) ? start : std::max(len + start, 0);
    int to = (end >= 0) ? end : std::max(len + end, 0);

    if (from >= len || from >= to)
    {
        return std::vector<T>();
    }

    to = std::min(to, len);

    return std::vector<T>(arr.begin() + from, arr.begin() + to);
}

template <typename T>
std::vector<T> splice(std::vector<T> &arr, int start, int deleteCount, const std::vector<T> &items)
{
    // Check for out-of-bounds start index
    if (start > arr.size())
    {
        start = arr.size();
    }

    // Calculate the end index
    size_t end = start + deleteCount;
    if (end > arr.size())
    {
        end = arr.size();
    }

    // Create a new vector to store the spliced elements
    std::vector<T> spliced;

    // Move elements before the start index to the spliced vector
    spliced.insert(spliced.end(), arr.begin() + start, arr.begin() + end);

    arr.insert(arr.begin() + end, items.begin(), items.end());
    arr.erase(arr.begin() + start, arr.begin() + end);

    return spliced;
}
