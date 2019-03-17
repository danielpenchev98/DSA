#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Pair
{
    int height;
    int cost;
};
int FindCost(const Pair* const arr,const int size,const int pos,const int maxhigh)
{
    if (pos<0 || pos>maxhigh)
    {
        return 1900000000;
    }
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int temp = abs(arr[i].height - pos);
        if ( temp!= 0)
        {
            sum += arr[i].cost*temp;
        }
    }
    return sum;
}
int TernarySearch(const Pair* const arr, const int size, const int low, const int high,const int maxhigh)
{
    if (low <= high)
    {
        int mid1 = (2 * low + high) / 3;
        int mid2 =(int)std::ceil(((double)((low + 2 * high)) / 3));
        int costMid1 = FindCost(arr, size, mid1,maxhigh);
        int costMid2 = FindCost(arr, size, mid2,maxhigh);
        if (costMid1 <= costMid2)
        {
            int lessThanMid1 = FindCost(arr, size, mid1-1,maxhigh);
            int greaterThanMid1 = FindCost(arr, size,mid1+1,maxhigh);
            if (lessThanMid1 >= costMid1 && greaterThanMid1 >= costMid1)
            {
               
                return costMid1;
            }
            else if(lessThanMid1 < costMid1 && greaterThanMid1 > costMid1)
            {
                return TernarySearch(arr, size, 0, mid1-1,maxhigh);
            }
            else
            {
                return TernarySearch(arr, size, mid1+1,mid2-1,maxhigh);
            }
            
            
        }
        else
        {
            int lessThanMid2 = FindCost(arr, size, mid2-1,maxhigh);
            int greaterThanMid2 = FindCost(arr, size, mid2+1,maxhigh);
            if (lessThanMid2 >= costMid2 && greaterThanMid2 >= costMid2)
            {
                return costMid2;
            }
            else if (lessThanMid2 < costMid2 && greaterThanMid2 > costMid2)
            {
                return TernarySearch(arr, size, mid1+1, mid2-1,maxhigh);
            }
            else
            {
                return TernarySearch(arr, size, mid2+1, high,maxhigh);
            }
        }
    }
    else
    {
        return 1900000000;
    }
}
int main()
{
    int size = 0;
    std::cin >> size;
    Pair* arr = new Pair[size];
    int largest = -1900000000;
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i].height;
        if (largest < arr[i].height)
        {
            largest = arr[i].height;
        }
    }
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i].cost;
    }
    std::cout << TernarySearch(arr, size, 0, largest,largest);
    delete[] arr;
    return 0;
}
