include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
void InsertionSort(std::string& toSort)
{
    char temp;
    int i = 0;
    int j = 0;
    for (i = 1; i < toSort.size(); i++)
    {
        temp = toSort[i];
        for (j = i - 1; j >=0&&toSort[j]>temp; j--)
        {
            toSort[j + 1] = toSort[j];
        }
        toSort[j + 1] = temp;
    }
}
void FindCommonSubString(const std::string str1, std::string str2)
{
    std::string container = "";
    for (int i = 0; i < str1.size(); i++)
    {
        for (int j = 0; j < str2.size(); j++)
        {
            if (str1[i] == str2[j])
            {
                container += str2[j];
                str2.erase(j,1);
                break;
            }
        }
    }
    InsertionSort(container);
    std::cout << container << std::endl;
}
int main()
{
    std::string str1 = "";
    std::getline(std::cin, str1);
    std::string str2 = "";
    std::getline(std::cin, str2);
    FindCommonSubString(str1, str2);
    return 0;
}
