#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
int main() {
    int tests=0;
    std::cin >> tests;
    int groups = 0;
    for (int i = 0; i < tests; i++)
    {
        std::cin >> groups;
        int counter=0;
        while(groups>0)
        {
            groups/=2;
            counter++;
        }
        std::cout<<counter<<std::endl;
    }
    return 0;
}
