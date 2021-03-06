#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
struct Pair
{
    Pair(int t, int w) :to(t), weight(w) {}
    int to;
    long long weight;
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
std::vector<std::vector<Pair>> vec[10];
bool checked[200001];
long long path[200001];
int main() {
    std::ios_base::sync_with_stdio(false);
    int tests = 0;
    std::cin >> tests;
    int vertex = 0;
    int edges = 0;
    int start = 0;
    int first = 0;
        int second = 0;
        long long weight = 0;
    for (int i = 0; i < tests; i++)
    {
        std::cin >> vertex;
        std::cin >> edges;
        vec[i].resize(vertex);
        for (int j = 0; j < edges; j++)
        {
            std::cin >> first;
            std::cin >> second;
            std::cin >> weight;
            vec[i][first - 1].push_back(Pair(second, weight));
            vec[i][second - 1].push_back(Pair(first, weight));
        }
        for (int j = 0; j < vertex; j++)
        {
          path[j] = 922337203685477580;
          checked[j] = 0;
        }
        std::cin >> start;
        path[start - 1] = 0;
        std::priority_queue<Pair, std::vector<Pair>, Compare> que;
        que.push(Pair(start, 0));
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
            for (int k = 0; k < vec[i][curr - 1].size(); k++)
            {
                if (path[vec[i][curr - 1][k].to - 1] > path[curr - 1] + vec[i][curr - 1][k].weight)
                {
                    path[vec[i][curr - 1][k].to - 1] = path[curr - 1] + vec[i][curr - 1][k].weight;
                    que.push(Pair(vec[i][curr - 1][k].to, path[vec[i][curr - 1][k].to - 1]));
                }
            }
        }
        for (int j = 0; j < vertex; j++)
        {
            if (checked[j] && start - 1 != j)
            {
                std::cout << path[j] << " ";
            }
            else if (start - 1 != j)
            {
                std::cout << -1 << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
