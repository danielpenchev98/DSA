#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
long long Merge(int* const arr, const int n, const int low, const int mid, const int high)
{
    long long counter = 0;
    int* temp = new int[n];
    int i = low;
    int j = mid + 1;
    int k = low;
    while (i <= mid && j <= high)
    {
        if (arr[i] > arr[j])
        {
            counter += mid - i + 1;
            temp[k++] = arr[j++];
        }
        else
        {
            temp[k++] = arr[i++];
            
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= high)
    {
        temp[k++] = arr[j++];
    }
    for (i = low; i <= high; i++)
    {
        arr[i] = temp[i];
    }
    delete[] temp;
    return counter;
}
long long MergeSort(int* const arr,const int n, const int low, const int high)
{
    long long counter = 0;
    int mid = 0;
    if (low < high)
    {
        mid = (high + low) / 2;
        counter += MergeSort(arr,n, low, mid);
        counter += MergeSort(arr,n, mid + 1, high);
        counter += Merge(arr,n, low, mid, high);
    }
    return counter;
}
int main()
{
    int count = 0;
    std::cin >> count;
    int size = 0;
    for (int i = 0; i < count; i++)
    {
        std::cin >> size;
        int* arr = new int[size];
        for (int i = 0; i <size; i++)
        {
            std::cin >> arr[i];
        }
        std::cout << MergeSort(arr, size, 0, size - 1) << std::endl;
        delete[] arr;
    }
    return 0;
}
