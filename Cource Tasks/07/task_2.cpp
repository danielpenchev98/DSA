#include <iostream>
#include <stdio.h>
#include <iomanip>
double maxHeap[1000000];
double minHeap[1000000];
int sizeMaxHeap;
int sizeMinHeap;
inline void InsertMaxHeap(double num,int loc)
{
    int par = 0;
    int locat = loc;
    while (locat > 0)
    {
        par = (locat - 1) / 2;
        if (maxHeap[par] >= num)
        {
            maxHeap[locat] = num;
            sizeMaxHeap++;
            return ;
        }
        maxHeap[locat] = maxHeap[par];
        locat = par;
    }
    maxHeap[0] = num;
    sizeMaxHeap++;
}
inline void InsertMinHeap(double num,int loc)
{
    int par = 0;
    int locat = loc;
    while (locat > 0)
    {
        par = (locat - 1) / 2;
        if (minHeap[par] <= num)
        {
            minHeap[locat] = num;
            sizeMinHeap++;
            return ;
        }
        minHeap[locat] = minHeap[par];
        locat = par;
    }
    minHeap[0] = num;
    sizeMinHeap++;
}
inline double DeleteMaxRoot()
{
    int left = 0, right = 0, i = 0;
    double temp = maxHeap[i];
    maxHeap[i] = maxHeap[sizeMaxHeap-1];
    maxHeap[sizeMaxHeap-1] = temp;
    left = 2 * i + 1;
    right = 2 * i + 2;
    while(right < sizeMaxHeap-1 )
    {
        if (maxHeap[i] >= maxHeap[left] && maxHeap[i] >= maxHeap[right])
        {
            sizeMaxHeap--;
            return maxHeap[sizeMaxHeap];
        }
        if (maxHeap[left] >= maxHeap[right])
        {
            temp = maxHeap[i];
        maxHeap[i] = maxHeap[left];
            maxHeap[left] = temp;
            i = left;
        }
        else
        {
            temp = maxHeap[i];
            maxHeap[i] = maxHeap[right];
            maxHeap[right] = temp;
            i = right;
        }
        left = 2 * i + 1;
        right = 2 * i + 2;
    }
    if (left+1==sizeMaxHeap-1  && maxHeap[i] < maxHeap[left])
    {
        temp = maxHeap[i];
        maxHeap[i] = maxHeap[left];
        maxHeap[left] = temp;
    }
    sizeMaxHeap--;
    return maxHeap[sizeMaxHeap];
}
inline double DeleteMinRoot()
{
    int left = 0, right = 0, i = 0;
    double temp = minHeap[i];
     minHeap[i] =  minHeap[sizeMinHeap-1];
     minHeap[sizeMinHeap-1] = temp;
    left = 2 * i + 1;
    right = 2 * i + 2;
    while(right < sizeMinHeap-1 )
    {
        if ( minHeap[i] <=  minHeap[left] &&  minHeap[i] <=  minHeap[right])
        {
            sizeMinHeap--;
            return minHeap[sizeMinHeap];
        }
        if (minHeap[left] <= minHeap[right])
        {
            temp = minHeap[i];
        minHeap[i] = minHeap[left];
            minHeap[left] = temp;
            i = left;
        }
        else
        {
            temp = minHeap[i];
            minHeap[i] = minHeap[right];
            minHeap[right] = temp;
            i = right;
        }
        left = 2 * i + 1;
        right = 2 * i + 2;
    }
    if (left+1==sizeMinHeap-1  && minHeap[i] > minHeap[left])
    {
        temp = minHeap[i];
        minHeap[i] = minHeap[left];
        minHeap[left] = temp;
    }
    sizeMinHeap--;
    return minHeap[sizeMinHeap];
}
inline void Add(double num)
{
    if(sizeMaxHeap==0||num<maxHeap[0])
    {
        InsertMaxHeap(num,sizeMaxHeap);
    }
    else
    {
        InsertMinHeap(num,sizeMinHeap);
    }
}
inline void Balancer()
{
    if(sizeMaxHeap-sizeMinHeap>=2)
    {
        InsertMinHeap(DeleteMaxRoot(),sizeMinHeap);
    }
    else if(sizeMinHeap-sizeMaxHeap>=2)
    {
         InsertMaxHeap(DeleteMinRoot(),sizeMaxHeap);
    }
}
inline double GetMedian()
{
    if(sizeMinHeap==sizeMaxHeap)
    {
        return (minHeap[0]+maxHeap[0])/2;
    }
    return sizeMinHeap>sizeMaxHeap?minHeap[0]:maxHeap[0];
}
int main() {
    int size=0;
    std::ios_base::sync_with_stdio(false);
    std::cin>>size;
    double sum=0;
    double curr=0;
    for(int i=0;i<size;i++)
    {
        std::cin>>curr;
      //scanf("%lf",&curr);
      Add(curr);
      Balancer();
      printf("%.1f\n",GetMedian() );
    }

    return 0;
}
