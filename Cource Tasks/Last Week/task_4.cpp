#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

struct ThreeSome
{
    ThreeSome(){}
    ThreeSome(int fr,int t,int w):from(fr),to(t),weight(w){}
    int from;
    int to;
    int weight;
    bool operator<(ThreeSome& b)
    {
       return weight>b.weight;
    }
};

ThreeSome Edges[100000];
bool reached[100000];
int rch[100000];
int index=0;
void clear(const int size)
{
    while(index)
    {
        reached[rch[--index]-1]=0;
    }
    
}
void add(const int v)
{
    reached[v-1]=1;
    rch[index++]=v;
}
 std::vector<int> graph[100000];
bool DFS(const int v, const int end)
{
   for(int vertex : graph[v-1])
   {
      if(reached[vertex-1])continue;
       add(vertex);
       if(vertex==end) return true;
       if(DFS(vertex,end)) return true;
   }
    return false;
}
int main() {
    std::ios::sync_with_stdio(false);
    int nodes;
    int edges;
    std::cin>>nodes>>edges;
    int first=0;
    int second=0;
    int weight=0;
    for(int i=0;i<edges;i++)
    {
        std::cin>>first>>second>>weight;
        Edges[i].from=first;
        Edges[i].to=second;
        Edges[i].weight=weight;
    }
    std::sort(Edges,Edges+edges);
     std::queue<int> Q;
    int counter=0;
    int temp=0;
for(int j=0;j<edges;j++)
{
    first=Edges[j].from;
    second=Edges[j].to;
    weight=Edges[j].weight;
    graph[first-1].push_back(second);
    
    bool cycle=DFS(first,first);
    clear(nodes);
    if(cycle)
    {
        std::cout<<weight<<std::endl;
        return 0;
    }
}
    std::cout<<0<<std::endl;
    return 0;
}
