#include <cmath>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
int arr[5000][5000];

struct Pair
{
    int x;
    int y;
    int level;
    Pair(int x_, int y_,int lv) :x(x_), y(y_), level(lv) {}
};

bool CheckIfGood(const int x, const int y, const int rows, const int cols)
{
    if (x >= 0 && x < rows&&y >= 0 && y < cols&&arr[x][y] == 0) return true;
    return false;
}
int main() {
    int rows = 0;
    int cols = 0;
    int queries = 0;
    std::cin >> rows;
    std::cin >> cols;
    std::cin >> queries;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> arr[i][j];
            if (arr[i][j] == 1)
            {
                arr[i][j] = -1;
            }
        }
    }
    arr[0][0]=1;
    std::queue<Pair*> container;
    container.push(new Pair(0, 0,0));
    int x = 0;
    int y = 0;
    int level=0;
    int counter = 0;
    while (!container.empty())
    {
        x = container.front()->x;
        y = container.front()->y;
        level=container.front()->level;
        container.pop();
       // std::cout<<"x :"<<x<<" y :"<<y<<std::endl;
        if (CheckIfGood(x, y + 1, rows, cols))
        {
            arr[x][y + 1] = level+1;
            container.push(new Pair{x, y + 1,level+1});
        }
        if (CheckIfGood(x, y - 1, rows, cols))
        {
            arr[x][y - 1] = level+1;
            container.push(new Pair{x, y - 1,level+1});
        }
        if (CheckIfGood(x - 1, y, rows, cols))
        {
            arr[x - 1][y] = level+1;
            container.push(new Pair{x - 1, y,level+1});
        }
        if (CheckIfGood(x + 1, y, rows, cols))
        {
            arr[x + 1][y] = level+1;
            container.push(new Pair{x + 1, y,level+1});
        }
    }
    arr[0][0]=0;
    for(int i=0;i<queries;i++)
    {
        std::cin>>x;
        std::cin>>y;
        if(arr[x][y]==0&&((x!=0)||(y!=0)))
        {
             std::cout<<-1<<std::endl;
        }
        else
        std::cout<<arr[x][y]<<std::endl;
    }
    return 0;
}
