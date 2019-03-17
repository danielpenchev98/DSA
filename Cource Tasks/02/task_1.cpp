#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
bool Compare(const std::string& str1, const std::string& str2)
{
    int i = 0;
    int j = 0;
    while (true)
    {
        if (str1[i] == str2[j])
        {
            if (str1.size() - 1 == i)
            {
                while (str2.size() - 1 != j && str1[i] == str2[j])
                {
                    j++;
                }
                if (str2.size() != j && str1[0] < str2[j])
                {
                    return 1;
                }
                else if (str2.size() != j && str1[0] == str2[j])
                {
                    if (str1.size() != 1 && str1[1] > str2[j])
                    {
                        return 1;
                    }
                }
               
                return 0;
                
            }
            else if (str2.size() - 1 == j)
            {
                while (str1.size() - 1 != i && str1[i] == str2[j])
                {
                    i++;
                }
                if (str1.size() != i && str1[i] > str2[0])
                {
                    if (str1.size() != 1 && str1[i] < str2[1])
                    {
                        return 1;
                    }
                    return 0;
                }
                else
                    return 1;
            }
        }
        else if (str1[i] > str2[j])
        {
            return 0;
        }
        else
        {
            return 1;
        }
        i++;
        j++;
    }
}
void InsertionSort(std::string*& arr, const int size)
{
    int i = 0;
    int j = 0;
    std::string k = "";
    for (i = 1; i < size; i++)
    {
        k = arr[i];
        for (j = i - 1; j >= 0 && Compare(arr[j], k); j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = k;
    }
}
int main()
{
    int size = 0;
    std::cin >> size;
    std::string* arr = new std::string[size];
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
    InsertionSort(arr, size);
    std::string largest = "";
    for (int i = 0; i < size; i++)
    {
        largest += arr[i];
    }
    std::string test = largest;
    test.erase(std::remove(test.begin(), test.end(), '0'), test.end());
    if (test == "")
    {
        largest = "0";
    }
    std::cout << largest << std::endl;
    delete[] arr;
    return 0;
}
