#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Node
{
    int data;
    Node* next;
    Node* prev;
};
class LinkedList
{
private:
    Node* start;
    Node* tail;
    Node* mid;
public:
    int counter;
    LinkedList();
    void PushBack(const int data);
    void PopFrontAndPushBack(const int num);
    void PopBack();
    void Print() const;
};
LinkedList::LinkedList() :start(nullptr), tail(nullptr), counter(0)
{
}
void LinkedList::Print() const
{
    Node* temp = start;
    while (temp != nullptr)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
}
void LinkedList::PushBack(const int data)
{
    counter++;
    Node* newElement = new Node{ data,nullptr,nullptr };
    //if its the first element
    if (start == nullptr)
    {
        start = newElement;
        mid = nullptr;
        tail = start;
        return;
    }
    //if the number of increased nodes is even 
    if (counter % 2 == 0)
    {
        //mid was nullptr before cuz counter-1=1
        if (counter == 2)
        {
            mid = start;
        }
        else
        {
            mid = mid->next;
        }
    }
    tail->next = newElement;
    newElement->prev = tail;
    tail = newElement;
}
void LinkedList::PopBack()
{
    counter--;
    if (start == tail)
    {
        mid = nullptr;
        start = nullptr;
        tail = nullptr;
        //here armqnov would have got stroke if he had looked at the line below 
        // delete toDel;
        return;
    }
    /*
    while (temp->next != tail)
    {
        temp = temp->next;
    }
    */
    if (counter % 2 == 1)
    {
        if (counter == 1)
        {
            mid = nullptr;
        }
        else
        {
            mid = mid->prev;
        }
    }
    //toDel = temp->next;
    Node* temp = tail->prev;
    (tail->prev)->next = nullptr;
    tail = temp;
    //should have deleted toDel but performance uber Alles
    //delete toDel;
}
void LinkedList::PopFrontAndPushBack(const int num)
{
    if (num > 0)
    {
        Node* newStart = mid->next;
        (mid->next)->prev = nullptr;
        mid->next = nullptr;
        start->prev = tail;
        tail->next = start;
        Node* last = mid;
        if (counter % 2 == 1)
        {
            mid = tail->prev;
        }
        else
        {
            mid = tail;
        }
        start = newStart;
        tail = last;
    }
}
int main() {
    LinkedList list;
    int size=0;
    std::cin>>size;
    int num=0;
     std::string input="";
     std::ios_base::sync_with_stdio(false);
    for(int i=0;i<size;i++)
    {
       std::cin>>input;
       if(input[0]=='a')
       {
           std::cin>>num;
           list.PushBack(num);
       }
       else if(input[0]=='g')
       {
           list.PopBack();
       }
       else 
       {
          list.PopFrontAndPushBack(list.counter/2);
       }
    }
    std::cout<<list.counter<<'\n';
    list.Print();
    return 0;
}
