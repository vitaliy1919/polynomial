#pragma once
#include "stdafx.h"

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
	Node(T d = 0, Node* pr = nullptr, Node* nx = nullptr) :data(d), prev(pr), next(nx) {}
};

template <typename T>
class List
{
protected:
	Node<T>* head;
	Node<T>* tail;
public:
	List() :head(nullptr), tail(nullptr) {}
	List(const List &a);
	List<T>& operator=(const List<T>& a);
	bool isempty();
	int size();
	void addNode_tail(T data);
	void addNode_head(T data);
	void showList(ostream&os=cout) const;
	void showList_reverse(ostream&os = cout) const;
	void insertNode_sorted(T key,bool (*pf)(const T&,const T&));
	void insertNode_after(Node<T>* a,T data);
	void insertNode_before(Node<T>* a, T data);
	void deleteNode_head();
	void deleteNode_tail();
	void deleteNode_key(T key);
	Node<T>* find(T key);
	Node<T>*& operator[](int i);
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
	if (a == nullptr)
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
	if (a == nullptr)
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
	if (!head)
		return;
	Node<T>* t = head;
	if (head == tail)
		tail = nullptr;
	else
		head->next->prev = nullptr;
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
		head = nullptr;
	else
		tail->prev->next = nullptr;
	tail = tail->prev;
	delete t;
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
				Node<T>* t = p;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				delete t;
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
	return nullptr;
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
	t->next = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List<T> & a)
{
	if (this == &a)
		return *this;
	this->~List();
	if (!a.head)
	{
		head = tail = nullptr;
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
		t->next = nullptr;
	}
	return *this;
}


template<typename T>
inline bool List<T>::isempty()
{
	return head==nullptr;
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
Node<T>*& List<T>::operator[](int i)
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
