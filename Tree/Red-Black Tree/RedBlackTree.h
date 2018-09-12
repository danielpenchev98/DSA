#pragma once
#include "BST.h"
//The Red-Black Tree should follow these 5 rules:
//1. Every node is either black or red
//2. The root is black
//3. Every leaf(nullptr) is black
//4. If a node is red, then both its children are black
//5. For each node, all simple paths from the node to descendatn leaves contain the same number of black nodes
template<typename T>
class RedBlackTree : public BinarySearchTree2<T>
{
private:
	void RBInsertFixup(Node<T>*&);
	bool RBTransplant(Node<T>*&, Node<T>*&);
	void RBDeleteFixup(Node<T>*&,Node<T>*&,const bool);
	void RBDelete(Node<T>*&);
public:
	void InsertNode(const Node<T>&) override;
	void InsertNode(const T&, const int) override;
	void DeleteNode(const int);
};
//this implementation treats nullptr as a black node
//Note : we dont use Sentinel nodes
//How to implement RB-Insert effciently if the representation for red black trees include no storage for parent pointers
//Answer: Use stack to record the path tp the inserted note,then parent is the top element in the stack
//case 1: we pop z.p and z.p.p
//case 2: we pop z.p and z.p.p, then push z.p.p and z
//case 3: we pop z.p, z.p.p and z.p.p.p, then push z.p
template<typename T>
inline void RedBlackTree<T>::RBInsertFixup(Node<T>*&z)
{
	Node<T>* y = nullptr;
	while (z->parent!=nullptr &&z->parent->col == red)
	{
		/*
		if (z->parent->parent == nullptr&&z->parent->left!=nullptr&&z->parent->right!=nullptr)
		{
			if ((z == z->parent->left&&z->parent->right->col == black) || (z == z->parent->right&&z->parent->left->col == black))
			{
				z->col = black;
			}
		}
		
		else*/
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			//red uncle
			if (y!=nullptr&&y->col == red)
			{//case1
				z->parent->col = black;
				y->col = black;
				z->parent->parent->col = red;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->right)
				{//case 2
					z = z->parent;
					this->LeftRotation(z);
				}
				//case 3
				z->parent->col = black;
				z->parent->parent->col = red;
				this->RightRotation(z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;
			//red uncle
			if ( y!=nullptr&&y->col == red)
			{
				z->parent->col = black;
				y->col = black;
				z->parent->parent->col = red;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					this->RightRotation(z);
				}
				z->parent->col = black;
				z->parent->parent->col = red;
				this->LeftRotation(z->parent->parent);
			}
		}
	}
	this->root->col = black;
}
template<typename T>
inline void RedBlackTree<T>::InsertNode(const Node<T>&A)
{
	InsertNode(A.data, A.key);
}
template<typename T>
inline void RedBlackTree<T>::InsertNode(const T&DATA, const int KEY)
{
	BinarySearchTree2<T>::InsertNode(DATA, KEY);
	Node<T>* temp = this->GetNode(KEY);
	if (temp != nullptr)
	{
		temp->col = red;
		RBInsertFixup(temp);
	}
}
// if x is nullptr then we canno find if it is left or right child so we need the bool choice to find out
template<typename T>
bool RedBlackTree<T>::RBTransplant(Node<T>*&A, Node<T>*&B)
{
	bool choice = 0;
	if (A->parent == nullptr)
	{
		this->root = B;
	}
	else if (A==A->parent->left)
	{
		A->parent->left = B;
		choice = 0;
	}
	else if (A == A->parent->right)
	{
		A->parent->right = B;
		choice = 1;
	}
	if (B != nullptr)
		B->parent = A->parent;
	return choice;
}
//xpar why we need it? Insteal of using Sentinel nodes the program uses nullptrs which basically are black children, and we cannot get the parent of it, so we need to story it additionaly 
template<typename T>
void RedBlackTree<T>::RBDeleteFixup(Node<T>*&x,Node<T>*&xpar,const bool choice)
{
	Node<T>* w = nullptr;
	while (x != this->root&&(x == nullptr||x->col == black))
	{
		if (x == xpar->left&&choice==0)
		{
			w = xpar->right;
			if (w != nullptr)
			{
				//case 1:x's sibling w is red
				if (w->col == red)
				{
					w->col = black;
					xpar->col = red;
					this->LeftRotation(xpar);
					w = xpar->right;
				}
				//case 2: x's sibling w is black and both w's children are black
				if ((w->left&&w->right&&w->left->col == black && w->right->col == black)||(!w->left&&!w->right)||(!w->left&&w->right&&w->right->col==black)||(!w->right&&w->left&&w->left->col == black))
				{
					w->col = red;
					x = xpar;
				}
				//case 3: x's sibling w is black, w's left child is red and w's right child is black
				else if ((w->right&&w->right->col == black)||(!w->right))
				{
					if(w->left)
					w->left->col = black;
					w->col = red;
					this->RightRotation(w);
					w = xpar->right;
				}
				//case 4: x's sibling w is black abd w's right child is red
				else 
				{
					w->col =xpar->col;
					if(w->right)
					w->right->col = black;
					xpar->col = black;
					if (xpar->right)
						this->LeftRotation(xpar);
					x = this->root;
				}
			}
		}
		else
		{
			w = xpar->left;
			if (w != nullptr)
			{
				//case 1:x's sibling w is red
				if (w->col == red)
				{
					w->col = black;
					xpar->col = red;
					this->RightRotation(xpar);
					w = xpar->left;
				}
				//case 2: x's sibling w is black and both w's children are black
				if ((w->left&&w->right&&w->left->col == black && w->right->col == black) || (!w->left && !w->right) || (!w->left&&w->right&&w->right->col == black) || (!w->right&&w->left&&w->left->col == black))
				{
					w->col = red;
					x = xpar;
				}
				//case 3: x's sibling w is black, w's right child is red and w's left child is black
				else if ((w->left&&w->left->col == black)||(!w->left))
				{
					if(w->right)
					w->right->col = black;
					w->col = red;
					this->LeftRotation(w);
					w = xpar->left;
				}
				//case 4: x's sibling w is black abd w's right child is red
				else 
				{
					w->col = xpar->col;
					if (w->left)
						w->left->col = black;
					xpar->col = black;
					if (xpar->left)
						this->RightRotation(xpar);
					x = this->root;
				}
			}

		}
	}
	if(x!=nullptr)
	x->col = black;
}
template<typename T>
void RedBlackTree<T>::DeleteNode(const int KEY)
{
	Node<T>* temp = this->GetNode(KEY);
	if(temp!=nullptr)
	RBDelete(temp);
}
//this is a better version than the Delete operation in BST , should implement it also, for better performance
template<typename T>
void RedBlackTree<T>::RBDelete(Node<T>*&z)
{
	Node<T>* y = z;
	Node<T>* x = nullptr;
	Node<T>* parx = nullptr;
	bool choice = 0;
	Color yorigin = y->col;
	if (z->left == nullptr)
	{
        //case B
		x = z->right;
		parx = z->parent;
		choice=RBTransplant(z, z->right);
	}
	else if(z->right==nullptr)
	{
		//case B
		x = z->left;
		parx = z->parent;
		choice=RBTransplant(z, z->left);
	}
	else
	{
		//case C
	   y = this->SubTreeMin(z->right);
	   std::cout << y->key<< std::endl;
	   yorigin = y->col;
	   x = y->right;
	   if (y->parent == z)
	   {
		   parx = y;
		   choice = 1;
		   if (x != nullptr)
		   {
				   x->parent = y;
		   }
	   }
	   else
	   {
		   parx = y->parent;
		   choice=RBTransplant(y, y->right);
		   y->right = z->right;
		   y->right->parent = y;
	   }
	   RBTransplant(z, y);
	   y->left = z->left;
	   y->left->parent = y;
	   y->col = z->col;
    }
	delete z;
	if (yorigin == black)
	{
			RBDeleteFixup(x,parx,choice);
	}
   
}