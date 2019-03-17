#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
struct Node
{
    char sign;
    int num;
    Node* left;
    Node* right;
};
int counterSign[2];
int allValues[2][1000000];
int index = 0;
int numberOfNums = 0;
void Add(Node* const curr)
{
    if (curr->sign == '?')
    {
        numberOfNums++;
        return;
    }
    char sign;
    if (!curr->left)
    {
        std::cin >> sign;
        curr->left = new Node{ sign,1,nullptr,nullptr };
        Add(curr->left);
    }
    if (!curr->right)
    {
        std::cin >> sign;
        curr->right = new Node{ sign,1,nullptr,nullptr};
        Add(curr->right);
    }
}

void PreOrder(Node* curr,int correction)
{
    if (curr->sign =='?')
    {
   //     std::cout<<"? ";
        curr->num = correction * 1;
        allValues[0][index] = curr->num;
        allValues[1][index] = 1;
        index++;
        curr->num == 1 ? counterSign[0]++ : counterSign[1]++;
        return;
    }
 //   std::cout<<curr->sign<<" ";
    PreOrder(curr->left,correction*1);
    PreOrder(curr->right,correction*(curr->sign == '+' ? 1 : -1));
}
void Pre(Node* curr)
{
    PreOrder(curr,1);
}
int main() {
    char sign;
    std::cin >> sign;
    Node* root = new Node{ sign,0,nullptr,nullptr };
    Node* curr = nullptr;
    Add(root);
    Pre(root);
   // std::cout << "with + sign :" << counterSign[0] << " and with negative sign :" << counterSign[1] << std::endl;
    if (counterSign[0] == counterSign[1])
    {
        for (int i = 0; i < index; i++)
        {
            std::cout << 1 << std::endl;
        }
    }
    else if (counterSign[0] > counterSign[1])
    {
        int diff = counterSign[0] - counterSign[1];
        int destribution = diff / counterSign[1];
        int left = diff % counterSign[1];
        for (int i = 0; i < index; i++)
        {
            if (allValues[0][i] == -1)
            {
                if(left>=1)
                {
                std::cout << allValues[1][i] + destribution + 1 << std::endl;
                left--;
                }
                else  if (left == 0)
                {
                     std::cout << allValues[1][i] + destribution << std::endl;
                }
            }
            else
            {
                std::cout << 1 << std::endl;
            }
        }
      
    }
    else
    {
        int diff = counterSign[1] - counterSign[0];
        int destribution = diff / counterSign[0];
        int left = diff % counterSign[0];
        for (int i = 0; i < index; i++)
        {

            if (allValues[0][i] == 1)
            {
                if(left>=1)
                {
                std::cout << allValues[1][i] + destribution + 1 << std::endl;
                     left--;
                }
                else if (left == 0)
                {
                     std::cout << allValues[1][i] + destribution<<std::endl;
                   
                }
            }
            else
            {
                std::cout << 1 << std::endl;
            }
        }
        
    }
        
    return 0;
}
