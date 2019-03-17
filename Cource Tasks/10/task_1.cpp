include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Triple
{
    Triple(int f,int t,long long w):from(f),to(t),weight(w){}
  int from;
  int to;
  long long weight;
};
long long path[1000];
int main() {
    
    int vertex;
    std::cin>>vertex;
    int edges;
    std::cin>>edges;
    int start;
    std::cin>>start;
    int end;
    std::cin>>end;
    std::vector<Triple> vec;
    int from=0;
    int to=0;
    long long weight=0;
    for(int i=0;i<edges;i++)
    {
        std::cin>>from>>to>>weight;
        vec.push_back(Triple(from,to,weight));
    }
    for(int i=0;i<vertex;i++)
    {
        path[i]=-922337203685477580;
    }
    path[start-1]=0;
    for(int i=0;i<vertex-1;i++)
    {
        for(int j=0;j<vec.size();j++)
        {
            if(path[vec[j].to-1]<path[vec[j].from-1]+vec[j].weight)
            {
                path[vec[j].to-1]=path[vec[j].from-1]+vec[j].weight;
            }
        }
    }
    if(path[end-1]!=-922337203685477580)
    std::cout<<path[end-1];
    else
        std::cout<<-1;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
