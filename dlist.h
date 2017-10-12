#ifndef DLLIST_H
#define DLLIST_H

#include <iterator>

template <class T>
class DList
{
	struct Node
	{
		Node(const T& x = NULL,Node* y = 0, Node* z=0):data(x),next(y),prev(z){}
		T data;
		Node* next;
		Node* prev;
	};

	Node* head;
public:

	class iterator 
	{
		Node* rep;
	public:
		friend class DList;

		inline iterator(Node* x=0):rep(x){
        }
		inline iterator(const iterator& x):rep(x.rep) {
        }
		inline iterator& operator=(const iterator& x)
		{ 
			rep=x.rep; return *this;
		}
		inline iterator& operator++()
		{ 
			rep = rep->next; return *this;
		}
		inline iterator operator++(int)
		{ 
			iterator tmp(*this); rep = rep->next; return tmp;
		}
		inline T& operator*() const {
            return rep->data; }
		inline Node* operator->() const {
            return rep; }
		inline bool operator==(const iterator& x) const {
			return rep == x.rep;
		}	
		inline bool operator!=(const iterator& x) const {
			return rep != x.rep;
		}	

	};

	DList(){
		head = new Node();
		head->next = head;
		head->prev = head;
	}

	~DList() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	inline void push_front(const T&x)
	{
		Node* tmp = new Node(x);
		tmp->next = head->next;
		tmp->prev = head;
		tmp->next->prev = tmp;
		tmp->prev->next = tmp;
	}
	inline void pop_front()
	{
		if (!empty())
		{
			Node* front = head->next;
			front->next->prev = head;
			front->prev->next = front->next;
			delete front;
		}
	}
	inline bool empty() { return head->next = head; }

	inline T& front() { return *begin(); }
	inline const T& front() const { return *begin(); }

	inline iterator begin() { return iterator(head->next); }
	inline iterator end() { return iterator(head); }

	void insert (iterator& x, const T& y) {
		Node *tmp = new Node(y, x.rep, x.rep->prev);
		Node *p = head->next;
		while (p != head && p->next != x.rep) p = p->next;
		if (p == head) throw std::exception();
		x.rep->prev->next = tmp;
		x.rep->prev = tmp;
	}

	void push_back (const T& y) {
		Node *nd = new Node(y, head, head->prev);
		head->prev->next = nd;
		head->prev = nd;
	}

};

#endif
