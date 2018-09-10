#pragma once
template<typename T>
struct Node
{
	Node* left;
	Node*right;
	Node* parent;
	int key;
	T data;
};
template<typename T>
class BinarySearchTree2
{
private:
	Node<T>* root;
	unsigned int size;
	//help functions - Big 4

	void CopyTree(const BinarySearchTree2&);
	void CopyNode(const Node<T>*const,Node<T>*&, Node<T>*&);
	void DeleteTree();
	void DeleteSubTree(Node<T>* const);

	//Tree Traversal

	void Pre(const Node<T>* const) const;
	void In(const Node<T>* const) const;
	void Post(const Node<T>* const) const;

	//Help functions for DeleteNode()

	   //when the Node we want to delete has:

	        //- no children

	void caseA(Node<T>*& );

	        //-has either left or right child

	void caseB(Node<T>*& );

	        //-has both left and right children

	void caseC(Node<T>*& );

	//rotation

	Node<T>* RightRotation(Node<T>*);
	Node<T>* LeftRotation(Node<T>*);

	//help function for getting the Height of a Node or a Tree

	unsigned int GetHeightOfRoot(const Node<T>* const , const unsigned int) const;
	unsigned int GetLevel(const Node<T>* const ,const T&,const int, const unsigned int) const;

	//help recursive function for balancing the tree

	void Balancer(Node<T>*);

public:
	//Big 4

	BinarySearchTree2();
	BinarySearchTree2(const BinarySearchTree2&);
	~BinarySearchTree2();
	BinarySearchTree2& operator=(const BinarySearchTree2&);

	//modifiers

	void InsertNode(const T&, const int);
	void InsertNode(const Node<T>&);
	void DeleteNode(const int );

	//Traversal

	void Preorder() const;
	void Inorder() const;
	void Postorder() const;

	//Element access

	T& GetData(const int =0);
	const T& GetData(const int = 0) const;
	const Node<T>* const GetNode(const int = 0) const;
	Node<T>* GetNode(const int = 0);
	const Node<T>* const GetParent(const int = 0) const;
	Node<T>* GetParent(const int = 0);
	const Node<T>* const GetChild(const bool =0,const int = 0) const;
	Node<T>* GetChild(const bool =0,const int = 0);
	const Node<T>* const GetMaxNode() const;
	Node<T>* GetMaxNode();
	const Node<T>* const GetMinNode() const;
	Node<T>* GetMinNode();
	T& maxData();
	const T& maxData() const;
	T& minData();
	const T& minData() const;
	unsigned int GetHeightOfSubTree(const Node<T>* const) const;
	unsigned int GetLevelOfNode(const Node<T>* const) const;
	unsigned int GetLevelOfNode(const T&, const int) const;
	int GetBalance(const Node<T>* const) const;

	//Function for balancing the binary search tree

	void BringBalance();
};
template<typename T>
inline BinarySearchTree2<T>::BinarySearchTree2() :size(0)
{
	root = nullptr;
}
template<typename T>
inline BinarySearchTree2<T>::BinarySearchTree2(const BinarySearchTree2<T>&A)
{
	CopyTree(A);
}
template<typename T>
inline BinarySearchTree2<T>::~BinarySearchTree2()
{
	DeleteTree();
}
template<typename T>
inline BinarySearchTree2<T>& BinarySearchTree2<T>::operator=(const BinarySearchTree2<T>&A)
{
	if (this != &A)
	{
		DeleteTree();
		CopyTree(A);
	}
	return *this;
}
template<typename T>
inline void BinarySearchTree2<T>::CopyTree(const BinarySearchTree2<T>&A)
{
	size = A.size;
	if (A.root == nullptr)
	{
		root = nullptr;
		return;
	}
	else
	{
		try
		{
			Node<T>* source = A.root;
			CopyNode(nullptr,this->root, source);
		}
		catch (std::bad_alloc& maybe)
		{
			std::cerr << "Couldnt allocate enough memory" << std::endl;
			exit(0);
		}
	}
}
template<typename T>
inline void BinarySearchTree2<T>::CopyNode(const Node<T>* const par,Node<T>*& curr, Node<T>*& toCopy)
{
	if (toCopy == nullptr)
	{
		curr = nullptr;
		return;
	}
	curr = new Node<T>;
	curr->key = toCopy->key;
	curr->data = toCopy->data;
	curr->parent = par;
	CopyNode(curr,curr->left, toCopy->left);
	CopyNode(curr,curr->right, toCopy->right);

}
template<typename T>
inline void BinarySearchTree2<T>::DeleteTree()
{
	if(root!=nullptr)
	DeleteSubTree(root);
}
template<typename T>
inline void BinarySearchTree2<T>::DeleteSubTree(Node<T>* const toDel)
{
	if (toDel->right != nullptr)
		DeleteSubTree(toDel->right);
	if (toDel->left != nullptr)
		DeleteSubTree(toDel->left);
	delete toDel;
}
template<typename T>
inline void BinarySearchTree2<T>::InsertNode(const T& DATA, const int KEY)
{
	Node<T>* newElement = new Node<T>;
	newElement->key = KEY;
	newElement->data = DATA;
	newElement->left = nullptr;
	newElement->right = nullptr;
	newElement->parent = nullptr;
	if (root == nullptr)
	{
		root = newElement;
		newElement->parent = nullptr;
		size++;
		return;
	}
	Node<T>* temp = root;
	while (true)
	{
		if (temp->key < KEY)
		{
			if (temp->right == nullptr)
			{
				temp->right = newElement;
				newElement->parent = temp;
				size++;
				return;
			}
			temp = temp->right;
		}
		else if (temp->key > KEY)
		{
			if (temp->left == nullptr)
			{
				temp->left = newElement;
				newElement->parent = temp;
				size++;
				return;
			}
			temp = temp->left;
		}
		else if (temp->key == KEY)
		{
			std::cerr << "Error cannot include duplicates" << std::endl;
			return;
		}
	}
}
template<typename T>
void BinarySearchTree2<T>::InsertNode(const Node<T>&A)
{
	InsertNode(A.data, A.key);
}
template<typename T>
inline void BinarySearchTree2<T>::Pre(const Node<T>* const curr) const
{
	if (curr == nullptr)
	{
		return;

	}
	std::cout << curr->data << std::endl;
	Pre(curr->left);
	Pre(curr->right);
}
template<typename T>
inline void BinarySearchTree2<T>::In(const Node<T>* const curr) const
{
	if (curr == nullptr)
	{
		return;
	}
	In(curr->left);
	std::cout << curr->data << std::endl;
	In(curr->right);
}
template<typename T>
inline void BinarySearchTree2<T>::Post(const Node<T>* const curr) const
{
	if (curr == nullptr)
	{
		return;
	}
	In(curr->left);
	In(curr->right);
	std::cout << curr->data << std::endl;
}
template<typename T>
inline void BinarySearchTree2<T>::Preorder() const
{
	Pre(root);
}
template<typename T>
inline void BinarySearchTree2<T>::Inorder() const
{
	In(root);
}
template<typename T>
inline void BinarySearchTree2<T>::Postorder() const
{
	Post(root);
}
//caseA : the node hasnt got any children
template<typename T>
inline void BinarySearchTree2<T>::caseA(Node<T>*& loc)
{
	if (loc->parent == nullptr)
	{
		root = nullptr;
	}
	else
	{
		if (loc == loc->parent->left)
		{
			loc->parent->left = nullptr;

		}
		else if (loc == loc->parent->right)
		{
			loc->parent->right = nullptr;
		}
	}
}
//case B : the node has only 1 child
template<typename T>
inline void BinarySearchTree2<T>::caseB(Node<T>*& loc)
{
	Node<T>* child = nullptr;
	if (loc->right != nullptr)
	{
		child = loc->right;
	}
	else if (loc->left != nullptr)
	{
		child = loc->left;
	}
	if (loc->parent == nullptr)
	{
		root = child;
		child->parent = nullptr;
	}
	else
	{
		if (loc == loc->parent->left)
		{
			loc->parent->left = child;
		}
		else if (loc == loc->parent->right)
		{
			loc->parent->right = child;
		}
		child->parent = loc->parent;
	}
}
//case C :the node has 2 children
template<typename T>
inline void BinarySearchTree2<T>::caseC(Node<T>*& loc)
{
	Node<T>* ptr = nullptr;
	Node<T>* suc = nullptr;
	ptr = loc->right;
	while (ptr->left != nullptr)
	{
		ptr = ptr->left;
	}
	suc = ptr;
	if (suc->left == nullptr&&suc->right == nullptr)
	{
		caseA(suc);
	}
	else
	{
		caseB(suc);
	}
	if (loc->parent == nullptr)
	{
		root = suc;
		suc->parent = nullptr;
	}
	else
	{
		if (loc == loc->parent->left)
		{
			loc->parent->left = suc;
		}
		else
		{
			loc->parent->right = suc;
		}
		suc->parent = loc->parent;
	}
	suc->left = loc->left;
	suc->right = loc->right;
}
//            100
//       60          120
//      30  74     110  140
//                105         Delete 100


  //           105
 //       60        120
//     30  74     110  140
template<typename T>
inline void BinarySearchTree2<T>::DeleteNode(const int KEY)
{
	//Node<T>* parent = nullptr;
	Node<T>* location = nullptr;
	if (root == nullptr)
	{
		return;
	}
	location = GetNode(KEY);
	if (location == nullptr)
	{
		return;
	}
	if (location->left == nullptr&&location->right == nullptr)
	{
		caseA(location);
	}
	if (location->left != nullptr&&location->right == nullptr)
	{
		caseB(location);
	}
	if (location->left == nullptr&&location->right != nullptr)
	{
		caseB(location);
	}
	if (location->left != nullptr&&location->right != nullptr)
	{
		caseC(location);
	}
	size--;
	delete location;
	std::cout << "lol" << std::endl;
}
template<typename T>
inline Node<T>* BinarySearchTree2<T>::RightRotation(Node<T>* node)
{
	if (node == nullptr || node->left == nullptr)
	{
		std::cout << "Operation unsuccesful" << std::endl;
		return nullptr;
	}
	Node<T>* Subroot = node->parent;
	Node<T>* B = node->left;
	node->left = B->right;
	if (B->right != nullptr)
	{
		(B->right)->parent = node;
	}
	B->right = node;
	node->parent = B;
	if (Subroot != nullptr)
	{
		Subroot->left == node ? Subroot->left = B : Subroot->right = B;
	}
	else
	{
		root = B;
		B->parent = nullptr;
	}
	return B;
}
template<typename T>
inline Node<T>* BinarySearchTree2<T>::LeftRotation(Node<T>* node)
{
	if (node == nullptr || node->right == nullptr)
	{
		std::cout << "Operation unsuccesful" << std::endl;
		return nullptr;
	}
	Node<T>* Subroot = node->parent;
	Node<T>* C = node->right;
	node->right = C->left;
	if (C->left != nullptr)
	{
		(C->left)->parent = node->right;
	}
	C->left = node;
	node->parent = C;
	if (Subroot != nullptr)
	{
		Subroot->right == node ? Subroot->right = C : Subroot->left = C;
	}
	else
	{
		root = C;
		C->parent = nullptr;
	}
	return C;
}
template<typename T>
inline const Node<T>* const BinarySearchTree2<T>::GetNode(const int KEY) const
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->key == KEY)
	{
		return root;
	}
	Node<T>* loc = root;
	while (loc != nullptr)
	{
		if (loc->key < KEY)
		{
			loc = loc->right;
		}
		else if (loc->key > KEY)
		{
			loc = loc->left;
		}
		else
		{
			return loc;
		}
	}
	return nullptr;
}
template<typename T>
inline Node<T>* BinarySearchTree2<T>::GetNode(const int KEY)
{
	return const_cast<Node<T>*>(static_cast<const BinarySearchTree2<T>&>(*this).GetNode(KEY));
}
template<typename T>
inline T& BinarySearchTree2<T>::GetData(const int KEY)
{
	return GetNode(KEY)->data;
}
template<typename T>
inline const T& BinarySearchTree2<T>::GetData(const int KEY) const
{
	return GetNode(KEY)->data;
}
template<typename T>
inline const Node<T>* const BinarySearchTree2<T>::GetParent(const int KEY) const
{
	return GetNode(KEY)->parent;
}
template<typename T>
inline Node<T>* BinarySearchTree2<T>::GetParent(const int KEY)
{
	return GetNode(KEY)->parent;
}
template<typename T>
inline const Node<T>* const BinarySearchTree2<T>::GetChild(const bool choice, const int KEY) const
{
	return choice == 1 ?  GetNode(KEY)->right : GetNode(KEY)->left;
}
template<typename T>
inline Node<T>* BinarySearchTree2<T>::GetChild(const bool choice, const int KEY)
{
	return choice == 1 ? GetNode(KEY)->right : GetNode(KEY)->left;
}
template<typename T>
const Node<T>* const BinarySearchTree2<T>::GetMaxNode() const
{
	if (root == nullptr)
	{
		std::cerr << "The tree is empty" << std::endl;
		return nullptr;
	}
	const Node<T>* temp = root;
	while (temp->right != nullptr)
	{
		temp = temp->right;
	}
	return temp;
}
template<typename T>
Node<T>*  BinarySearchTree2<T>::GetMaxNode()
{
	return const_cast<Node<T>*>(static_cast<const BinarySearchTree2<T>&>(*this).GetMaxNode());
}
template<typename T>
T& BinarySearchTree2<T>::maxData()
{
	return GetMaxNode()->data;
}
template<typename T>
const T&  BinarySearchTree2<T>::maxData() const
{
	return GetMaxNode()->data;
}
template<typename T>
const Node<T>* const BinarySearchTree2<T>::GetMinNode() const
{
	if (root == nullptr)
	{
		std::cerr << "The tree is empty" << std::endl;
		return nullptr;
    }
	const Node<T>* temp = root;
	while (temp->left != nullptr)
	{
		temp = temp->left;
	}
	return temp;
}
template<typename T>
Node<T>* BinarySearchTree2<T>::GetMinNode() 
{
	return const_cast<Node<T>*>(static_cast<const BinarySearchTree2<T>&>(*this).GetMinNode());
}
template<typename T>
T&  BinarySearchTree2<T>::minData()
{
	return GetMinNode()->data;
}
template<typename T>
const T&  BinarySearchTree2<T>::minData() const
{
	return GetMinNode()->data;
}
template<typename T>
inline unsigned int BinarySearchTree2<T>::GetHeightOfSubTree(const Node<T>* const r) const
{	
	if (r == nullptr)
	{
		return 0;
	}
	return GetHeightOfRoot(r, 1);
}
template<typename T>
inline unsigned int BinarySearchTree2<T>::GetHeightOfRoot(const Node<T>* const node,const unsigned int counter) const
{
	if (node == nullptr)
	{
		return counter-1;
	}
	int temp1 = GetHeightOfRoot(node->left,counter+1);
	int temp2 = GetHeightOfRoot(node->right,counter+1);
	if (temp1 > temp2)
	{
		return temp1;
	}
	return temp2;  	
}

template<typename T>
inline unsigned int BinarySearchTree2<T>::GetLevelOfNode(const Node<T>* const toSearch) const
{
	if (toSearch == nullptr)
	{
		return 0;
	}
	return GetLevel(root, toSearch->data,toSearch->key, 1);
}
template<typename T>
inline unsigned int BinarySearchTree2<T>::GetLevelOfNode(const T&DATA, const int KEY) const
{
	return GetLevel(root, DATA, KEY, 1);
}
//the root is at the first level
template<typename T>
inline unsigned int BinarySearchTree2<T>::GetLevel(const Node<T>* const curr, const T& DATA,const int KEY, const unsigned int counter) const
{
	if (curr == nullptr)
	{
		return 0;
	}
	else if (curr->data ==DATA&&curr->key == KEY)
	{
		return counter;
	}
	int temp1 = GetLevel(curr->left,DATA,KEY, counter + 1);
	int temp2 = GetLevel(curr->right,DATA,KEY, counter + 1);
	if (temp1 == 0 && temp2 == 0)
	{
		return 0;
	}
	return temp1 != 0 ? temp1 : temp2;
}
template<typename T>
inline int BinarySearchTree2<T>::GetBalance(const Node<T>* const curr) const
{
	if (curr == nullptr)
	{
		return 0;
	}
	return GetHeightOfSubTree(curr->left) - GetHeightOfSubTree(curr->right);
}
template<typename T>
inline void BinarySearchTree2<T>::BringBalance()
{
	if (root == nullptr||size==1)
	{
		return;
	}
	Balancer(root);
}
template<typename T>
inline void BinarySearchTree2<T>::Balancer(Node<T>*curr)
{
	if (curr == nullptr)
	{
		return;
	}
	Node<T>* temp = nullptr;
	//left rotation
	if (GetBalance(curr) > 1)
	{
		//right rotation
		if (GetBalance(curr->left) <=-1)
		{
			temp = LeftRotation(curr->left);
			Balancer(temp);
		}
		//left rotation
		temp = RightRotation(curr);
		Balancer(temp);
	}
	//right rotataion
	else if (GetBalance(curr) < -1)
	{
		//left rotation
		if (GetBalance(curr->right) >= 1)
		{
			temp = LeftRotation(curr->right);
			Balancer(temp);
		}
		temp = LeftRotation(curr);
		Balancer(temp);
	}
}
