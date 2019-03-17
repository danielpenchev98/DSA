#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
bool CheckIfDry(const long long* const arr, const int size, const int time, const long long power)
{
    long long countTimes = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] - time > 0)
        {
            countTimes += (arr[i] - time) / (power-1);
            if ((arr[i] - time)% (power-1) != 0)
            {
                countTimes++;
            }
        }
    }
    if (countTimes <= time)
    {
        return 1;
    }
    return 0;
}
int main()
{
    int size = 0;
    std::cin >> size;
    long long hairdryer = 0;
    std::cin >> hairdryer;
    long long* arr = new long long[size];
    long long largest = -2147483647;
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
        if (largest < arr[i])
        {
            largest = arr[i];
        }
    }
    int index = 0;
    int mid = 0;
    int left = 0;
    int right = largest + 1;
    if(hairdryer==1)
    {
        std::cout<<largest<<std::endl;
        return 0;
    }
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (CheckIfDry(arr, size, mid, hairdryer))
        {
            right = mid - 1;
            index = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    delete[] arr;
    std::cout << index << std::endl;
    return 0;
}
