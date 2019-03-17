#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

struct Pair
{
    Pair(int t,int m):to(t),moves(m){}
    int to;
    int moves;
};
bool checkedAngel[100000];
bool checkedDevil[100000];
int finalStop[100000];
int main() {
    for(int i=0;i<100000;i++)
    {
        finalStop[i]=-1;
    }
    int size=0;
    std::cin>>size;
    std::vector<std::vector<int>> vec(size);
    int ivan=0;
    std::cin>>ivan;
    int first=0;
    int second=0;
    for(int i=0;i<size-1;i++)
    {
        std::cin>>first>>second;
        vec[first-1].push_back(second);
        vec[second-1].push_back(first);
    }
    std::queue<Pair> devil;
    std::queue<Pair> angel;
    int curr1=1;
    int curr2=ivan;
    int toPopDevils=0;
    int toPopAngels=0;
    devil.push(Pair(1,0));
    angel.push(Pair(ivan,0));
    while(!devil.empty()||!angel.empty())
    {
            
        while(!angel.empty()&&angel.front().moves==toPopAngels)
        {
             if(!checkedAngel[angel.front().to-1]&&!checkedDevil[angel.front().to-1])
             {
                checkedAngel[angel.front().to-1]=1;
                for(int i=0;i<vec[angel.front().to-1].size();i++)
                {
                    if(!checkedAngel[vec[angel.front().to-1][i]-1]&&!checkedDevil[vec[angel.front().to-1][i]-1])
                    {
                           angel.push(Pair(vec[angel.front().to-1][i],toPopAngels+1));
                    } 
                }
             
              }
              angel.pop();
        }
        toPopAngels++;
        
        while(!devil.empty()&&devil.front().moves==toPopDevils)
        {
           if(!checkedDevil[devil.front().to-1])
           {
              
               curr2=devil.front().to;
               if(vec[curr2-1].size()==1&&checkedAngel[vec[curr2-1][0]-1])
               {
                   finalStop[vec[curr2-1][0]-1]=devil.front().moves;
               }
               checkedDevil[curr2-1]=1;
                  for(int i=0;i<vec[curr2-1].size();i++)
                  {
                        if(!checkedDevil[vec[curr2-1][i]-1])
                        {
                          devil.push(Pair(vec[curr2-1][i],devil.front().moves+1));
                        }
                   }
         
            }
            devil.pop();
        }
        toPopDevils++;
    }
    int max=0;
    for(int i=0;i<size;i++)
    {
      if(finalStop[i]>max)
      {
          max=finalStop[i];
      }
    }
    std::cout<<2*max<<std::endl;
    
    return 0;
}
