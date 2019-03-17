#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Node
{
    int data;
    Node* next;
};

int main() {
  //  LinkedList list;
    int num = 0;
    std::ios_base::sync_with_stdio(false);
    std::cin>>num;
    Node* temp=new Node{num,nullptr};
    Node* prev=temp;
    Node* start=temp;
    while (std::cin>>num)
    {
        temp=new Node{num,nullptr};
        prev->next=temp;
        prev=temp;
    }
    temp->next=nullptr;
    int min = INT32_MAX;
    int max = INT32_MIN;
    long long sum = 0;
    while(start!=nullptr)
    {
        if(min>start->data)
        {
            min=start->data;
        }
        if(max<start->data)
        {
            max=start->data;
        }
        sum+=start->data;
        start=start->next;
    }
    std::cout << min << " " << max << " " << sum << std::endl;
    return 0;
}
