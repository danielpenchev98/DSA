#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
struct TrieNode
{
    TrieNode* next[26];
    int repeated;
    TrieNode()
    {
        repeated = -1;
        for (int i = 0; i < 26; i++)
        {
            next[i] = nullptr;
        }
    }
};
class Trie
{
public:
    TrieNode* root;
    Trie()
    {
        
        root = new TrieNode;
    }
    bool CheckInsert(std::string& toCheck)
    {
        int counter = 0;
        TrieNode* curr = root;
       
        
         
            while (counter < toCheck.size())
            {
            
                if (curr->next[(int)(toCheck[counter]) % 97] != nullptr)
                {
                    curr = curr->next[(int)(toCheck[counter]) % 97];
                    counter++;
                    continue;
                }
                break;
            }
        
            if (counter == toCheck.size())
            {  
                
                if(curr->repeated>=0)
                toCheck = toCheck +" "+ std::to_string((++curr->repeated)+1);
              else
                    curr->repeated++;
                return 1;
            
            }
            else
            {
               
                int counter2 = counter;
                while (counter < toCheck.size())
                {
              
                    curr->next[(int)(toCheck[counter]) % 97] = new TrieNode;
                    curr = curr->next[(int)(toCheck[counter]) % 97];
                    counter++;
                }
                curr->repeated++;
                toCheck = toCheck.substr(0, counter2+1);
                return 0;
            }
        
    }
};
int main() {
    std::string name = "";
    int size = 0;
    std::cin >> size;
    Trie trie;
    for(int i=0;i<size;i++)
    {
        std::cin>>name;
        trie.CheckInsert(name);
            std::cout<<name<<std::endl;
        
    }
    
    return 0;
}
