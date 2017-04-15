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
protected:
	Node<T>* head; 
	Node<T>* tail;
	Node<T>* nil; //added for supporting iterator end() function, nil->prev = tail 
public:
	class iterator
	{
		Node<T>* iter_;
	public:
		iterator(Node<T> *val = nullptr) :iter_(val) {}
		iterator& operator=(Node<T> *val) { iter_ = val; }
		bool operator==(const iter_& b) const;
		bool operator!=(const iter_& b) const;
		void operator++();
		void operator++(int i);
		void operator--();
		void operator--();
		void operator*();
	};
	List();
	List(const List &a);
	List<T>& operator=(const List<T>& a);
	bool isempty();
	int size();
	inline iterator begin() const { return head; }
	inline iterator end() const { return nil; }
	void addNode_tail(T data);
	void addNode_head(T data);
	void showList(ostream&os=cout) const;
	void showList_reverse(ostream&os = cout) const;
	void insertNode_sorted(T key,bool (*pf)(const T&,const T&));
	void insertNode_after(Node<T>* a,T data);
	void insertNode_before(Node<T>* a, T data);
	void deleteNode_head();
	void deleteNode_tail();
	void deleteNode_index(int i);
	void deleteNode_key(T key);
	Node<T>* find(T key);
	iterator& operator[](int i);
	const Node<T>* operator[](int i) const;
	virtual ~List();
	template <typename U>
	friend ostream& operator<<(ostream& os,const List<U>& a);
};
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
void List<T>::insertNode_after(Node<T>* a,T data)
{
	if (a == nil)
		return;
	if (a == tail)
	{
		addNode_tail(data);
		return;
	}
	Node<T>* add = new Node<T>(data,a,a->next);
	a->next->prev = add;
	a->next = add;
}

template<typename T>
void List<T>::insertNode_before(Node<T>* a, T data)
{
	if (a == nil)
		return;
	if (a == head)
	{
		addNode_head(data);
		return;
	}
	insertNode_after(a->prev, data);
}

template<typename T>
void List<T>::deleteNode_head()
{
	if (!head) //head = nullptr - then list is empty
		return;
	Node<T>* t = head;
	if (head == tail) //list has 1 element, so we should change not only head, but also tail
		tail = nil;
	else
		head->next->prev = nil;
	head = head->next;
	delete t;
}

template<typename T>
void List<T>::deleteNode_tail()
{
	if (!head)
		return;
	Node<T>* t = tail;
	if (head == tail)
		head = nil;
	else
		tail->prev->next = nil;
	tail = tail->prev;
	delete t;
}

template<typename T>
void List<T>::deleteNode_index(int i)
{
	if (i < 0)
		return;
	if (i == 0)
		deleteNode_head();
	else
	{
		Node<T> *p = head;
		while (p && (i > 0))
		{
			p = p->next;
			i--;
		}
		if (p == tail)
			deleteNode_tail();
		else
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
		}
	}
}

template<typename T>
void List<T>::deleteNode_key(T key)
{
	if (head->data == key)
		deleteNode_head();
	else if (tail->data == key)
		deleteNode_tail();
	else
	{
		Node<T>* p = head->next;
		while (p->next)
		{
			if (p->data == key)
			{
				//Node<T>* t = p;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete p;
				return;
			}
			p = p-> next;
		}
	}
}

template<typename T>
Node<T>* List<T>::find(T key)
{
	Node<T>* p=head;
	while (p)
	{
		if (p->data == key)
			return p;
		p = p->next;
	}
	return nil;
}

template<typename T>
List<T>::List()
{
	nil = new Node;
	head = tail = nul;
}

template<typename T>
List<T>::List(const List & a):List()
{
	if (!a.head)
		return;
	head = new Node<T>(a.head->data);
	Node<T>* p = a.head->next,*t,*prev;
	prev = head;
	t = head;
	while (p)
	{
		t = new Node<T>(p->data);
		t->prev = prev;
		prev->next = t;
		prev = t;
		p = p->next;
	}
	tail = t;
	t->next = nil;
}

template<typename T>
List<T>& List<T>::operator=(const List<T> & a)
{
	if (this == &a)
		return *this;
	this->~List();
	if (!a.head)
	{
		head = tail = nil;
	}
	else
	{
		head = new Node<T>(a.head->data);
		Node<T>* p = a.head->next, *t, *prev;
		prev = head;
		t = head;
		while (p)
		{
			t = new Node<T>(p->data);
			t->prev = prev;
			prev->next = t;
			prev = t;
			p = p->next;
		}
		tail = t;
		t->next = nil;
	}
	return *this;
}


template<typename T>
inline bool List<T>::isempty()
{
	return head==nil;
}

template<typename T>
inline int List<T>::size()
{
	Node<T>* p = head;
	int count = 0;
	while (p)
	{
		p = p->next;
		++count;
	}
	return count;
}

template<typename T>
void List<T>::addNode_tail(T data)
{
	Node<T>* add = new Node<T>(data);
	if (!head)
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
void List<T>::addNode_head(T data)
{
	Node<T>* add = new Node<T>(data);
	if (!head)
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
void List<T>::showList(ostream& os) const
{
	Node<T>* p = head;
	while (p)
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
	while (p)
	{
		os << p->data << ' ';
		p = p->prev;
	}
	os << endl;
}

template<typename T>
void List<T>::insertNode_sorted(T key,bool (*pf)(const T&,const T&))
{
	if (!head)
	{
		addNode_tail(key);
		return;
	}
	Node<T>*p=head;
	if (pf(key,head->data))
	{
		addNode_head(key);
		return;
	}
	if (pf(tail->data, key))
	{
		addNode_tail(key);
		return;
	}
	while (p)
	{
		if (pf(key,p->data))
		{
			insertNode_after(p->prev, key);
			return;
		}
		p = p->next;
	}
}

template<typename T>
List<T>::iterator& List<T>::operator[](int i)
{
	Node<T>*p = head;
	while (p && (i>0))
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
	while (p && (i>0))
	{
		p = p->next;
		i--;
	}
	return p;
}


template<typename T>
List<T>::~List()
{
	while (head)
	{
		Node<T>* cur = head;
		head = head->next;
		delete cur;
	}
}
