#include <cmath>
#include <cstdio>
#include <queue>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    int level;
    double data;
};
int main() {
    int size=0;
    std::cin>>size;
    if(size==0)
    {
        return 0;
    }
    double val=0;
    std::cin>>val;
    TreeNode* start=new TreeNode{nullptr,nullptr,0,val};
    TreeNode* curr=nullptr;
    for(int i=1;i<size;i++)
    {
        std::cin>>val;
       // std::cout<<"val :"<<val<<std::endl;
        curr=start;
        while(true)
        {
            if(curr->data>val)
            {
                 if(curr->left==nullptr)
                {
                     curr->left=new TreeNode{nullptr,nullptr,curr->level+1,val};
                  //   std::cout<<"At level :"<<curr->left->level<<std::endl;
                    break;
                }
                curr=curr->left;
            }
            else 
            {
                if(curr->right==nullptr)
                {
                    curr->right=new TreeNode{nullptr,nullptr,curr->level+1,val};
                   // std::cout<<"At level :"<<curr->right->level<<std::endl;
                    break;
                }
                curr=curr->right;
            }
        }
    }
    double sum=0;
    int count=0;
    int lev=0;
    std::queue<TreeNode*> container;
    container.push(start);
    curr=nullptr;
    while(!container.empty())
    {
        curr=container.front();
        if(curr->level==lev)
        {
        
            sum+=curr->data;
            count++;
        }
        else
        {
           
            std::cout << std::fixed<<std::setprecision(2)<<(sum/count)<<std::endl;
            lev++;
            count=1;
            sum=curr->data;
        }
        container.pop();
        if(curr->left!=nullptr)
        {
            container.push(curr->left);
        }
        if(curr->right!=nullptr)
        {
            container.push(curr->right);
        }
    }
            std::cout << std::fixed<<std::setprecision(2)<<(sum/count)<<std::endl;
  
    return 0;
}
