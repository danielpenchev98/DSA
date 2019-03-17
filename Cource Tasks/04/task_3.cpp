#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Node
{
    Node* addBallOn;
    long long value;
};
int main()
{
    int size = 0;
    std::cin >> size;
    Node* arr = new Node[size+1];
    arr[0].addBallOn = nullptr;
    arr[0].value = 0;
    int add = 0;
    int from = 0;
    long long sum = 0;
    for (int i = 1; i <= size; i++)
    {
        std::cin >> from;
        std::cin >> add;
        if (add > 0)
        {
            arr[i].addBallOn = &arr[from];
            arr[i].value = arr[from].value + add;
        }
        else
        {
            arr[i].addBallOn = arr[from].addBallOn->addBallOn;
            arr[i].value = arr[from].addBallOn->value;
        }
        sum += arr[i].value;
    }
    std::cout << sum << std::endl;
    return 0;
}
