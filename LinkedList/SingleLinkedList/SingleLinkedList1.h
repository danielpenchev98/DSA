#pragma once
#include <exception>
#include <vector>
template<typename T, typename Y>
struct Node
{
	Node(const T& DATA, const Y& KEY) :data(DATA), key(KEY) {}
	Node* next;
	T data;
	const Y key;
	void print() { std::cout << "Data :" << data << " Key :" << key << std::endl; }
};
template<typename T, typename Y>
bool operator==(const Node<T, Y>&A, const Node<T, Y>&B)
{
	if (A != nullptr&&B == nullptr || A == nullptr&&B != nullptr)
	{
		return 0;
	}
	else if (A == nullptr&&B == nullptr)
	{
		return 1;
	}
	if (A.data == B.data&&A.key == B.key)
	{
		return 1;
	}
	return 0;
}
template<typename T, typename Y>
bool operator!=(const Node<T, Y>&A, const Node<T, Y>&B)
{
	return !(A == B);
}
//swap cannot reassign their keys.Use the function member ChangeKey()
template<typename T, typename Y>
void swap(const Node<T, Y>&A, const Node<T, Y>&B)
{
	if (A == B)
	{
		return;
	}
	T tempT = A.data;
	A.data = B.data;
	B.data = temp;
}
template<typename T, typename Y>
class SingleLinkedList
{
private:
	Node<T, Y>* Start;
	int size;
	void CopyList(const SingleLinkedList&);
	void DeleteList();
public:
	class Iterator
	{
	private:
		Node<T, Y>* curr;
		static std::vector<Iterator*> container;
	public:
		static void CheckForInvalid(const Node<T, Y>*const);
		Iterator();
		Iterator(Node<T, Y>* const);
		//there isnt overload of operator = because the iterator is already listed in the container of iterators
		Iterator(const Iterator&);
		~Iterator();
		bool operator!=(const Node<T, Y>* const) const;
		bool operator!=(const Iterator&) const;
		Iterator& operator++();
		Iterator operator++(const int);
		Iterator operator+(const unsigned int) const;
		Iterator& operator+=(const unsigned int);
		bool operator<(const Iterator&) const;
		bool operator<=(const Iterator&) const;
		bool operator==(const Iterator&) const;
		Node<T, Y>* operator->();
		Node<T, Y>& operator*();
		void swap(Iterator&);
		void advance(const unsigned int);
	};
	SingleLinkedList();
	SingleLinkedList(const Node<T, Y>&);
	SingleLinkedList(const SingleLinkedList&);
	~SingleLinkedList();
	SingleLinkedList& operator=(const SingleLinkedList&);
	void AddNode(const T&, const Y&);
	void AddNode(const Node<T, Y>&);
	void DeleteNode(const T&, const Y&);
	void DeleteNode(const Node<T, Y>&);
	int SearchPosNode(const T&, const Y&) const;
	int SearchPosNode(const Node<T, Y>&) const;
	const T& At(const Y&) const;
	T& At(const Y&);
	void ChangeKey(const Y&, const Y&);
	void DisplayAllNodes() const;
	void Reverse();
	//Only for int is implemented
	void Sort();
	bool IsEmpty() const;
	unsigned int Size() const;
	const Iterator begin() const;
	const Iterator end() const;
	const Node<T, Y>* const front() const;
	const Node<T, Y>* const back() const;
	void clear() noexcept;
	SingleLinkedList<T, Y>* const merge(const SingleLinkedList&) const;
	void splice(SingleLinkedList&);
	void push_front(const Node<T, Y>&);
	void push_front(const T&, const Y&);
	void pop_front();
	void push_back(const Node<T, Y>&);
	void push_back(const T&, const Y&);
	void pop_back();
};
template<typename T, typename Y>
void swap(const typename SingleLinkedList<T, Y>::Iterator& iter1, const typename SingleLinkedList<T, Y>::Iterator& iter2)
{
	iter1.swap(iter2);
}
template<typename T, typename Y>
unsigned int SingleLinkedList<T, Y>::Size() const
{
	return size;
}
template<typename T, typename Y>
std::vector<typename SingleLinkedList<T, Y>::Iterator*> SingleLinkedList<T, Y>::Iterator::container = {};
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::SingleLinkedList()
{
	Start = nullptr;
	size = 0;
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::SingleLinkedList(const Node<T, Y>&A)
{
	Node<T, Y>* newElement = new Node <T, Y>(A.data,A.key);
	newElement->next = nullptr;
	Start = newElement;
	size = 1;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::CopyList(const SingleLinkedList<T, Y>&A)
{
	if (A.Start != nullptr)
	{
		size = A.size;
		Node<T, Y>* toCopy = A.Start;
		Node<T, Y>* newElement = nullptr;
		Node<T, Y>* prevElement = nullptr;
		newElement = new Node<T, Y>(toCopy->data,toCopy->key);
		newElement->next = nullptr;
		Start = newElement;
		prevElement = Start;
		toCopy = toCopy->next;
		while (toCopy != nullptr)
		{
			newElement = new Node<T, Y>(toCopy->data,toCopy->key);
			newElement->next = nullptr;
			prevElement->next = newElement;
			prevElement = newElement;
			toCopy = toCopy->next;
		}
	}
	else
	{
		Start = nullptr;
		size = 0;
	}
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::DeleteList()
{
	Node<T, Y>* temp = nullptr;
	while (Start != nullptr)
	{
		temp = Start;
		Start = Start->next;
		Iterator::CheckForInvalid(temp);
		delete temp;
	}
}
//The invalid iterators will be pointing to nullptr
//might be a problem that .end() is an iterator which points to nullptr
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::Iterator::CheckForInvalid(const Node<T, Y>* const toDel)
{
	for (int i = 0; i < container.size(); i++)
	{
		if (container[i]->curr == toDel)
		{
			container[i]->curr = nullptr;
		}
	}
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::SingleLinkedList(const SingleLinkedList<T, Y>&A)
{
	//if Y is char* then to use partialy specialized template<typename T,char*>
	CopyList(A);
	size = A.size;
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::~SingleLinkedList()
{
	DeleteList();
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>& SingleLinkedList<T, Y>::operator=(const SingleLinkedList<T, Y>&A)
{
	if (this != &A)
	{
		DeleteList();
		CopyList(A);
	}
	return *this;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::AddNode(const T& DATA, const Y& KEY)
{
	unsigned int pos = 0;
	std::cout << "Enter position :";
	std::cin >> pos;
	try
	{
		if (pos > size)
		{
			//std::cout << "Position Overflow" << std::endl;
			throw std::out_of_range("The position is invalid");
		}
		else
		{
			size++;
			Node<T, Y>* newElement = new Node<T, Y>(DATA,KEY);
			newElement->next = nullptr;
			if (pos == 0)
			{
				if (Start == nullptr)
				{
					newElement->next = nullptr;
				}
				else
				{
					newElement->next = Start;
				}
				Start = newElement;
			}
			else if (pos == size)
			{
				Node<T, Y>* temp = Start;
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}
				if (temp == nullptr)
				{
					Start = newElement;
				}
				else
				{
					temp->next = newElement;
				}
			}
			else
			{
				Node<T, Y>* temp = Start;
				int i = 0;
				while (i != pos - 1)
				{
					temp = temp->next;
					if (temp == nullptr)
					{
						std::cout << "The Position cant be reached" << std::endl;
						break;
					}
					i++;
				}
				if (i == pos - 1)
				{
					newElement->next = temp->next;
					temp->next = newElement;
				}

			}
		}
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	catch (const std::bad_alloc& err)
	{
		std::cerr << "Couldnt allocate memory" << std::endl;
		exit(1);
	}

}
template<typename T, typename Y>
void SingleLinkedList<T, Y>::AddNode(const Node<T, Y>& element)
{
	AddNode(element.data, element.key);
}
//Should it take 1 argument the DATA or to stay the same
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::DeleteNode(const T& DATA, const Y& KEY)
{
	Node<T, Y>* temp = Start;
	if (Start == nullptr)
	{
		std::cerr << "The list is already empty" << std::endl;
		return;
	}
	bool flag = 0;
	//if temp->data is char* then RIP
	if (temp->data == DATA && temp->key == KEY)
	{
		Start = temp->next;
		flag = 1;
		Iterator::CheckForInvalid(temp);
		delete temp;
	}
	else if (temp == nullptr)
	{
		std::cout << "The list is empty." << std::endl;
	}
	else
	{
		while (temp->next != nullptr)
		{
			if (temp->next->data == DATA && temp->next->key == KEY)
			{
				Node<T, Y>* temp1 = temp->next;
				temp->next = temp1->next;
				Iterator::CheckForInvalid(temp1);
				delete temp1;
				flag = 1;
				break;
			}
			temp = temp->next;
		}
		if (flag == 0 && temp->data == DATA && temp->key == KEY)
		{
			Node<T, Y>* temp1 = temp;
			temp = temp->next;
			Iterator::CheckForInvalid(temp1);
			delete temp1;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		std::cout << "A node with this DATA isnt found" << std::endl;
	}
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::DeleteNode(const Node<T, Y>&A)
{
	DeleteNode(A.data, A.key);
}
template<typename T, typename Y>
inline int SingleLinkedList<T, Y>::SearchPosNode(const T& DATA, const Y& KEY) const
{
	Node<T, Y>* temp = Start;
	int counter = 0;
	while (temp != nullptr)
	{
		if (temp->data == DATA && temp->key == KEY)
		{
			return counter;
		}
		temp = temp->next;
		counter++;
	}
	return -1;
}
template<typename T, typename Y>
inline int SingleLinkedList<T, Y>::SearchPosNode(const Node<T, Y>&A) const
{
	return SearchPosNode(A.data, A.key;)
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::DisplayAllNodes() const
{
	Node<T, Y>* temp = Start;
	if (temp == nullptr)
	{
		std::cout << "The list is empty" << std::endl;
	}
	else
	{
		while (temp != nullptr)
		{
			std::cout << "Data :" << temp->data << " with Key:" << temp->key << std::endl;
			temp = temp->next;
		}
	}
}
template<typename T, typename Y>
inline const T& SingleLinkedList<T, Y>::At(const Y& KEY) const
{
	Iterator iter = begin();
	for (; iter <= end(); ++iter)
	{
		if (iter->key == KEY)
		{
			return iter->data;
		}
	}
}
template<typename T, typename Y>
inline T& SingleLinkedList<T, Y>::At(const Y&KEY)
{
	return const_cast<T&>(static_cast<const SingleLinkedList<T, Y>&>(*this).At(KEY));
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::Reverse()
{
	if (Start->next == nullptr)
	{
		return;
	}
	Node<T, Y>* temp1 = Start;
	Node<T, Y>* temp2 = temp1->next;
	Node<T, Y>* temp3 = temp2->next;
	temp1->next = nullptr;
	temp2->next = temp1;
	while (temp3 != nullptr)
	{
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp3->next;
		temp2->next = temp1;
	}
	Start = temp2;
}

template<typename T, typename Y>
inline Node<T, Y>* RadixSort(Node<T, Y>* const start)
{//	return start;
}
int digit(const int dig, const int k)
{
	int digit = 0;
	int counter = 0;
	int num = dig;
	while (counter < k)
	{
		digit = num % 10;
		num /= 10;
		counter++;
	}
	return digit;
}
template<typename T>
int largeDigit(Node<T, unsigned int>* const start)
{
	int large = 0;
	Node<T, unsigned int>* temp = start;
	while (temp != nullptr)
	{
		if (large < temp->key)
		{
			large = temp->key;
		}
		temp = temp->next;
	}
	int counter = 0;
	while (large != 0)
	{
		large /= 10;
		counter++;
	}
	return counter;
}

template<typename T>
inline Node<T, unsigned int>* RadixSort(Node<T, unsigned int>* const start)
{
	Node<T, unsigned int>** front = new Node<T, unsigned int>*[10];
	Node<T, unsigned int>** rear = new Node<T, unsigned int>*[10];
	Node<T, unsigned int>* ptr = nullptr;
	Node <T, unsigned int> *newStart = start;
	int i = 0, k = 0, least_dig = 1, most_dig = 0, min_dig = 0, max_dig = 0, currDig = 0;
	most_dig = largeDigit(start);
	for (k = least_dig; k <= most_dig; k++)
	{
		for (i = 0; i < 9; i++)
		{
			front[i] = nullptr;
			rear[i] = nullptr;
		}
		min_dig = 9;
		max_dig = 0;
		ptr = newStart;
		while (ptr != nullptr)
		{
			currDig = digit(ptr->key, k);
			if (min_dig > currDig)
			{
				min_dig = currDig;
			}
			if (max_dig < currDig)
			{
				max_dig = currDig;
			}
			if (front[currDig] == nullptr)
			{
				front[currDig] = ptr;
			}
			else
			{
				rear[currDig]->next = ptr;
			}
			rear[currDig] = ptr;
			ptr = ptr->next;
		}
		newStart = front[min_dig];
		for (i = min_dig; i < max_dig; i++)
		{
			if (rear[i + 1] != nullptr)
			{
				rear[i]->next = front[i + 1];
			}
			else
			{
				rear[i + 1] = rear[i];
			}
		}
		rear[max_dig]->next = nullptr;
	}
	return newStart;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::Sort()
{
	Start = RadixSort(Start);
}
template<typename T, typename Y>
inline bool SingleLinkedList<T, Y>::IsEmpty() const
{
	return Start == nullptr;
}
template<typename T, typename Y>
inline const  typename SingleLinkedList<T, Y>::Iterator const SingleLinkedList<T, Y>::begin() const
{
	Iterator temp(Start);
	return temp;
}
template<typename T, typename Y>
inline const typename SingleLinkedList<T, Y>::Iterator const SingleLinkedList<T, Y>::end() const
{
	return Iterator(nullptr);
}
template<typename T, typename Y>
inline const Node<T, Y>* const SingleLinkedList<T, Y>::front() const
{
	return Start;
}
template<typename T, typename Y>
inline const Node<T, Y>* const SingleLinkedList<T, Y>::back() const
{
	if (Start == nullptr)
	{
		std::cerr << "The list is empty" << std::endl;
		return nullptr;
	}
	Node<T, Y>* temp = Start;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	return temp;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::clear() noexcept
{
	DeleteList();
	Start = nullptr;
	size = 0;
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::Iterator::Iterator()
{
	curr = nullptr;
	container.push_back(this);
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::Iterator::Iterator(Node<T, Y>* const  toLink)
{
	curr = toLink;
	container.push_back(this);
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::Iterator::Iterator(const typename SingleLinkedList<T, Y>::Iterator&A)
{
	curr = A.curr;
	container.push_back(this);
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>::Iterator::~Iterator()
{
	for (int i = 0; i < container.size(); i++)
	{
		if (this == container[i])
		{
			container.erase(container.begin() + i);
			break;
		}
	}
}
template<typename T, typename Y>
inline typename SingleLinkedList<T, Y>::Iterator& SingleLinkedList<T, Y>::Iterator::operator++()
{
	try
	{
		if (curr == nullptr)
		{
			throw std::out_of_range("Out of range");
		}
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	curr = curr->next;
	return *this;
}

template<typename T, typename Y>
inline typename SingleLinkedList<T, Y>::Iterator SingleLinkedList<T, Y>::Iterator::operator++(const int)
{
	Iterator temp(*this);
	++(*this);
	return temp;
}
template<typename T,typename Y>
inline typename SingleLinkedList<T, Y>::Iterator SingleLinkedList<T,Y>::Iterator::operator+(const unsigned int adv) const
{
	Iterator temp(*this);
	temp.advance(adv);
	return adv;
}
template<typename T,typename Y>
inline typename SingleLinkedList<T, Y>::Iterator& SingleLinkedList<T, Y>::Iterator::operator+=(const unsigned int adv)
{
	//copy-swap strategy - if an exception is thrown *this wont be harmed
	Iterator temp = this->operator+(adv);
	this->swap(temp);
	return *this;
}
template<typename T,typename Y>
inline bool SingleLinkedList<T, Y>::Iterator::operator<(const typename SingleLinkedList<T, Y>::Iterator&A) const
{
	Iterator temp(*this);
	while (temp->curr != nullptr)
	{
		++temp;
		if (temp == A)
		{
			return 1;
		}
	}
	return 0;
}
template<typename T,typename Y>
inline bool SingleLinkedList<T, Y>::Iterator::operator<=(const typename SingleLinkedList<T, Y>::Iterator&A) const
{
	Iterator temp(*this);
	if (temp.curr==A.curr) return 1;
	return this->operator<(A);
}
template<typename T, typename Y>
inline bool SingleLinkedList<T, Y>::Iterator::operator==(const typename SingleLinkedList<T, Y>::Iterator&A) const
{
	return (curr == A.curr);
}
template<typename T, typename Y>
inline Node<T, Y>*  SingleLinkedList<T, Y>::Iterator::operator->()
{
	try
	{
		if (this->curr == nullptr)
		{
			throw std::runtime_error("The Iterator is invalid");
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return curr;
}
template<typename T, typename Y>
inline Node<T, Y>& SingleLinkedList<T, Y>::Iterator::operator*()
{
	try {
		if (this->curr == nullptr)
		{
			throw std::runtime_error("The Iterator is invalid");
			//return nullptr;
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	return *curr;
}
template<typename T, typename Y>
inline bool SingleLinkedList<T, Y>::Iterator::operator!=(const Node<T, Y>* const toCheck) const
{
	return !(curr == toCheck);
}
template<typename T, typename Y>
inline bool SingleLinkedList<T, Y>::Iterator::operator!=(const typename SingleLinkedList<T, Y>::Iterator&A) const
{
	return !(curr == A.curr);
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::Iterator::swap(Iterator&A)
{
	Node<T, Y>* temp = A.curr;
	curr = A.curr;
	A.curr = temp;
};
template<typename H>
inline void Myswap(H&A, H&B)
{
	using std::swap;
	swap(A, B);
}
template<typename T, typename Y>
inline void swap(typename SingleLinkedList<T, Y>::Iterator&A, typename SingleLinkedList<T, Y>::Iterator&B)
{
	A.swap(B);
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::Iterator::advance(const unsigned int num)
{
	unsigned int counter = num;
	Iterator temp(*this);
	while (counter != 0)
	{
		if (temp.curr == nullptr)
		{
			std::cout << "The operation is cannot be accomplished" << std::endl;
			return;
		}
		++temp;
	}
	swap(temp);
}
template<typename T, typename Y>
inline void fillList(Node<T, Y>*& toFill, Node<T, Y>* source1, Node<T, Y>* source2)
{
	Node<T, Y>* curr3 = nullptr;
	while (source1 != nullptr&&source2 != nullptr)
	{
		Node<T, Y>* temp = nullptr;
		if (source1->key > source2->key)
		{
			temp = new Node<T, Y>(source2->data, source2->key);
			if (toFill == nullptr)
			{
				toFill = temp;
				curr3 = toFill;
			}
			else
			{
				curr3->next = temp;
				curr3 = curr3->next;
			}
			source2 = source2->next;
		}
		else
		{
			temp = new Node<T, Y>(source1->data, source1->key);
			if (toFill == nullptr)
			{
				toFill = temp;
				curr3 = toFill;
			}
			else
			{
				curr3->next = temp;
				curr3 = curr3->next;
			}
			source1 = source1->next;
		}
	}
	while (source1 != nullptr)
	{
		Node<T, Y>* temp = new Node<T, Y>(source1->data,source1->key);
		if (toFill == nullptr)
		{
			toFill = temp;
			curr3 = toFill;
		}
		else
		{
			curr3->next = temp;
			curr3 = curr3->next;
		}
		source1 = source1->next;
	}
	while (source2 != nullptr)
	{
		Node<T, Y>* temp = new Node<T, Y>(source2->data,source2->key);
		if (toFill == nullptr)
		{
			toFill = temp;
			curr3 = toFill;
		}
		else
		{
			curr3->next = temp;
			curr3 = curr3->next;
		}
		source2 = source2->next;
	}
	curr3->next = nullptr;
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>* const SingleLinkedList<T, Y>::merge(const SingleLinkedList<T, Y>&A) const
{
	SingleLinkedList<T, Y> temp1(*this);
	SingleLinkedList<T, Y> temp2(A);
	SingleLinkedList<T, Y>* box = new SingleLinkedList<T, Y>;
	if (temp1.Start == nullptr&&temp2.Start == nullptr)
	{
		box->Start = nullptr;
		box->size = 0;
		return box;
	}
	temp1.Sort();
	temp2.Sort();
	//Node<T, Y>* curr3 =nullptr;
	Node<T, Y>* newStart = nullptr;
	fillList(newStart, temp1.Start, temp2.Start);
	box->Start = newStart;
	box->size = A.size + this->size;
	return box;
}
template<typename T, typename Y>
inline SingleLinkedList<T, Y>* const merge(const SingleLinkedList<T, Y>&A, const SingleLinkedList<T, Y>&B)
{
	return A.merge(B);
}
//Adding all the Nodes from the A's list to *this's list and deleting A
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::splice(SingleLinkedList<T, Y>&A)
{
	if (A.Start == nullptr)
	{
		return;
	}
	Node<T, Y>* newStart = nullptr;
	fillList(newStart, this->Start, A.Start);
	unsigned int num = this->size + A.size;
	A.DeleteList();
	DeleteList();
	this->Start = newStart;
	this->size = num;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::push_front(const T&DATA, const Y&KEY)
{
	Node<T, Y>* newElement = new Node<T, Y>(DATA,KEY);
	size++;
	if (Start == nullptr)
	{
		Start = newElement;
		newElement->next = nullptr;
		return;
	}
	newElement->next = Start;
	Start = newElement;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::push_front(const Node<T, Y>&A)
{
	push_front(A.data, A.key);
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::pop_front()
{
	if (Start == nullptr)
	{
		std::cout << "Couldn't delete the first element.Its already empty" << std::endl;
		return;
	}
	Node<T, Y>* toDel = Start;
	if (size == 1)
	{
		Start = nullptr;
	}
	else
	{
		Start = Start->next;
	}
	delete toDel;
	size--;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::push_back(const T&DATA, const Y&KEY)
{
	Node<T, Y>* newElement = new Node<T, Y>(DATA,KEY);
	newElement->next = nullptr;
	size++;
	if (Start == nullptr)
	{
		curr = newElement;
		return;
	}
	Node<T, Y>* temp = Start;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = newElement;
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::push_back(const Node<T, Y>&A)
{
	push_back(A.data, A.key);
}
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::pop_back()
{
	if (Start == nullptr)
	{
		return;
	}
	else if (Start->next = nullptr)
	{
		delete Start;
		Start = nullptr;
		size--;
		return;
	}
	Node<T, Y>* last = Start;
	while (last->next->next != nullptr)
	{
		last = last->next;
	}
	Node<T, Y>* toDel = last->next;
	last->next = nullptr;
	delete toDel;
	size--;
}
//Special Function for changing the Node's const KEY
template<typename T, typename Y>
inline void SingleLinkedList<T, Y>::ChangeKey(const Y&KEY, const Y&NEWKEY)
{
	Node<T, Y>* curr = Start;
	while (curr != nullptr)
	{
		if (curr->key == NEWKEY)
		{
			std::cout << "Cannot assign new key to that node" << std::endl;
			return;
		}
		curr = curr->next;
	}
	curr = Start;
	if (curr == Start && curr->key == KEY)
	{
		Start = new Node<T, Y>(Start->data, NEWKEY);
		Start->next = curr->next;
		return;
	}
	Node<T, Y>* par = nullptr;
	while (curr != nullptr)
	{
		if (curr->key == KEY)
		{
			Node<T, Y>* toDel = curr;
			curr = new Node<T, Y>(curr->data, NEWKEY);
			curr->next = par->next->next;
			par->next = curr;
			delete toDel;
			return;
		}
		par = curr;
		curr = curr->next;
	}
	std::cout << "Coundnt find a Node with the old key" << std::endl;
}
