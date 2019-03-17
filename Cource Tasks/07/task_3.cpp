#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct TreeNode
{
    TreeNode* parent;
    double data;
};
struct Pair
{
    int node1;
    int node2;
};
bool Compare(Pair& comp1,Pair comp2)
{
    if(comp1.node1<comp2.node1) return 1;
    return 0;
}
int bucks[100000];
int maxPath[100000];
TreeNode* leaves[100000];
TreeNode arr[100000];
int main() {
    int size=0;
    std::cin>>size;
    int maxBucks=0;
    std::cin>>maxBucks;
    for(int i=0;i<size;i++)
    {
        std::cin>>bucks[i];
    }
    if(size==0)
    {
        return 0;
    }
    Pair* pairs=new Pair[size-1];
    int vertex1=0;
    int vertex2=0;
    for(int i=0;i<size-1;i++)
    {
        std::cin>>pairs[i].node1;
        std::cin>>pairs[i].node2;
        if(pairs[i].node1>pairs[i].node2)
        {
            int temp=pairs[i].node1;
            pairs[i].node1=pairs[i].node2;
            pairs[i].node2=temp;
            
        }
    }
   std::sort(pairs,pairs+size-1,Compare);
    arr[0].parent=nullptr;
    arr[0].data=1;
    leaves[0]=&arr[0];
    for(int i=0;i<100000;i++)
    {
        maxPath[i]=bucks[0];
    }
    for(int i=1;i<size;i++)
    {
     
      vertex1=pairs[i-1].node1;
        vertex2=pairs[i-1].node2;
        if(arr[vertex1-1].data==0)
        {
            leaves[vertex1-1]=&arr[vertex1-1];
            leaves[vertex2-1]=nullptr;
            arr[vertex1-1].parent=&arr[vertex2-1];
            arr[vertex1-1].data=vertex1;
            if(bucks[vertex1-1]!=0)
            {
               bucks[vertex1-1]+=bucks[vertex2-1];
                 if(maxPath[vertex2-1]<bucks[vertex1-1]){
                maxPath[vertex1-1]=bucks[vertex1-1];}
                else
                {
                    maxPath[vertex1-1]=maxPath[vertex2-1];
                }
               
            }
            else
            {
             
             
                    maxPath[vertex1-1]=maxPath[vertex2-1];
             
            }
        }
        else
        {
            leaves[vertex2-1]=&arr[vertex2-1];
            leaves[vertex1-1]=nullptr;
            arr[vertex2-1].parent=&arr[vertex1-1];
            arr[vertex2-1].data=vertex2;
            if(bucks[vertex2-1]!=0)
            {
            bucks[vertex2-1]+=bucks[vertex1-1];
                if(maxPath[vertex1-1]<bucks[vertex2-1])
                {
                  maxPath[vertex2-1]=bucks[vertex2-1];
                  
                }
                else
                {
                    maxPath[vertex2-1]=maxPath[vertex1-1];
                }
               
            }
             else
            {
             
                 maxPath[vertex2-1]=maxPath[vertex1-1];
                   
             }
        }
    }
  
    int counter=0;
    for(int i=0;i<100000;i++)
    {
        if(leaves[i]!=nullptr&&maxPath[i]<=maxBucks)
        {
        
            counter++;
        }
            
    }
    std::cout<<counter;
    return 0;
}
