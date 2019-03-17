#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
void FindMinMaxTime(const int time[3][2])
{
    int min= 2147483647;
    int max=0;
    int temp = 0;
    for (int i = 0; i < 3; i++)
    {
        if (time[i][0] > time[i][1])
        {
            temp = time[i][1] + 24 * 60 - time[i][0];
        }
        else 
        {
            temp = time[i][1] - time[i][0];
        }
        if (min > temp)
        {
            min = temp;
        }
        if (max < temp)
        {
            max = temp;
        }
    }
    std::string start = std::to_string(min / 60);
    std::string fin = "";
    if (min % 60 < 9&&min%60!=0)
    {
        fin = "0";
    }
    fin += ((min % 60) != 0 ? std::to_string(min % 60) : "00");
    std::cout << start << ':' << fin << std::endl;
    start = std::to_string(max / 60);
    if (max % 60 < 9&&max%60!=0)
    {
        fin = "0";
    }
    else fin = "";
    fin += ((max % 60) != 0 ? std::to_string(max % 60) : "00");
    std::cout << start<< ':' <<fin << std::endl;
}

int main() {
    int time[3][2];
    int hours1 = 0;
    int minutes1 = 0;
    int hours2 = 0;
    int minutes2 = 0;
    for (int i = 0; i < 3; i++)
    {
        std::cin >> hours1;
        std::cin >> minutes1;
        std::cin >> hours2;
        std::cin >> minutes2;
        time[i][0] = 60 * hours1 + minutes1;
        time[i][1] = 60 * hours2 + minutes2;
    }
    FindMinMaxTime(time);
    return 0;
}
