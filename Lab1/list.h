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
	Node<T>* nil; //added for supporting iterator end() function, nil->prev == tail  and if list not empty tail->next == nil head->prev == nil
				  //also if list is empty tail and head are nil, nil->prev == nil
	void deleteList(Node<T>* start_node);
	void copyList(const Node<T>* source);
	void deleteNode(const Node<T> *node_to_delete);
public:
	class iterator
	{
		Node<T>* iter_;
	public:
		iterator(Node<T> *val = nullptr) :iter_(val) {}
		iterator& operator=(Node<T> *val) { iter_ = val; return *this; }
		void setNode(const Node<T>* val) { iter_ = val; }
		Node<T>* getNode() const { return iter_; }
		bool operator==(const iterator& b) const;
		bool operator!=(const iterator&  b) const;
		void operator++();
		void operator++(int i);
		void operator--();
		void operator--(int i);
		iterator operator+(int i) const;
		iterator operator-(int i) const;
		void operator*();
	};
	List();
	List(const List &a) { copyList(a.head); }
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
	void deleteNode(const iterator& iter) { deleteNode(iter.getNode()); }
	void insertNodeSorted(T key,bool (*pf)(const T&,const T&));
	void insertNodeAfter(const iterator& a,T data);
	void insertNodeBefore(const iterator& a, T data);
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
void List<T>::deleteNode(const Node<T>* node_to_delete)
{
	if (node_to_delete == head)
		deleteNodeHead();
	else if (node_to_delete == tail)
		deleteNodeTail();
	else
	{
		node_to_delete->prev->next = node_to_delete->next;
		node_to_delete->next->prev = node_to_delete->prev;
		delete node_to_delete;
	}
}

template<typename T>
List<T>::List()
{
	nil = new Node<T>;
	nil->prev = nil;
	head = tail = nil;
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
	if (head == nil) //if list is empty we shoud change head also
	{
		head = add;
		tail = head;
	}
	else
	{
		tail->next = add;
		add->prev = tail;
		tail = add;
	}
	nil->prev = tail;
}

template<typename T>
void List<T>::addNodeHead(T data)
{
	Node<T>* add = new Node<T>(data);
	if (head == nil) //if list is empty we shoud change tail also
	{
		head = add;
		tail = head;
		nil->prev = tail; //for the sake of iterators end() and -- function
	}
	else
	{
		add->next = head;
		head->prev = add;
		head = add;
	}
}

template<typename T>
void List<T>::deleteNodeHead()
{
	if (head==nil) //head = nil - then list is empty
		return;
	Node<T>* t = head; //remember position of head (for deleting it later)
	if (head == tail) //list has 1 element, so we should change not only head, but also tail
	{
		head = tail = nil;
		nil->prev = nil;
	}
	else
	{
		head->next->prev = nil; //otherwise move head and change links
		head = head->next;
	}
	delete t;
}

template<typename T>
void List<T>::deleteNodeTail()
{
	if (head==nil)
		return;
	Node<T>* t = tail;
	if (head == tail)
		head = tail = nil;
	else
	{
		tail->prev->next = nil;
		tail = tail->prev;
	}
	nil->prev = tail;
	delete t;
}

template<typename T>
void List<T>::deleteNodeIndex(int i)
{
	Node<T>* node_to_delete = operator[i].getNode();
	deleteNode(node_to_delete);
}

template<typename T>
void List<T>::deleteNodeKey(T key)
{
	Node<T>* node_to_delete = find(key).getNode();
	deleteNode(node_to_delete);
}

template<typename T>
void List<T>::insertNodeAfter(const iterator& a, T data)
{
	Node<T>* node_from_iter = a.getNode();
	if (node_from_iter == nil)
		return;
	if (node_from_iter == tail)
	{
		addNodeTail(data);
		return;
	}
	Node<T>* add = new Node<T>(data, node_from_iter, node_from_iter->next);
	node_from_iter->next->prev = add;
	node_from_iter->next = add;
}

template<typename T>
void List<T>::insertNodeBefore(const iterator& a, T data)
{
	Node<T>* node_from_iter = a.getNode();
	if (node_from_iter == nil)
		return;
	if (node_from_iter == head)
	{
		addNodeHead(data);
		return;
	}
	insertNodeAfter(node_from_iter->prev, data);
}

template<typename T>
void List<T>::insertNodeSorted(T key, bool(*pf)(const T&, const T&)) //pf should return true if argument are in right order
{
	if (head == nil)
	{
		addNodeTail(key);
		return;
	}
	Node<T>* iter = head;
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
	while (iter != nil)
	{
		if (pf(key, iter->data))
		{
			insertNodeAfter(iter->prev, key);
			return;
		}
		iter = iter->next;
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
	Node<T>* p = head;
	while (p!=nil && (i>0))
	{
		p = p->next;
		i--;
	}
	return iterator(p);
}

template<typename T>
const typename List<T>::iterator List<T>::operator[](int i) const
{
	Node<T>*p = head;
	while (p!=nil && (i>0))
	{
		p = p->next;
		i--;
	}
	return iterator(p);
}

template<typename T>
List<T>::~List()
{
	deleteList(head);
	delete nil;
}
