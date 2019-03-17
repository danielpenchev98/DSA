#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    std::vector<long long> vec;
    int size=0;
    std::cin>>size;
    long long num=0;
    for(int i=0;i<size;i++)
    {
        std::cin>>num;
        vec.push_back(num);
    }
    std::sort(vec.begin(), vec.end()); 
   auto last= std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    std::cout<<vec.size()<<std::endl;
 
    return 0;
}
