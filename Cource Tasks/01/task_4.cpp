#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <algorithm>
struct PairSocks
{
    PairSocks() {}
    PairSocks(const int f, const int s) :a(f), b(s),diff(s-f){}
    int a;
    int b;
    int diff;
};
void InsertionSort(std::vector<PairSocks>& arr, const int low, const int high)
{
    PairSocks k;
    int i = 0;
    int j = 0;
    for (int i = low+1; i <=high; i++)
    {
        k = arr[i];
        for (j = i - 1; j >= low && k.a < arr[j].a; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = k;
    }
}
struct Pair
{
    Pair(const int f, const int l) :lb(f), ub(l) {}
    int lb;
    int ub;
};
Pair PartitionWithCopies(std::vector<PairSocks>& arr, const int low, const int high)
{
    PairSocks y;
    int i = low;
    int h = low;
    PairSocks x = arr[low];
    for (int j = i + 1; j <= high; j++)
    {
        if (arr[j].diff < x.diff)
        {
            y = arr[j];
            arr[j] = arr[h + 1];
            arr[h + 1] = arr[i];
            arr[i] = y;
            i++;
            h++;
        }
        else if (arr[j].diff == x.diff)
        {
            std::swap(arr[h + 1], arr[j]);
            h++;
        }
    }
    InsertionSort(arr, i, h);
    return Pair(i, h);
}
//RandimPartition Optimization through Median-of-3 
Pair  RandomPartitionWithCopies(std::vector<PairSocks>& arr, const int low, const int high)
{
    srand(static_cast<unsigned int>(time(0)));
    int num1 = rand() % (high - low + 1) + low;
    int num2 = rand() % (high - low + 1) + low;
    int num3 = rand() % (high - low + 1) + low;
    int median = std::max(std::min(num1, num2), std::min(std::max(num1, num2), num3));
    std::swap(arr[median], arr[low]);
    return PartitionWithCopies(arr, low, high);
}

//better version if there are multiple copies of an element
void QuickSortWithCopies(std::vector<PairSocks>& arr, int low, int high)
{
    while (low < high)
    {
        Pair temp = RandomPartitionWithCopies(arr, low, high);
        if (temp.lb - low < high - temp.ub)
        {
            QuickSortWithCopies(arr, low, temp.lb - 1);
            low = temp.ub + 1;
        }
        else
        {
            QuickSortWithCopies(arr, temp.ub + 1, high);
            high = temp.lb - 1;
        }
    }
}
int main()
{
    int num = 0;
    std::cin >> num;
    int day = 0;
    std::cin >> day;
    int* numbers = new int[num];
    for (int i = 0; i <num; i++)
    {
        std::cin >> numbers[i];
    }
    std::vector<PairSocks> pairs;
    for (int i = 0; i < num; i++)
    {
        for (int j = i+1; j < num; j++)
        {
            pairs.push_back(PairSocks(numbers[i], numbers[j]));
        }
    }
    QuickSortWithCopies(pairs,0,pairs.size()-1);
    std::cout << pairs[day - 1].a << " " << pairs[day - 1].b << std::endl;
    return 0;
}
