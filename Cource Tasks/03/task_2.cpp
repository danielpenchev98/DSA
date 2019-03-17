#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
int HoaresPartition(long long* const arr, const int low, const int high)
{
    int i = low - 1;
    int j = high + 1;
    long long x = arr[low];
    while (true)
    {
        do
        {
            i++;
        } while (arr[i]<x);
        do
        {
            j--;
        } while (arr[j]>x);
        if (i >= j)
        {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}
int RandomizedPartition(long long* const arr, const int low, const int high)
{
    srand(static_cast<unsigned int>(time(0)));
    int num1 = rand() % (high - low + 1) + low;
    int num2 = rand() % (high - low + 1) + low;
    int num3 = rand() % (high - low + 1) + low;
    int median = std::max(std::min(num1, num2), std::min(std::max(num1, num2), num3));
    std::swap(arr[median], arr[low]);
    return HoaresPartition(arr, low, high);

}
void QuickSort(long long* const arr, const int low, const int high)
{
    if (low < high)
    {
        int pivot = RandomizedPartition(arr, low, high);
        QuickSort(arr, low, pivot);
        QuickSort(arr, pivot+1,high);
    }
}
int BinaySearchOccurence(const long long* const arr, const int size, const long long num, const int choice)
{
    int left = 0;
    int right = size - 1;
    int mid = 0;
    int index = -1;
    while (left <= right)
    {
        mid = (right + left) / 2;
        if (arr[mid] == num)
        {
            index = mid + 1;
            if (choice == 0)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else if (arr[mid] > num)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return index;
}
int main()
{
    int size = 0;
    std::cin >> size;
    long long* arr = new long long[size];
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
    QuickSort(arr, 0, size - 1);
    int loops = 0;
    long long num = 0;
    std::cin >> loops;
    for (int i = 0; i < loops; i++)
    {
        std::cin >> num;
        std::cout << BinaySearchOccurence(arr, size, num, 0) << " " << BinaySearchOccurence(arr, size, num, 1) << std::endl;
    }
    return 0;
}
