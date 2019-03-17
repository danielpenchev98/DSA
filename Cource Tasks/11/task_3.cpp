#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
struct Pair
{
    Pair(int t, long long w,bool ty) :to(t), weight(w),type(ty) {}
    int to;
    long long weight;
    bool type;
};
class Compare
{
public:
    bool operator()(Pair& a, Pair& b)
    {
        if (a.weight > b.weight) return true;
        return false;
    }
};
std::vector<std::vector<Pair>> vec;
bool checked[200001];
long long path[2][200001];
int main() {
    std::ios_base::sync_with_stdio(false);
    int vertex = 0;
    int edges = 0;
    int start = 0;
    int first = 0;
    int second = 0;
    long long weight = 0;
    std::cin >> vertex;
    std::cin >> edges;
    int trainTracks=0;
    std::cin>>trainTracks;
    vec.resize(vertex);
    for (int j = 0; j < edges; j++)
    {
       std::cin >> first;
       std::cin >> second;
       std::cin >> weight;
       vec[first - 1].push_back(Pair(second, weight,0));
       vec[second - 1].push_back(Pair(first, weight,0));
     }
    for(int j=0;j<trainTracks;j++)
    {
       std::cin >> second;
       std::cin >> weight;
       vec[0].push_back(Pair(second, weight,1));
       vec[second - 1].push_back(Pair(1, weight,1));
    }
     for (int j = 0; j < vertex; j++)
     {
      path[0][j] = 922337203685477580;
      checked[j] = 0;
     }
        path[0][0] = 0;
        std::priority_queue<Pair, std::vector<Pair>, Compare> que;
        que.push(Pair(1, 0,0));
        int curr = 0;
        while (!que.empty())
        {
            curr = que.top().to;
            que.pop();
            if(checked[curr-1]!=0)
            {
                continue;
            }
            checked[curr - 1] = 1;
            for (int k = 0; k < vec[curr - 1].size(); k++)
            {
                if (path[0][vec[curr - 1][k].to - 1] > path[0][curr - 1] + vec[curr - 1][k].weight||(path[0][vec[curr - 1][k].to - 1] == path[0][curr - 1] + vec[curr - 1][k].weight&&path[1][vec[curr - 1][k].to - 1]))
                {
                    path[0][vec[curr - 1][k].to - 1] = path[0][curr - 1] + vec[curr - 1][k].weight;
                    path[1][vec[curr - 1][k].to - 1]=vec[curr-1][k].type;
                    que.push(Pair(vec[curr - 1][k].to, path[0][vec[curr - 1][k].to - 1],vec[curr-1][k].type));
                }
            }
        }
    int counter=0;
     for(int i=0;i<vertex;i++)
     {
         if(path[1][i]==1)
         {
             counter++;
         }
     }
     
      std::cout<<trainTracks-counter;
    return 0;
}
