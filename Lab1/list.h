#pragma once
#include <iostream>
using namespace std;

template <typename T>
bool bigger(const T& a,const T& b)
{
	return a > b;
}
template <typename T>
bool smaller(const T& a,const T& b)
{
	return a < b;
}
template <typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;
	Node(const T& d = 0, Node* pr = nullptr, Node* nx = nullptr) :data(d), prev(pr), next(nx) {}
};

template <typename T>
class List
{
private:
	Node<T>* head; 
	Node<T>* tail;
	Node<T>* nil; //added for supporting iterator end() function, nil->prev = tail 
	void deleteList(Node<T>* start_node);
	void copyList(const Node<T>* source);
public:
	class iterator
	{
		Node<T>* iter_;
	public:
		iterator(Node<T> *val = nullptr) :iter_(val) {}
		iterator& operator=(Node<T> *val) { iter_ = val; return *this; }
		bool operator==(const iterator& b) const;
		bool operator!=(const iterator&  b) const;
		void operator++();
		void operator++(int i);
		void operator--();
		void operator--(int i);
		void operator*();
	};
	List();
	List(const List &a);
	List<T>& operator=(const List<T>& a);
	bool empty() const { return head == nil; }
	int size() const;
	inline iterator begin() const { return head; }
	inline iterator end() const { return nil; }
	void addNodeTail(T data);
	void addNodeHead(T data);
	void deleteNodeHead();
	void deleteNodeTail();
	void deleteNodeIndex(int i);
	void deleteNodeKey(T key);
	void insertNodeSorted(T key,bool (*pf)(const T&,const T&));
	void insertNodeAfter(Node<T>* a,T data);
	void insertNodeBefore(Node<T>* a, T data);
	void showList(ostream&os=cout) const;
	void showList_reverse(ostream&os = cout) const;
	iterator find(T key) const;
	iterator& operator[](int i);
	const Node<T>* operator[](int i) const;
	virtual ~List();
	template <typename U>
	friend ostream& operator<<(ostream& os,const List<U>& a);
};

template<typename T>
void List<T>::deleteList(Node<T>* start_node)
{
	while (start_node != nil)
	{
		Node<T>* node_to_delete = head;
		start_node = start_nodes->next;
		delete node_to_delete;
	}
}

template<typename T>
void List<T>::copyList(const Node<T>* source)
{
	if (source == nil)
		head = tail = nil;
	else
	{
		Node<T>* new_node = new Node(source->data);
		head = new_node;
		Node<T>* prev_node = head, *iter = source->next; //prev note is used to fill next and prev fields
		while (iter != nil)
		{
			new_node = new Node(iter->data); //copy data
			prev_node->next = new_node; //fill next and prev fields
			new_node->prev = prev_node;
			prev_node = new_node; //move prev node
			iter = iter->next;
		}
		prev_node->next = nil; //fill last element
		tail = prev_node; //fill tail
		nil->prev = tail;
	}
}

template<typename T>
List<T>::List()
{
	nil = new Node;
	head = tail = nil;
}

template<typename T>
List<T>::List(const List & a):List()
{
	copyList(a.head);
}

template<typename T>
List<T>& List<T>::operator=(const List<T> & a)
{
	if (this == &a)
		return *this;
	deleteList(head);
	copyList(a.head);
	return *this;
}

template<typename T>
inline int List<T>::size() const
{
	Node<T>* p = head;
	int count = 0;
	while (p != nil)
	{
		p = p->next;
		++count;
	}
	return count;
}

template<typename T>
void List<T>::addNodeTail(T data)
{
	Node<T>* add = new Node<T>(data);
	if (head == nil)
	{
		head = add;
		tail = head;
		return;
	}
	tail->next = add;
	add->prev = tail;
	tail = add;
}

template<typename T>
void List<T>::addNodeHead(T data)
{
	Node<T>* add = new Node<T>(data);
	if (head == nil)
	{
		head = add;
		tail = head;
		return;
	}
	add->next = head;
	head->prev = add;
	head = add;
}

template<typename T>
void List<T>::deleteNodeHead()
{
	if (!head) //head = nullptr - then list is empty
		return;
	Node<T>* t = head; //remember position of head (for deleting it later)
	if (head == tail) //list has 1 element, so we should change not only head, but also tail
	{
		tail = nil;
		nil->prev = nil;
	}
	else
		head->next->prev = nil; //
	head = head->next;
	delete t;
}

template<typename T>
void List<T>::deleteNodeTail()
{
	if (!head)
		return;
	Node<T>* t = tail;
	if (head == tail)
		head = nil;
	else
		tail->prev->next = nil;
	tail = tail->prev;
	nil->prev = tail;
	delete t;
}

template<typename T>
void List<T>::deleteNodeIndex(int i)
{
	if (i < 0)
		return;
	if (i == 0)
		deleteNodeHead();
	else
	{
		Node<T> *p = head;
		while (p != nil && (i > 0))
		{
			p = p->next;
			i--;
		}
		if (p == tail)
			deleteNodeTail();
		else
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
		}
	}
}

template<typename T>
void List<T>::deleteNodeKey(T key)
{
	if (head->data == key)
		deleteNodeHead();
	else if (tail->data == key)
		deleteNodeTail();
	else
	{
		Node<T>* p = head->next;
		while (p->next != nil)
		{
			if (p->data == key)
			{
				//Node<T>* t = p;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete p;
				return;
			}
			p = p->next;
		}
	}
}

template <typename U>
ostream & operator<<(ostream& os, const List<U>& a)
{
	Node<U>* p = a.head;
	while (p)
	{
		os << p->data << ' ';
		p = p->next;
	}
	return os;
}

template<typename T>
void List<T>::insertNodeAfter(Node<T>* a,T data)
{
	if (a == nil)
		return;
	if (a == tail)
	{
		addNodeTail(data);
		return;
	}
	Node<T>* add = new Node<T>(data,a,a->next);
	a->next->prev = add;
	a->next = add;
}

template<typename T>
void List<T>::insertNodeBefore(Node<T>* a, T data)
{
	if (a == nil)
		return;
	if (a == head)
	{
		addNodeHead(data);
		return;
	}
	insertNodeAfter(a->prev, data);
}

template<typename T>
void List<T>::insertNodeSorted(T key, bool(*pf)(const T&, const T&))
{
	if (head == nil)
	{
		addNodeTail(key);
		return;
	}
	Node<T>*p = head;
	if (pf(key, head->data))
	{
		addNodeHead(key);
		return;
	}
	if (pf(tail->data, key))
	{
		addNodeTail(key);
		return;
	}
	while (p != nil)
	{
		if (pf(key, p->data))
		{
			insertNodeAfter(p->prev, key);
			return;
		}
		p = p->next;
	}
}

template<typename T>
void List<T>::showList(ostream& os) const
{
	Node<T>* p = head;
	while (p != nil)
	{
		os << p->data << ' ';
		p = p->next;
	}
	os << endl;
}

template<typename T>
void List<T>::showList_reverse(ostream& os) const
{
	Node<T> *p = tail;
	while (p != nil)
	{
		os << p->data << ' ';
		p = p->prev;
	}
	os << endl;
}

template<typename T>
typename List<T>::iterator List<T>::find(T key) const
{
	Node<T>* p=head;
	while (p != nil)
	{
		if (p->data == key)
			return p;
		p = p->next;
	}
	return nil;
}

template<typename T>
typename List<T>::iterator& List<T>::operator[](int i)
{
	Node<T>*p = head;
	while (p!=nil && (i>0))
	{
		p = p->next;
		i--;
	}
	return p;
}

template<typename T>
const Node<T>* List<T>::operator[](int i) const
{
	Node<T>*p = head;
	while (p!=nil && (i>0))
	{
		p = p->next;
		i--;
	}
	return p;
}

template<typename T>
List<T>::~List()
{
	deleteList(head);
	delete nil;
}
