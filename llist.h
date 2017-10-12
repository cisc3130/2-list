#ifndef LLIST_H
#define LLIST_H

#include <iterator>

template <class T>
class List
{
	struct Node
	{
		Node(const T& x,Node* y = 0):m_data(x),m_next(y){}
		T data;
		Node* next;
	};

	Node* head;
public:

	class iterator 
	{
		Node* rep;
	public:
		friend class List;

		inline iterator(Node* x=0):rep(x){
        }
		inline iterator(const iterator& x):rep(x.rep) {
        }
		inline iterator& operator=(const iterator& x) {
			rep=x.rep; return *this;
		}
		inline iterator& operator++() {
			rep = rep->next; return *this;
		}
		inline iterator operator++(int) {
			iterator tmp(*this); rep = rep->mnext; return tmp;
		}
		inline T& operator*() const {
            return rep->data; }
		inline Node* operator->() const {
            return rep; }
		inline bool operator==(const iterator& x) const
		{
			return rep == x.rep;
		}	
		inline bool operator!=(const iterator& x) const
		{
			return rep != x.rep;
		}	

	};


	~List() { clear(); }
	void clear() { while (!empty()) pop_front(); }

	inline void push_front(const T&x)
	{
		Node* tmp = new Node(x);
		tmp->next = head;
		head = tmp;
	}
	inline void pop_front()
	{
		if (head)
		{
			Node* newhead = head->next;
			delete head;
			head = newhead;
		}
	}
	inline bool empty() {
        return head; }

	inline T& front() {
        return *begin(); }
	inline const T& front() const {
        return *begin(); }

	inline iterator begin() {
        return iterator(head); }
	inline iterator end() {
        return iterator(); }

	void insert (iterator& x, const T& y) {
		Node *tmp = new Node(y, x.rep);
		if (x.rep==head) head = tmp;
		else { 
			Node *p = head;
			while (p && p->next != x.rep) p = p->next;
			if (!p) throw std::exception();
			p->next = tmp;
		}
	}

	void push_back (const T& y) {
		Node *nd = new Node(y, NULL);
		if (!head) head = nd;
            else {
                Node *p = head;
                    while (p->next) p = p->next;
                p->next = nd;
            }
        }

};

#endif
