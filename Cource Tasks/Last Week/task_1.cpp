#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

int positive[80];
int negative[80];
int B[2224];
long long GetMaxPositiveSumMult(const int size)
{
    long long sum=0;
    int* C=new int[size];
    int ones=0;
    int zeros=0;
    for(int i=0;i<2224;i++)
    {
        B[i]=0;
    }
    for(int i=0;i<size;i++)
    {
        B[positive[i]]++;
    }
    ones=B[1];
    zeros=B[0];
    for(int i=0;i<2223;i++)
    {
        B[i+1]+=B[i];
    }
    for(int i=0;i<size;i++)
    {
        C[B[positive[i]]-1]=positive[i];
        B[positive[i]]--;
    }
    for(int i=size-1;i>=0;i-=2)
    {
        if(C[i]<=1)
        {
            break;
        }
        else if(i-1<0||C[i-1]<=1)
        {
            sum+=C[i];
            break;
        }
        else if(i-1>=0)
        {
        sum+=C[i]*C[i-1];
        }
    }
    sum+=ones;
    return sum;
}
long long GetMaxNegativeSumMult(const int size)
{
    long long sum=0;
    int* C=new int[size];
    int ones=0;
    int zeros=0;
    for(int i=0;i<2223;i++)
    {
        B[i]=0;
    }
    for(int i=0;i<size;i++)
    {
        B[negative[i]]++;
    }
    ones=B[1];
    zeros=B[0];
    for(int i=0;i<2222;i++)
    {
        B[i+1]+=B[i];
    }
    for(int i=0;i<size;i++)
    {
        C[B[negative[i]]-1]=negative[i];
        B[negative[i]]--;
    }
    int iter=size-1;
    for(iter=size-1;iter>=1;iter-=2)
    {
       
        sum+=C[iter]*C[iter-1];
    }
    if(iter==0)
    {
       sum-=C[0];
    }
    return sum;
}
int main() {
    int test=0;
    std::cin>>test;
    int size=0;
    int num=0;
    long long resultPositive=0;
    long long resultNegative=0;
    int sizePositive=0;
    int sizeNegative=0;
    for(int i=0;i<test;i++)
    {
        std::cin>>size;
        sizePositive=0;
        sizeNegative=0;
        for(int j=0;j<80;j++)
        {
            positive[j]=0;
            negative[j]=0;
        }
        for(int j=0;j<size;j++)
        {
           std::cin>>num;
            if(num>0)
            {
                positive[sizePositive]=num;
                sizePositive++;
            }
            else
            {
                negative[sizeNegative]=-num;
                sizeNegative++;
            }
        }
       resultPositive=GetMaxPositiveSumMult(sizePositive);
       resultNegative=GetMaxNegativeSumMult(sizeNegative);
       std::cout<<resultNegative+resultPositive<<std::endl;
    }  
    return 0;
}
