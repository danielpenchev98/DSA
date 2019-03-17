#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <time.h>
int HoaresPartition(int* const arr, const int n, const int low, const int high)
{
    int x = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < x);
        do
        {
            j--;
        } while (arr[j] > x);
        if (i >= j)
        {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}
int RandomPartition(int* const arr, const int n, const int low, const int high)
{
    srand(static_cast<unsigned int>(time(0)));
    int i = rand() % (high - low + 1) + low;
    std::swap(arr[i], arr[high]);
    return HoaresPartition(arr, n, low, high);
}
void QuickSort(int* const arr, const int n, const int low, const int high)
{
    if (low < high)
    {
        int piv = RandomPartition(arr, n, low, high);
        QuickSort(arr, n, low, piv);
        QuickSort(arr, n, piv + 1, high);
    }
}
int MaxCountToys(int* const toys, const int size, const int money)
{
    QuickSort(toys, size, 0, size - 1);
    int maxCounter = 0;
    int sum = 0;
    int counter = 0;
    for (int i = 0; i < size; i++)
    { 
        if (toys[i] > money)
        {
            continue;
        }
        counter = 1;
        sum = toys[i];
        for (int j = i + 1; j < size; j++)
        {
            counter++;
            sum += toys[j];
            if (sum > money)
            {
                counter--;
                break;
            }
        }
        if (maxCounter < counter)
        {
            maxCounter = counter;
        }
    }
    return maxCounter;
}
int main()
{
    int numToys = 0;
    std::cin >> numToys;
    int money = 0;
    std::cin >> money;
    int* arr = new int[numToys];
    for (int i = 0; i < numToys; i++)
    {
        std::cin >> arr[i];
    }
    std::cout << MaxCountToys(arr, numToys, money) << std::endl;
    return 0;
}
