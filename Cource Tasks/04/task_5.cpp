#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Node
{
    std::string sentence;
    Node* next;
};
int main()
{
    char ch;
    std::string s="";
    std::getline(std::cin,s);
    int size=std::stoi(s);
    for(int i=0;i<size;i++)
    {
      Node* curr= new Node{"",nullptr };
      Node* start = curr;
      Node*  tail = curr;
      while (std::cin.get(ch)&&ch!='\n')
      {
        if (ch != '['&&ch!=']')
        {
            curr->sentence+=ch;
        }
        else if (ch == '[')
        {
            curr = new Node{"",start };
            start = curr;
        }
        else if(ch==']')
        {
           curr=tail;
        }     
      } 
      while (start != nullptr)
      {
         std::cout << start->sentence;//<<"| and the level is"<<start->level<<std::endl;
         start = start->next;
      }
      std::cout<<'\n';
    }
    return 0;
}



