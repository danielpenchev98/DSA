#pragma once
#include <string>
#include <random>
#include <time.h>
#include <vector>
#include <limits>
//#include <math.h>
template<typename T>
struct Vertex;
template<typename T>
struct Edge;
template<typename T>
struct Vertex
{
	Edge<T>* start;
	std::string name;
	T data;
};
template<typename T>
struct Edge
{
   Vertex<T>* to;
   Edge<T>* next;
   int weight;
};
//To CHOOSE TO BE Determined Graph or not IMPORTANT
template<typename T>
class GraphLinkedList
{
private:
	Vertex<T>* vertex;
	unsigned int size;
	unsigned int maxsize;
	void grow();
	void CopyGraph(const GraphLinkedList&);
	void DeleteGraph();
	void CopyLinkedList(Edge<T>*&,const Edge<T>*);
	bool CheckForInComingEdges(const std::string&) const;
public:
	GraphLinkedList(const int = 3);
	GraphLinkedList(const GraphLinkedList&);
	~GraphLinkedList();
	GraphLinkedList& operator=(const GraphLinkedList&);
	void AddVertex(const std::string&, const int = 0);
	void DeleteVertex(const std::string&);
	void AddEdge(const std::string&, const std::string&,const int =0);
	void DeleteEdge(const std::string&, const std::string&);
	void DisplayGraph() const;
	T& GetData(const std::string&);
	const T& GetData(const std::string&) const;
	const Vertex<T>* const GetVertex(const std::string&) const;
	Vertex<T>* GetVertex(const std::string&);
	const Edge<T>* const GetEdge(const std::string&, const std::string&) const;
	Edge<T>* GetEdge(const std::string&, const std::string&);
	int GetWeightOfEdge(const std::string&, const std::string&) const;
	unsigned int DegreeVertex(const std::string&) const;
	unsigned int TotalNumberOfEdges() const;
	bool isCyclic() const;
	//Traversal
	void BreadthFirstSearch(const std::string&) const;
	void DepthFirstSearch(const std::string&) const;
	
	//Algoritms
	int Djiikstra(const std::string&,const std::string&) const;
	
};
template<typename T>
inline void DeleteLinkedList(const Edge<T>* start)
{
	const Edge<T>* temp = nullptr;
	while (start != nullptr)
	{
		temp = start;
		start = start->next;
		delete temp;
	}
}
template<typename T>
inline GraphLinkedList<T>::GraphLinkedList(const int s) :size(0), maxsize(s)
{
	vertex = new Vertex<T>[maxsize];
}
template<typename T>
inline GraphLinkedList<T>::GraphLinkedList(const GraphLinkedList<T>&A)
{
	CopyGraph(A);
}
template<typename T>
inline GraphLinkedList<T>::~GraphLinkedList()
{
	DeleteGraph();
}
template<typename T>
inline GraphLinkedList<T>& GraphLinkedList<T>::operator=(const GraphLinkedList<T>&A)
{
	if (this != &A)
	{
		DeleteGraph();
		CopyGraph(A);
	}
	return *this;
}
template<typename T>
inline void GraphLinkedList<T>::CopyGraph(const GraphLinkedList<T>&A)
{
	if (size == 0)
	{
		vertex = nullptr;
		std::cout << "Error.No vertex at all" << std::endl;
		return;
	}
	size = A.size;
	maxsize = A.maxsize;
	vertex = new Vertex<T>[maxsize];
	for (int i = 0; i < size; i++)
	{
		vertex[i].data = A.vertex[i].data;
		vertex[i].name = A.vertex[i].name;
		vertex[i].start = nullptr;
	}
	for (int i = 0; i < size; i++)
	{
		CopyLinkedList(vertex[i].start, A.vertex[i].start);
	}
}
template<typename T>
inline void GraphLinkedList<T>::CopyLinkedList(Edge<T>*& curr,const Edge<T>* copy)
{
	if (copy == nullptr)
	{
		curr = nullptr;
		return;
	}
	Vertex<T>* temp = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (copy->to->name == vertex[i].name)
		{
			temp = &vertex[i];
		}
	}
	if (temp != nullptr)
	{
		curr = new Edge<T>;
		curr->next = nullptr;
		curr->to = temp;
		curr->weight = copy->weight;
		CopyLinkedList(curr->next, copy->next);
	}
	else
	{
		std::cerr << "Critical error" << std::endl;
		exit(0);
	}
}
template<typename T>
inline void GraphLinkedList<T>::DeleteGraph()
{
	if (vertex == nullptr)
	{
		return;
	}
	Edge<T>* toDel = nullptr;
	for (int i = 0; i < size; i++)
	{
		toDel = vertex[i].start;
		DeleteLinkedList(toDel);
	}
	delete[] vertex;
}
template<typename T>
inline void GraphLinkedList<T>::AddVertex(const std::string& nm, const int data)
{
	for (int i = 0; i < size; i++)
	{
		if (nm == vertex[i].name)
		{
			std::cout << "The vertex already exists" << std::endl;
			return;
		}
	}
	if (size == maxsize - 1)
	{
		grow();
	}
	vertex[size].data = data;
	vertex[size].name = nm;
	vertex[size].start = nullptr;
	size++;
}
//might be a problem
template<typename T>
inline void GraphLinkedList<T>::DeleteVertex(const std::string& nm)
{
	int pos = 0;
	for (; pos < size; pos++)
	{
		if (vertex[pos].name == nm)
		{
			DeleteLinkedList(vertex[pos].start);
			for (int i = 0; i < size - 1; i++)
			{
				if (i == pos)
				{
					continue;
				}
				DeleteEdge(vertex[i].name, vertex[pos].name);
			}
			for (int i = pos; i < size - 1; i++)
			{
				vertex[i] = vertex[i + 1];
			}
			vertex[size - 1].start = nullptr;
			size--;
		}
	}
}
template<typename T>
inline void GraphLinkedList<T>::AddEdge(const std::string& from, const std::string& to, const int wei)
{
	int pos1 = -1;
	int pos2 = -1;
	//if (from == to)
	//{
		//std::cout << "cannot add edge" << std::endl;
		//return;
	//}
	for (int i = 0; i < size; i++)
	{
		if (from == vertex[i].name)
		{
			pos1 = i;
		}
		if (to == vertex[i].name)
		{
			pos2 = i;
		}
	}
	if (pos1 != -1 && pos2 != -1)
	{
		Edge<T>* curr = vertex[pos1].start;
		if (curr == nullptr)
		{
			vertex[pos1].start = new Edge<T>;
			vertex[pos1].start->next = nullptr;
			vertex[pos1].start->weight = wei;
			vertex[pos1].start->to = &vertex[pos2];
			return;
		}
		while (curr->next != nullptr)
		{
			if (curr->next->to == &vertex[pos2])
			{
				std::cerr << "Error, an edge with the same destination point exists" << std::endl;
				return;
			}
			curr = curr->next;
		}
		curr->next = new Edge<T>;
		curr->next->next = nullptr;
		curr->next->to = &vertex[pos2];
		curr->next->weight = wei;
		return;
	}
	std::cout << "The edge cant be added" << std::endl;
}
template<typename T>
inline void GraphLinkedList<T>::DeleteEdge(const std::string&A, const std::string&B)
{
	if (vertex == nullptr /*|| A == B*/)
	{
		return;
	}
	int pos1 = -1;
	int pos2 = -1;
	for (int i = 0; i < size; i++)
	{
		if (A == vertex[i].name)
		{
			pos1 = i;
		}
		/*else*/ if (B == vertex[i].name)
		{
			pos2 = i;
		}
	}
	if (pos1 != -1 && pos2 != -1 && vertex[pos1].start != nullptr)
	{
		Edge<T>* toDel = vertex[pos1].start;
		if (toDel->to == &vertex[pos2])
		{
			vertex[pos1].start = toDel->next;
			delete toDel;
			return;
		}
		while (toDel->next != nullptr)
		{
			if (toDel->next->to == &vertex[pos2])
			{
				Edge<T>* temp = toDel->next;
				toDel->next = toDel->next->next;
				delete temp;
				return;
			}
		}
	}
	std::cout << "The edge hasnt been found" << std::endl;
}
template<typename T>
inline void GraphLinkedList<T>::grow()
{
	Vertex<T>* temp = new Vertex<T>[2 * maxsize];
	for (int i = 0; i < size; i++)
	{
		temp[i].name = vertex[i].name;
		temp[i].data = vertex[i].data;
		temp[i].start = nullptr;
	}
	for (int i = 0; i < size; i++)
	{
		CopyLinkedList(temp[i].start, vertex[i].start);
	}
	DeleteGraph();
	maxsize = 2 * maxsize;
	vertex = temp;
}
template<typename T>
inline void GraphLinkedList<T>::DisplayGraph() const
{
	Edge<T>* curr = nullptr;
	for (int i = 0; i < size; i++)
	{
		std::cout << "Vertex :" << vertex[i].name << " with Value :" << vertex[i].data << " and  Edges :";
		curr = vertex[i].start;
		while (curr != nullptr)
		{
			std::cout << "(" << curr->to->name << " , " << curr->weight << ")" << "  ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}
}
template<typename T>
inline T& GraphLinkedList<T>::GetData(const std::string& nm)
{
	return const_cast<T&>(static_cast<const GraphLinkedList<T>&>(*this).GetData(nm));
} 
template<typename T>
inline const T& GraphLinkedList<T>::GetData(const std::string& nm) const
{
	for (int i = 0; i < size; i++)
	{
		if (vertex[i].name == nm)
		{
			return vertex[i].data;
		}
	}
}
template<typename T>
inline const Vertex<T>* const GraphLinkedList<T>::GetVertex(const std::string& nm) const
{
	for (int i = 0; i < size; i++)
	{
		if (vertex[i].name == nm)
		{
			const Vertex<T>* const temp = &vertex[i];
			return temp;
		}
	}
}
template<typename T>
inline Vertex<T>* GraphLinkedList<T>::GetVertex(const std::string& nm)
{
	return const_cast<Vertex<T>*>(static_cast<const GraphLinkedList<T>&>(*this).GetVertex(nm));
}
template<typename T>
inline const Edge<T>* const GraphLinkedList<T>::GetEdge(const std::string& from, const std::string& to) const
{
	for (int i = 0; i < size; i++)
	{
		if (vertex[i].name == from)
		{
			const Edge<T>* curr = vertex[i].start;
			while (curr != nullptr)
			{
				if (curr->to->name == to)
				{
					return curr;
				}
				curr = curr->next;
			}

		}
	}
	return nullptr;
}
template<typename T>
inline Edge<T>* GraphLinkedList<T>::GetEdge(const std::string& from, const std::string& to)
{
	return const_cast<Edge<T>*>(static_cast<const GraphLinkedList<T>&>(*this).GetEdge(from, to));
}
template<typename T>
inline int GraphLinkedList<T>::GetWeightOfEdge(const std::string& from, const std::string& to) const
{
	return GetEdge(from, to)->weight;
}
template<typename T>
inline void GraphLinkedList<T>::BreadthFirstSearch(const std::string& nm) const
{
	if (size == 0)
	{
		std::cout << "The Graph is empty" << std::endl;
		return;
	}
	const Vertex<T>** ToVisit = new const Vertex<T>*[size];
	for (int i = 0; i < size; i++)
	{
		ToVisit[i] = nullptr;
	}
	const Vertex<T>* temp=nullptr;
	const Edge<T>* curr = nullptr;
	bool flag = 0;
	int front = 0;
	int rear = 0;
	ToVisit[rear] = GetVertex(nm);
	while (front <= rear)
	{
		temp = ToVisit[front++];
		std::cout << temp->name << std::endl;
		curr = temp->start;
		while (curr != nullptr)
		{
			flag = 0;
			for (int i = 0; i < size; i++)
			{
				if (ToVisit[i] == nullptr)
				{
					break;
				}
				else if (ToVisit[i]->name == curr->to->name)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				ToVisit[++rear] = curr->to;
			}
			curr = curr->next;
		}
	}
	delete[] ToVisit;
}
template<typename T>
inline void GraphLinkedList<T>::DepthFirstSearch(const std::string& nm) const
{
	if (size == 0)
	{
		std::cerr << "The graph is empty" << std::endl;
		return;
	}
	const Vertex<T>** ToVisit = new const Vertex<T>*[size];

	for (int i = 0; i < size; i++)
	{
		ToVisit[i] = nullptr;
	}
	bool flag = 0;
	int bottom = 0;
	int top = 0;
	const Vertex<T>* temp = nullptr;
	const Edge<T>* curr = nullptr;
	ToVisit[top] = GetVertex(nm);
	while (bottom<=top)
	{
		temp = ToVisit[top];
		for (int i = bottom; i < top;i++)
		{
			ToVisit[i + 1] = ToVisit[i];
		}
		ToVisit[bottom++] = temp;
		std::cout << temp->name << std::endl;
		curr = temp->start;
		while (curr != nullptr)
		{
			flag = 0;
			for (int i = 0; i < size; i++)
			{
				if (ToVisit[i] == nullptr)
				{
					break;
				}
				if (ToVisit[i]->name == curr->to->name)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				ToVisit[++top] = curr->to;
			}
			curr = curr->next;
		}
	}
	delete[] ToVisit;
}
template<typename T>
inline bool GraphLinkedList<T>::CheckForInComingEdges(const std::string& name) const
{
	Edge<T>* curr = nullptr;
	for (int i = 0; i < size; i++)
	{
		curr = vertex[i].start;
		while (curr != nullptr)
		{
			if (curr->to->name == name)
			{
				return 1;
			}
			curr = curr->next;
		}
	}
	return 0;
}
//topological sort for finding a cycle in a graph
template<typename T>
inline bool GraphLinkedList<T>::isCyclic() const
{
	GraphLinkedList<T> temp(*this);
	Edge<T>* curr = nullptr;
	Vertex<T>* toVertex = nullptr;
	std::vector<Vertex<T>*> L;
	std::vector<Vertex<T>*> Q;
	for (int i = 0; i < size; i++)
	{
		if (!CheckForInComingEdges(vertex[i].name))
		{
			Q.push_back(&vertex[i]);
		}
	}
	while (!Q.empty())
	{
		L.push_back(Q.front());
		Q.erase(Q.begin());
		curr = L.back()->start;
		while (curr != nullptr)
		{
			toVertex = curr->to;
			temp.DeleteEdge(L.back()->name, toVertex->name);
			if (!temp.CheckForInComingEdges(toVertex->name))
			{
				Q.push_back(toVertex);
			}
			curr = curr->next;
		}
	}
	if (temp.TotalNumberOfEdges())
	{
		std::cout << "The graph has a cycle" << std::endl;
		return 1;
	}
	return 0;
}
template<typename T>
inline unsigned int GraphLinkedList<T>::TotalNumberOfEdges() const
{
	unsigned int counter = 0;
	const Edge<T>* curr = nullptr;
	for (int i = 0; i < size; i++)
	{
		curr = vertex[i].start;
		while (curr != nullptr)
		{
			counter++;
			curr = curr->next;
		}
	}
	return counter;
}
template<typename T>
inline unsigned int GraphLinkedList<T>::DegreeVertex(const std::string& nm) const
{
	Edge<T>* curr = GetVertex(nm)->start;
	unsigned int counter = 0;
	while (curr != nullptr)
	{
		counter++;
		curr = curr->next;
	}
	return counter;
}
int CheckWinner(const int*const arr, bool* det,const unsigned int size)
{
	int min = 0;
	for (int i = 0; i < size; i++)
	{
		if (det[i] == 0)
		{
			min = i;
			break;
		}
	}
	for (int j = 0; j < size; j++)
	{
		if (!det[j] && !det[min] && arr[min] > arr[j])
		{
			min = j;
		}
	}
	det[min] = 1;
	return min;
}
template<typename T>
int GraphLinkedList<T>::Djiikstra(const std::string& from, const std::string& to) const
{
	//Preparation for the algorithm
	int start = -1;
	for (int i = 0; i < size; i++)
	{
		if (vertex[i].name == from)
		{
			start = i;
		}
	}
	if (start == -1)
	{
		return -1;
	}
	Edge<T>* curr = vertex[start].start;
	bool* alreadyDeterm = new bool[size];
	for (int i = 0; i < size; i++)
	{
		alreadyDeterm[i] = 0;
	}
	int* table = new int[size];
	for (int i = 0; i < size; i++)
	{
			if (i != start)
			{
				table[i] = std::numeric_limits<int>::max();
			}
			else
			{
				table[i] = 0;
			}
	}
	//The Algorithm starts from here
	for (int i = 0; i < size; i++)
	{
		//Searching for the lightest path
		start = CheckWinner(table, alreadyDeterm,size);
		//Checking if the lightest path leads to the needed vertex
		if (vertex[start].name == to)
		{
			int minWeight = table[start];
			delete[] table;
			delete[] alreadyDeterm;
			return minWeight;
		}
		curr = vertex[start].start;
		while (curr != nullptr)
		{
			for (int j = 0; j < size; j++)
			{
				if (curr->to->name == vertex[j].name)
				{
					table[j] = std::min(table[j], curr->weight + table[start]);
					break;
				}
			}
			curr = curr->next;
		}
	}
	delete[] table;
	delete[] alreadyDeterm;
	return -1;
}
/////////////////// Use for under 64 vertex
/*
//The algorithm uses masks instead of bool array to mark a particular path already determined
bool CheckIfIncluded(unsigned long long det, unsigned int k)
{
	return det & (1 << k) ? 1 : 0;
}
void IncludeEl(unsigned long long& det, unsigned int k)
{ 
	det |= (1 << k);
}
int CheckWinner(const int*const arr, unsigned long long& det, const unsigned int size)
{
	int min = 0;
	for (int i = 0; i < size; i++)
	{
		if (!(CheckIfIncluded(det,i)))
		{
			min = i;
			break;
		}
	}
	for (int j = 0; j < size; j++)
	{
		if (!CheckIfIncluded(det,j) && !CheckIfIncluded(det,min) && arr[min] > arr[j])
		{
			min = j;
		}
	}
	IncludeEl(det, min);
	return min;
}
template<typename T>
int GraphLinkedList<T>::Djiikstra(const std::string& from, const std::string& to) const
{
	//Preparation for the algorithm
	int start = -1;
	for (int i = 0; i < size; i++)
	{
		if (vertex[i].name == from)
		{
			start = i;
		}
	}
	if (start == -1)
	{
		return -1;
	}
	Edge<T>* curr = vertex[start].start;
	unsigned long long alreadyDeterm = 0;
	int* table = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (i != start)
		{
			table[i] = std::numeric_limits<int>::max();
		}
		else
		{
			table[i] = 0;
		}
	}
	//The Algorithm starts from here
	for (int i = 0; i < size; i++)
	{
		//Searching for the lightest path
		start = CheckWinner(table, alreadyDeterm, size);
		std::cout << alreadyDeterm << std::endl;
		//Checking if the lightest path leads to the needed vertex
		if (vertex[start].name == to)
		{
			int minWeight = table[start];
			delete[] table;
			return minWeight;
		}
		curr = vertex[start].start;
		while (curr != nullptr)
		{
			for (int j = 0; j < size; j++)
			{
				if (curr->to->name == vertex[j].name)
				{
					table[j] = std::min(table[j], curr->weight + table[start]);
					break;
				}
			}
			curr = curr->next;
		}
	}
	delete[] table;
	return -1;
}
*/
