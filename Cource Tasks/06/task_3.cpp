#include <iostream>
#include <vector>
struct Node
{
    Node* parent;
    //in which ladder is the current node
    int ladder;
    //the position in the ladder,the posotions are reversed instead of 1 2 3 4 it will be 4 3 2 1
    int pos;
    int data;
};
//arrays of vectors which contain all of the ladders
std::vector<Node*> ladders[500002];
//array which contains all the leaves
Node* leaves[500002];
//storing the Nodes in an array, which will use for getting a node with 0(1) time complexity from the array 
Node arr[500002];
int main() {
    std::ios_base::sync_with_stdio(false);
    int size=0;
    std::cin>>size;
    int size1=0;
    int size2=0;
    leaves[0]=&arr[0];
    arr[0].parent=nullptr;
    arr[0].data=1;
    arr[0].ladder=-1;
    //getting the leaves and the nodes 
    for(int i=0;i<size-1;i++)
    {
        std::cin>>size1;
        std::cin>>size2;
        if(arr[size2-1].data==0)
        {
            leaves[size2-1]=&arr[size2-1];
            leaves[size1-1]=nullptr;
            arr[size2-1].parent=&arr[size1-1];
                arr[size2-1].data=size2;
                arr[size2-1].ladder=-1;
        }
        else
        {
            leaves[size1-1]=&arr[size1-1];
            leaves[size2-1]=nullptr;
            arr[size1-1].parent=&arr[size2-1];
                arr[size1-1].data=size1;
             arr[size1-1].ladder=-1;
        }
        
    }
    //Making the ladders
    int counter=0;
    int position=0;
    for(int i=0;i<500002;i++)
    {
        if(leaves[i]!=nullptr)
        {
            position=0;
            Node* curr=leaves[i];
            while(curr!=nullptr)
            {
                //if the node is currently in another ladder
                if(curr->ladder!=-1) break;
                curr->ladder=counter;
                curr->pos=position++;
                ladders[counter].push_back(curr);
                curr=curr->parent;
            }
        }
        counter++;
    }
   int queries=0;
    std::cin>>queries;
    Node* curr=nullptr;
    for(int i=0;i<queries;i++)
    {
          std::cin>>size1;
         std::cin>>size2;
        curr=&arr[size1-1];
        while(true)
        {
          if(size2<=ladders[curr->ladder].size()-curr->pos-1)
          {
             std::cout<<ladders[curr->ladder][curr->pos+size2]->data<<std::endl; 
              break;
          }
          else
          {
           
              size2-=ladders[curr->ladder].size()-curr->pos;
              curr=ladders[curr->ladder].back()->parent;
          }
        }
    }
    return 0;
}
