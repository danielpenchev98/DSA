#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
bool CountingChar(const std::string& arr)
{
    int* temp = new int[26];
    for (int i = 0; i < 26; i++)
    {
        temp[i] = 0;
    }
    for (int i = 0; i < arr.size(); i++)
    {
        temp[arr[i] - 'a']++;
    }
    int largestCount = temp[0];
    for (int i = 1; i < 26; i++)
    {
        if (largestCount < temp[i])
        {
            largestCount =temp[i];
        }
    }
    if (largestCount > arr.size()-largestCount + 1)
    {
        return 0;
    }
    return 1;
}
int main()
{
    std::string input = "";
    std::getline(std::cin, input);
    std::cout << (CountingChar(input) == 1 ? "Yes" : "No");
    return 0;
}
