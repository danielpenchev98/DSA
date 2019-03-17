#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
//if K > N and the color is green/blue then RIP
struct Node
{
    int data;
    Node* next;
    Node* prev;
};
int main() {
    std::ios_base::sync_with_stdio(false);
    int size=0;
    std::cin>>size;
    std::string color="";
    int temp=0;
     std::cin>>color;
    std::cin>>temp;
      Node* curr=new Node{temp,nullptr};
    Node* previous=curr;
    Node* top=curr;
    Node* bottom=curr;
    size--;
    for(int i=0;i<size;i++)
    {
        std::cin>>color;
        std::cin>>temp;
        if(color[0]=='b')
        {
           int largest=curr->data;
           while(temp!=0&&curr!=nullptr)
           {
              
               if(largest<curr->data)
               {
                   largest=curr->data;
               }
               temp--;
               curr=curr->next;
               top=curr;
           }
           temp=largest;
        }
        else if(color[0]=='g')
        {
            long long sum=0;
            while(temp!=0&&curr!=nullptr)
            {
                sum+=curr->data;
                curr=curr->next;
                top=curr;
                temp--;
            }
            temp=sum;
        }
        previous=curr;
        curr=new Node{temp,previous,nullptr};
        if(previous!=nullptr)
           previous->prev=curr;
        else
           bottom=curr;
        top=curr;
    }
    while(bottom!=nullptr)
    {
        std::cout<<bottom->data<<" ";
        bottom=bottom->prev;
    }
    return 0;
}
