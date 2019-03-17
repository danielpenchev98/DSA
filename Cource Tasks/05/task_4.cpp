#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
int main() {
    
    long long size=0;
    std::cin>>size;
   std::queue<long long> container;
    for(int i=1;i<10;i++)
    {
        container.push(i);
    }
    long long curr=0;
    long long curr2=0;
    while(container.front()<=size)
    {
        curr=container.front();
        curr2=curr;
        std::cout<<curr<<" ";
        container.pop();
        if(curr%10-2>=0)
        {
            curr=curr*10+curr%10-2;
           
            container.push(curr);
        }
        if(curr2%10+2<=9)
        {
              curr2=curr2*10+curr2%10+2;
     
            container.push(curr2);
        }
        
    }
 
    return 0;
}
