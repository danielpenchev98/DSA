#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
int arr[1235][1235];
int arr2[1235];
struct Node
{
  int data;
  Node* next;
};
class LinkedList
{
private:
    Node* start;
    Node* tail;
public:
    LinkedList();
    void AddNode(const int data);
    int CountDistinctPairs() const;
};
LinkedList::LinkedList() :start(nullptr),tail(nullptr)
{
}
void LinkedList::AddNode(const int data)
{
    Node* newElement = new Node{data,nullptr};
    if (start == nullptr)
    {
        start = newElement;
        tail=start;
        return;
    }
    tail->next=newElement;
    tail=newElement;
}
int LinkedList::CountDistinctPairs() const
{
    int counter=0;
    Node* temp=start->next;
    Node* prev=start;
    while(temp!=nullptr)
    {
      
      int min=std::min(temp->data,prev->data);
        int max=(min==temp->data?prev->data:temp->data);
        if(arr[min][max]==0&&arr2[min]!=0&&arr2[max]!=0)
        {
            counter++;
            arr[min][max]++;
        }
         prev=temp;
        temp=temp->next;
       
    }
    return counter;
}
int main() {
  int size=0;
  std::cin>>size;
  LinkedList list;
  int num=0;
  for(int i=0;i<size;i++)
  {
      std::cin>>num;
      list.AddNode(num);
  }
  int sizeP=0;
  std::cin>>sizeP;
  for(int i=0;i<sizeP;i++)
  {
      std::cin>>num;
      if(num<=1234)
      arr2[num]++;
  }
  std::cout<<list.CountDistinctPairs()<<std::endl;
  return 0;
}


