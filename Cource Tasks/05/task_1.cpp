#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

struct Node
{
  int pos;
  Node* next;
};

int main() {
    int size=0;
    std::cin>>size;
    Node* start=new Node{1,nullptr};
    Node* curr=start;
    Node* prev=start;
    for(int i=3;i<=size;i+=2)
    {
        curr=new Node{i,nullptr};
        prev->next=curr;
        prev=curr;
    }
    curr->next=start;
    //Node* iter=start;
     Node* iter=nullptr;
    if(size%2==0)
       iter=start;
    else
       iter=curr;
   while(size!=0)
    {
        iter->next=iter->next->next;
        iter=iter->next;
        size--;
    }
    std::cout<<iter->pos<<std::endl;
    return 0;
}
