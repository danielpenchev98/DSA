#pragma once
#include <vector>
#include <exception>
//problem with begin() and end()
//how to get the keys? - through the iterators
template<typename T, typename Y>
struct Node
{
	Node(const T&DATA,const Y&KEY):data(DATA),key(KEY){}
	Node* next;
	Node* prev;
	T data;
	const Y key;
};
template<typename T, typename Y>
class CircularDoubleLinkedList
{
private:
	Node<T, Y>* last;
	int size;
	void DeleteList();
	void CopyList(const CircularDoubleLinkedList&);
public:
	class Iterator
	{
	private:
		Node<T, Y>* curr;
		//needed for loop iteration
		Node<T, Y>* iteratedFrom;
		//thanks to this container user can invalidate Iterators which are pointing to deleted Node
		static std::vector<Iterator*> container;
	public:
		//function for invalidation of the Iterator
		static void CheckForInvalid(const Node<T, Y>* const);

		//Big 4
		Iterator();
		Iterator(Node<T, Y>* const);
		//although we dont allocate new memory, we need them in order to assing nullptr to iteratedFrom
		Iterator(const Iterator&);
		Iterator& operator=(const Iterator&);
		~Iterator();

		//Operators
		bool operator!=(const Node<T, Y>* const) const;
		bool operator!=(const Iterator&) const;
		//To implement somewhen the operators < and > 
		//used for iterating ++ only
		bool operator<=(const Iterator&) const;
		//used for iterating -- only
		bool operator>=(const Iterator&) const;
		Iterator& operator +=(const int);
		Iterator operator+(const int) const;
		Iterator& operator -=(const int);
		Iterator operator -(const int) const;
		Iterator& operator++();
		Iterator operator++(const int);
		Iterator& operator--();
		Iterator operator--(const int);
		bool operator==(const Iterator&) const;
		//need further research for operators ->() const and *() const
		const Node<T, Y>* operator->() const;
		Node<T,Y>* operator->();
		const Node<T, Y>& operator*() const;
		Node<T,Y>& operator*();

		//helping functions
		void swap(Iterator&);
		void advance(const int);
	};

	//Big 4
	CircularDoubleLinkedList();
	CircularDoubleLinkedList(const CircularDoubleLinkedList&);
	CircularDoubleLinkedList(const Node<T, Y>&);
	//if the user want to assign a currently existing list
	//CircularDOubleLinkedList(const Node<T,Y>* const)
	~CircularDoubleLinkedList();
	CircularDoubleLinkedList& operator=(const CircularDoubleLinkedList&);

	//Modifiers
	void AddNode(const T&, const Y&);
	void AddNode(const Node<T, Y>&);
	void DeleteNode(const Y&);
	void DeleteNode(const Node<T, Y>&);
	int SearchPosNode(const T&, const Y&) const;
	int SearchPosNode(const Node<T, Y>&) const;
	T& At(const Y&);
	const T& At(const Y&) const;
	void ChangeKey(const Y&, const Y&);
	void ReverseList();
	void Display() const;
	void ReverseDisplay() const;
	void Sort();
	bool IsEmpty() const;
	unsigned int Size() const;
	const Iterator begin() const;
	const Iterator end() const;
	const Node<T, Y>* const front() const;
	const Node<T, Y>* const back() const;
	void clear() noexcept;
	CircularDoubleLinkedList<T, Y>* const merge(const CircularDoubleLinkedList<T, Y>&) const;
	void splice(CircularDoubleLinkedList<T, Y>&);
	void push_front(const Node<T, Y>&);
	void push_front(const T&, const Y&);
	void pop_front();
	void push_back(const Node<T, Y>&);
	void push_back(const T&, const Y&);
	void pop_back();
};
template<typename T, typename Y>
std::vector<typename CircularDoubleLinkedList<T, Y>::Iterator*> CircularDoubleLinkedList<T, Y>::Iterator::container = {};
template<typename T, typename Y>
CircularDoubleLinkedList<T, Y>::CircularDoubleLinkedList()
{
	last = nullptr;
	size = 0;
}
template<typename T, typename Y>
CircularDoubleLinkedList<T, Y>::CircularDoubleLinkedList(const CircularDoubleLinkedList&A)
{
	CopyList(A);
}
template<typename T, typename Y>
CircularDoubleLinkedList<T, Y>::CircularDoubleLinkedList(const Node<T, Y>&A)
{
	Node<T, Y>* newElement = new Node<T, Y>(A.data,A.key);
	last = newElement;
	last->next = newElement;
	last->prev = newElement;
	size = 1;
}
template<typename T, typename Y>
CircularDoubleLinkedList<T, Y>::~CircularDoubleLinkedList()
{
	DeleteList();
}
template<typename T, typename Y>
CircularDoubleLinkedList<T, Y>& CircularDoubleLinkedList<T, Y>::operator=(const CircularDoubleLinkedList<T, Y>&A)
{
	if (this != &A)
	{
		DeleteList();
		CopyList(A);
	}
	return *this;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::DeleteList()
{
	if (last == nullptr)
	{
		return;
	}
	Node<T, Y>* start = last->next;
	Node<T, Y>* temp = nullptr;
	last->next = nullptr;
	while (start != nullptr)
	{
		temp = start;
		start = start->next;
		Iterator::CheckForInvalid(temp);
		delete temp;
	}
	size = 0;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::CopyList(const CircularDoubleLinkedList<T, Y>&A)
{
	size = A.size;
	if (A.last == nullptr)
	{
		last = nullptr;
	}
	Node<T, Y>* newElement = nullptr;
	Node<T, Y>* prevElement = nullptr;
	Node<T, Y>* toCopy = A.last->next;
	newElement = new Node<T, Y>(toCopy->data,toCopy->key);
	newElement->next = nullptr;
	newElement->prev = nullptr;
	last = newElement;
	prevElement = last;
	toCopy = toCopy->next;
	while (toCopy != last)
	{
		newElement = new Node<T, Y>(toCopy->data,toCopy->key);
		newElement->prev = prevElement;
		newElement->next = nullptr;
		prevElement->next = newElement;
		prevElement = newElement;
		toCopy = toCopy->next;
	}
	newElement->next = last;
	last->prev = newElement;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::AddNode(const T&DATA, const Y&KEY)
{
	unsigned int pos = 0;
	std::cout << "Enter position :";
	std::cin >> pos;
	if (pos > size)
	{
		std::cerr << "Out of range.Cannot add the Node" << std::endl;
		return;
	}
	size++;
	Node<T, Y>* newElement = new Node<T, Y>(DATA,KEY);
	if (last == nullptr&&pos == 0)
	{
		last = newElement;
		newElement->next = last;
		newElement->prev = last;
		return;
	}
	if (pos == 0 && last->key != KEY)
	{
		newElement->next = last->next;
		newElement->prev = last;
		(last->next)->prev = newElement;
		last->next = newElement;
		return;
	}
	Node<T, Y>* temp = last->next;
	for (int i = 0; i < pos - 1; i++)
	{
		if (temp->key == KEY)
		{
			delete newElement;
			return;
		}
		temp = temp->next;
	}
	newElement->prev = temp;
	newElement->next = temp->next;
	(temp->next)->prev = newElement;
	temp->next = newElement;
	if (temp == last)
	{
		last = newElement;
	}
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::AddNode(const Node<T, Y>&A)
{
	AddNode(A.data, A.key);
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::DeleteNode(const Y&KEY)
{
	if (last == nullptr)
	{
		return;
	}
	Node<T, Y>* toDel = nullptr;
	if (last->next->key == KEY)
	{
		size--;
		toDel = last->next;
		(toDel->next)->prev = last;
		last->next = toDel->next;
		Iterator::CheckForInvalid(toDel);
		delete toDel;
		return;
	}
	Node<T, Y>* temp = last->next->next;
	while (temp != last)
	{
		if (temp->key == KEY)
		{
			size--;
			toDel = temp;
			(toDel->prev)->next = toDel->next;
			(toDel->next)->prev = toDel->prev;
			Iterator::CheckForInvalid(toDel);
			delete toDel;
			return;
		}
		temp = temp->next;
	}
	if (temp->key == KEY)
	{
		size--;
		toDel = last;
		last = toDel->prev;
		last->next = toDel->next;
		(toDel->next)->prev = last/*->next*/;
		Iterator::CheckForInvalid(toDel);
		delete toDel;
		return;
	}
	std::cout << "The node isnt found" << std::endl;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::DeleteNode(const Node<T, Y>&A)
{
	//this is just beta version
	DeleteNode(A.key);
}
//might decrease the number of arguments down to 1 :const Y& cuz maybe i need only KEY
template<typename T, typename Y>
inline int CircularDoubleLinkedList<T, Y>::SearchPosNode(const T&DATA, const Y&KEY) const
{
	//first position is last->next;
	if (last == nullptr)
	{
		std::cerr << "The list is empty" << std::endl;
		return -1;
	}
	int counter = 0;
	Node<T, Y>* temp = last->next;
	while (temp != last)
	{
		if (temp->data == DATA && temp->key == KEY)
		{
			return counter;
		}
		temp = temp->next;
		counter++;
	}
	if (temp->data == DATA && temp->key == KEY)
	{
		return counter;
	}
	std::cout << "The Node hasnt been found" << std::endl;
	return -1;
}
template<typename T, typename Y>
inline int CircularDoubleLinkedList<T, Y>::SearchPosNode(const Node<T, Y>&A) const
{
	SearchPosNode(A.data, A.key);
}
template<typename T, typename Y>
inline const T& CircularDoubleLinkedList<T, Y>::At(const Y&KEY) const
{
	CircularDoubleLinkedList<T, Y>::Iterator iter = begin();
	for (; iter <= end(); ++iter)
	{
		if (iter->key == KEY)
		{
			return iter->data;
		}
	}

}
template<typename T, typename Y>
inline T& CircularDoubleLinkedList<T, Y>::At(const Y&KEY)
{
	return const_cast<T&>(static_cast<const CircularDoubleLinkedList<T, Y>&>(*this).At(KEY));
}
template<typename T, typename Y>
void CircularDoubleLinkedList<T, Y>::ReverseList()
{
	if (last == nullptr)
	{
		return;
	}
	Node<T, Y>* temp1 = last->next;
	Node<T, Y>* temp2 = temp1->next;
	Node<T, Y>* start = temp1;
	last->next = nullptr;
	temp1->next = nullptr;
	temp1->prev = temp2;
	while (temp2 != nullptr)
	{
		temp2->prev = temp2->next;
		temp2->next = temp1;
		temp1 = temp2;
		temp2 = temp2->prev;
	}
	last = start;
	last->next = temp1;
	temp1->prev = last;

}
template<typename T, typename Y>
void CircularDoubleLinkedList<T, Y>::Display() const
{
	if (last == nullptr)
	{
		std::cout << "The list is empty" << std::endl;
		return;
	}
	Node<T, Y>* temp = last->next;
	while (temp != last)
	{
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
	std::cout << temp->data << std::endl;
}
template<typename T, typename Y>
void CircularDoubleLinkedList<T, Y>::ReverseDisplay() const
{
	if (last == nullptr)
	{
		std::cout << "The list is empty" << std::endl;
		return;
	}
	Node<T, Y>* temp = last;
	while (temp != last->next)
	{
		std::cout << temp->data << std::endl;
		temp = temp->prev;
	}
	std::cout << temp->data << std::endl;
}
template<typename T, typename Y>
inline Node<T, Y>* RadixSort(Node<T, Y>* const start)
{
	return start;
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
	(start->prev)->next = nullptr;
	start->prev = nullptr;
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
void CircularDoubleLinkedList<T, Y>::Sort()
{
	Node<T, Y>* temp = RadixSort(last->next);
	Node<T, Y>* start = temp;
	while (temp->next != nullptr)
	{
		(temp->next)->prev = temp;
		temp = temp->next;
	}
	last = temp;
	temp->next = start;
	start->prev = temp;
}
template<typename T, typename Y>
bool CircularDoubleLinkedList<T, Y>::IsEmpty() const
{
	return size == 0;
}
template<typename T, typename Y>
unsigned int CircularDoubleLinkedList<T, Y>::Size() const
{
	return size;
}
template<typename T, typename Y>
const typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::begin() const
{
	return Iterator(last->next);
}
template<typename T, typename Y>
const typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::end() const
{
	return Iterator(last);
}
template<typename T, typename Y>
const Node<T, Y>* const CircularDoubleLinkedList<T, Y>::front() const
{
	return last->next;
}
template<typename T, typename Y>
const Node<T, Y>* const CircularDoubleLinkedList<T, Y>::back() const
{
	return last;
}
template<typename T, typename Y>
void CircularDoubleLinkedList<T, Y>::clear() noexcept
{
	DeleteList();
	last = nullptr;
	size = 0;
}
//should rewrite it 
//this function creates a new "list"of Nodes from source1 and source2
template<typename T, typename Y>
inline void fillList(Node<T, Y>*& toFill, Node<T, Y>* source1, Node<T, Y>* source2)
{
	//problem when it is circular list, we have to break the bound between the first and the last element nad after the procedure to reattach them again
	Node<T, Y>* curr = nullptr;
	Node<T, Y>* s1 = nullptr;
	Node<T, Y>* s2 = nullptr;
	Node <T, Y>* f1 = nullptr;
	Node<T, Y>* f2 = nullptr;
	if (source1 != nullptr)
	{
		f1 = source1;
		s1 = source1->next;
		source1 = source1->next;
		s1->prev = nullptr;
		f1->next = nullptr;
	}
	if (source2 != nullptr)
	{
		s2 = source2->next;
		f2 = source2;
		source2 = source2->next;
		s2->prev = nullptr;
		f2->next = nullptr;
	}
	//Disconnecting the last and last->next element so we can treat it as normal DoubleLinkedList
	Node<T, Y>* newStart = nullptr;
	Node<T, Y>* temp = nullptr;
	while (source1 != nullptr&&source2 != nullptr)
	{
		if (source1->key > source2->key)
		{
			temp = new Node<T, Y>(source1->data, source1->key);
			source1 = source1->next;
		}
		else
		{
			temp = new Node<T, Y>(source2->data, source2->key);
			source2 = source2->next;
		}
		if (newStart == nullptr)
		{
			curr = temp;
			newStart = curr;
		}
		else
		{
			curr->next = temp;
			temp->prev = curr;
			curr = curr->next;
		}
	}
	while (source1 != nullptr)
	{
		temp = new Node<T, Y>(source1->data, source1->key);
		temp->key = source1->key;
		if (newStart == nullptr)
		{
			curr = temp;
			newStart = curr;
			toFill = curr;
		}
		else
		{
			curr->next = temp;
			temp->prev = curr;
			curr = curr->next;
			toFill = curr;
		}
		source1 = source1->next;
	}
	while (source2 != nullptr)
	{
		temp = new Node<T, Y>(source2->data,source2->key);
		if (newStart == nullptr)
		{
			curr = temp;
			newStart = curr;
			toFill = curr;
		}
		else
		{
			curr->next = temp;
			temp->prev = curr;
			curr = curr->next;
			toFill = curr;
		}
		source2 = source2->next;
	}
	//Connectring again the last and last->next element
	if (f1 != nullptr)
	{
		s1->prev = f1;
		f1->next = s1;
	}
	if (f2 != nullptr)
	{
		s2->prev = f2;
		f2->next = s2;
	}
	toFill->next = newStart;
	newStart->prev = toFill;
}
template<typename T, typename Y>
inline CircularDoubleLinkedList<T, Y>* const CircularDoubleLinkedList<T, Y>::merge(const CircularDoubleLinkedList<T, Y>&A) const
{
	Node<T, Y>* toInsert = nullptr;
	CircularDoubleLinkedList<T, Y>* toReturn = new CircularDoubleLinkedList<T, Y>;
	if (last == nullptr&&A.last == nullptr)
	{
		toReturn->last = nullptr;
		toReturn->size = 0;
	}
	else
	{
		CircularDoubleLinkedList<T, Y> temp1(*this);
		CircularDoubleLinkedList<T, Y> temp2(A);
		temp1.Sort();
		temp2.Sort();
		fillList(toInsert, temp1.last, temp2.last);
		toReturn->last = toInsert;
		toReturn->size = A.size + this->size;
	}
	return toReturn;
}
template<typename T, typename Y>
inline CircularDoubleLinkedList<T, Y>* const merge(const CircularDoubleLinkedList<T, Y>&A, const CircularDoubleLinkedList<T, Y>&B)
{
	return A.merge(B);
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::splice(CircularDoubleLinkedList<T, Y>&A)
{
	if (A.last == nullptr)
	{
		return;
	}
	Node<T, Y>* toAssign = nullptr;
	fillList(toAssign, this->last, A.last);
	int num = A.size + this->size;
	A.DeleteList();
	DeleteList();
	this->last = toAssign;
	this->size = num;
}
//this function adds a new last->next element
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::push_front(const Node<T, Y>&A)
{
	push_front(A.data, A.key);
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::push_front(const T&DATA, const Y&KEY)
{
	Node<T, Y>* newElement = nullptr;
	try
	{
		newElement = new Node<T, Y>(DATA,KEY);
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Enough memory cannot be allocated" << std::endl;
		return;
	}
	if (last == nullptr)
	{
		last = newElement;
		newElement->next = last;
	}
	else
	{
		Node<T, Y>* temp = last->next;
		last->next = newElement;
		newElement->next = temp;
		temp->prev = newElement;
	}
	newElement->prev = last;
	size++;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::pop_front()
{
	if (last == nullptr)
	{
		std::cout << "Its already empty" << std::endl;
		return;
	}
	Node<T, Y>* temp = last->next;
	if (size == 1)
	{
		last = nullptr;
		delete temp;
	}
	else
	{
		last->next = temp->next;
		temp->next->prev = last;
	}
	delete temp;
	size--;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::push_back(const Node<T, Y>&A)
{
	push_back(A.data, A.key);
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::push_back(const T&DATA, const Y&KEY)
{
	Node<T, Y>* newElement = new Node<T, Y>(DATA,KEY);
	size++;
	if (last == nullptr)
	{
		last = newElement;
		newElement->prev = last;
		newElement->next = last;
	}
	else
	{
		Node<T, Y>* temp = last->next;
		last->next = newElement;
		newElement->prev = last;
		temp->prev = newElement;
		newElement->next = temp;
		last = newElement;
	}
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::pop_back()
{
	if (last == nullptr)
	{
		std::cout << "Its already empty" << std::endl;
		return;
	}
	Node<T, Y>* toDel = last;
	if (size == 1)
	{
		last = nullptr;
	}
	else
	{
		last = last->prev;
		last->next = toDel->next;
		(toDel->next)->prev = last;
	}
	size--;
	delete toDel;
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::Iterator::CheckForInvalid(const Node<T, Y>* const toDel)
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
inline CircularDoubleLinkedList<T, Y>::Iterator::Iterator()
{
	curr = nullptr;
	iteratedFrom = nullptr;
	container.push_back(this);
}
template<typename T, typename Y>
inline CircularDoubleLinkedList<T, Y>::Iterator::Iterator(Node<T, Y>* const node)
{
	curr = node;
	iteratedFrom = nullptr;
	container.push_back(this);
}
template<typename T, typename Y>
inline CircularDoubleLinkedList<T, Y>::Iterator::Iterator(const typename CircularDoubleLinkedList<T, Y>::Iterator&A)
{
	curr = A.curr;
	iteratedFrom = nullptr;
	container.push_back(this);
}
template<typename T, typename Y>
inline CircularDoubleLinkedList<T, Y>::Iterator::~Iterator()
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
inline typename CircularDoubleLinkedList<T, Y>::Iterator& CircularDoubleLinkedList<T, Y>::Iterator::operator=(const Iterator&A)
{
	if (this != &A)
	{
		curr = A.curr;
		iteratedFrom = nullptr;
	}
	return *this;
}
template<typename T, typename Y>
inline bool CircularDoubleLinkedList<T, Y>::Iterator::operator!=(const Node<T, Y>* const toCompare) const
{
	return !(this->curr == toCompare);
}
template<typename T, typename Y>
inline bool CircularDoubleLinkedList<T, Y>::Iterator::operator!=(const typename CircularDoubleLinkedList<T, Y>::Iterator& toCompare) const
{
	return !(curr == toCompare.curr);
}
template<typename T, typename Y>
inline bool CircularDoubleLinkedList<T, Y>::Iterator::operator<=(const typename CircularDoubleLinkedList<T, Y>::Iterator&A) const
{
	if (iteratedFrom == nullptr) return 1;
	return !(iteratedFrom->key == A->key);
}
template<typename T, typename Y>
inline bool CircularDoubleLinkedList<T, Y>::Iterator::operator>=(const typename CircularDoubleLinkedList<T, Y>::Iterator&A) const
{
	if (iteratedFrom == nullptr) return 1;
	return !(iteratedFrom->key == A->key);
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator& CircularDoubleLinkedList<T, Y>::Iterator::operator +=(const int progress)
{
	Iterator temp(*this);
	temp.advance(progress);
	swap(temp);
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::Iterator::operator+(const int progress) const
{
	Iterator temp(*this);
	temp.advance(progress);
	return temp;
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator& CircularDoubleLinkedList<T, Y>::Iterator::operator -=(const int progress)
{
	Iterator temp(*this);
	temp.advance(-progress);
	swap(temp);
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::Iterator::operator -(const int progress) const
{
	Iterator temp(*this);
	temp.advance(-progress);
	return temp;
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator& CircularDoubleLinkedList<T, Y>::Iterator::operator++()
{
	try
	{
		if (curr == nullptr)
		{
			throw std::out_of_range("The Iterator hasnt been assigend to any Nodes or it just points to end()");
		}
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
		return *this;
	}
	iteratedFrom = curr;
	curr = curr->next;
	return *this;
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::Iterator::operator++(const int)
{
	Iterator temp(*this);
	++(*this);
	return temp;
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator& CircularDoubleLinkedList<T, Y>::Iterator::operator--()
{
	try
	{
		if (curr == nullptr)
		{
			throw std::out_of_range("The operation cannot be accomplished");
		}
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
		return *this;
	}
	iteratedFrom = curr;
	curr = curr->prev;
	return *this;
}
template<typename T, typename Y>
inline typename CircularDoubleLinkedList<T, Y>::Iterator CircularDoubleLinkedList<T, Y>::Iterator::operator--(const int)
{
	Iterator temp(*this);
	--(*this);
	return temp;
}
template<typename T, typename Y>
inline bool CircularDoubleLinkedList<T, Y>::Iterator::operator==(const typename CircularDoubleLinkedList<T, Y>::Iterator&A) const
{
	return this->curr == A.curr;
}
template<typename T, typename Y>
inline const Node<T, Y>*const CircularDoubleLinkedList<T, Y>::Iterator::operator->() const
{
	try
	{
		if (curr == nullptr)
		{
			throw std::out_of_range("The object is nullptr");
		}
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
		exit(1);
	}
	return curr;
}
template<typename T,typename Y>
inline Node<T, Y>* CircularDoubleLinkedList<T, Y>::Iterator::operator->()
{
     return const_cast<Node<T, Y>*>(static_cast<const typename CircularDoubleLinkedList<T, Y>::Iterator&>(*this).operator->());
}
template<typename T, typename Y>
inline const Node<T, Y>& CircularDoubleLinkedList<T, Y>::Iterator::operator*() const
{
	try
	{
		if (curr == nullptr)
		{
			throw std::out_of_range("The object is nullptr");
		}
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
		exit(1);
	}
	return *curr;
}
template<typename T, typename Y>
inline Node<T, Y>& CircularDoubleLinkedList<T, Y>::Iterator::operator*()
{
	return const_cast<Node<T, Y>&>(static_cast<const typename CircularDoubleLinkedList<T, Y>::Iterator&>(*this).operator*());
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::Iterator::swap(typename CircularDoubleLinkedList<T, Y>::Iterator&A)
{
	Node<T, Y>* temp = this->curr;
	this->curr = A.curr;
	A.curr = temp;
}
template<typename T, typename Y>
inline void swap(typename CircularDoubleLinkedList<T, Y>::Iterator&A, typename CircularDoubleLinkedList<T, Y>::Iterator&B)
{
	A.swap(B);
}
template<typename T, typename Y>
inline void CircularDoubleLinkedList<T, Y>::Iterator::advance(const int progress)
{
	Iterator temp(*this);
	try
	{
		if (progress > 0)
		{
			for (int i = 0; i < progress; i++)
			{
				if (temp.curr == nullptr)
				{
					throw std::out_of_range("The operation cannot be accomplished");
				}
				++temp;
			}
		}
		else
		{
			for (int i = progress - 1; i >= 0; i--)
			{
				if (temp.curr == nullptr)
				{
					throw std::out_of_range("The operation cannot be accomplished");
				}
				--temp;
			}
		}
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
		return;
	}
	swap(temp);
}
template<typename T,typename Y>
inline void CircularDoubleLinkedList<T, Y>::ChangeKey(const Y&KEY, const Y&NEWKEY)
{
	if (last->key == NEWKEY)
	{
		std::cout << "Cannot assign the new key" << std::endl;
		return;
	}
	Node<T, Y>* curr = last->next;
	while (curr != last)
	{
		if (curr->key == NEWKEY)
		{
			std::cout << "Cannot assign the new key" << std::endl;
			return;
		}
		curr=curr->next;
	}
	Node<T, Y>* toDel = nullptr;
	curr = last->next;
	while (curr != last)
	{
		if (curr->key == KEY)
		{
			toDel = curr;
			curr=new Node<T, Y>(curr->data, NEWKEY);
			curr->next = toDel->next;
			(toDel->next)->prev = curr;
			(toDel->prev)->next = curr;
			curr->prev = toDel->prev;
			delete toDel;
			return;
		}
		curr = curr->next;
	}
	if (curr->key == KEY)
	{
		toDel = curr;
		curr = new Node<T, Y>(curr->data, NEWKEY);
		curr->next = toDel->next;
		(toDel->next)->prev = curr;
		(toDel->prev)->next = curr;
		curr->prev = toDel->prev;
		last = curr;
		delete toDel;
		return;
	}
	std::cout << "Cannot find a Node with that particular old key" << std::endl;
}
