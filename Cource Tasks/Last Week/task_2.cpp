#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>

int wordCount[26];
int main() {
    int test=0;
    std::cin>>test;
    int size=0;
    char ch;
    int sum=0;
    std::string temp="";
    for(int i=0;i<test;i++)
    {
        for(int j=0;j<26;j++)
        {
            wordCount[j]=0;
        }
        sum=0;
        std::cin>>temp;
        size=temp.size();
        for(int j=0;j<size;j++)
        {
            wordCount[(int)(temp[j])-65]++;
        }
        for(int j=0;j<size;j++)
        {
            std::cin>>ch;
            wordCount[(int)(ch)-65]--;
        }
        for(int j=0;j<26;j++)
        {
           while(wordCount[j]<0)
           {
              
               for(int k=1;k<26;k++)
               {
                   if(j-k>=0&&wordCount[j-k]>=1)
                   {
                     sum+=k;
                       wordCount[j-k]-=1;
                       wordCount[j]++;
                       break;
                   }
                   else if(wordCount[26+j-k]>=1)
                   {
                       sum+=k;
                       wordCount[26+j-k]-=1;
                       wordCount[j]++;
                       break;
                   }
               }
          } 
        }
        std::cout<<sum<<std::endl;
    }
    return 0;
}
