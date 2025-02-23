#pragma once
#include "iostream"

template <typename TELEM>
class List {
protected:
	struct Node {
		bool isHeadNode = false;
		Node* next = nullptr;
		Node* prev = nullptr;
		TELEM value;
		Node() {};
		Node(const TELEM& val) : value(val) {};
	};
	Node* headNode = nullptr;
	// headNode stores no value 
	int size = 0;

public:

	/* --- Iterator --- */
	class Iterator {
	public:
		Node* curr = nullptr;
		Iterator(Node* nd) : curr(nd) {};

		Iterator createIterator(Node* nd) {
			return Iterator(nd);
		}

		Iterator& operator++() {
			curr = curr->next;
			return *this;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			curr = curr->next;
			return tmp;
		}
		Iterator& operator--() {
			curr = curr->prev;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			curr = curr->prev;
			return tmp;
		}

		Iterator operator+(int step) {
			Iterator res = *this;
			// If step < 0, we should go back, even if this is addition actually 
			if (step > 0) {
				for (int i = 0; i < step; i++) {
					res++;
				}
			}
			else {
				for (int i = 0; i < step; i++) {
					res--;
				}
			}
			return res;
		}
		Iterator operator-(int step) {
			Iterator res = *this + (step * -1);
			return res;
		}

		Iterator& operator+=(int step) {
			*this = *this + step;
			return *this;
		}
		Iterator& operator-=(int step) {
			*this = *this - step;
			return *this;
		}

		bool operator==(const Iterator& it) const {
			return curr == it.curr;
		}
		bool operator!=(const Iterator& it) const {
			return curr != it.curr;
		}

		TELEM* operator->() const {
			//if (curr->isHeadNode) throw std::runtime_error("Head node stores no value");
			return &(curr->value);
		}
		TELEM& operator*() const {
			//if (curr->isHeadNode) throw std::runtime_error("Head node stores no value");
			return curr->value;
		}
	};

	List() {
		headNode = new Node;
		headNode->isHeadNode = true;

		headNode->next = headNode;
		headNode->prev = headNode;

		size = 0;
	}
	List(int sz) {
		if (sz < 0) throw std::runtime_error("Size cannot be <0");

		headNode = new Node;
		headNode->isHeadNode = true;

		headNode->next = headNode;
		headNode->prev = headNode;

		size = 0;

		for (int i = 0; i < sz; i++) {
			insert_back(0);
		}
	}
	List(const List& l) {
		headNode = new Node;
		headNode->isHeadNode = true;

		headNode->next = headNode;
		headNode->prev = headNode;

		size = 0;

		for (int i = 0; i < l.size; i++) {
			insert_back(l[i]);
		}

	}
	~List() {
		clear();
	}
	List& operator=(const List& l) {
		if (*this != l) {
			clear();
			headNode = new Node;
			headNode->isHeadNode = true;

			headNode->next = headNode;
			headNode->prev = headNode;

			size = 0;

			for (int i = 0; i < l.size; i++) {
				insert_back(l[i]);
			}
		}

		return *this;
	}

private:
	/* --- Making other methods easier --- */
	Iterator addNode(Node* pNode, Node* nNode, const TELEM& value) {
		Node* nd = new Node(value);

		nd->next = nNode;
		nd->prev = pNode;
		nNode->prev = nd;
		pNode->next = nd;

		size++;

		return Iterator(nd);
	}
	Iterator delNode(Node* nd) {
		if (nd->isHeadNode) throw std::runtime_error("Cannot delete head node");

		Node* tmp = nd->next;
		tmp->prev = nd->prev;
		(tmp->prev)->next = tmp;

		delete nd;
		size--;
		
		return Iterator(tmp);
	}
	void clear() {
		Node* curr = headNode->next;
		while (curr != headNode) {
			Node* tmp = curr;
			curr = curr->next;
			delete tmp;
		}
		headNode->next = headNode;
		headNode->prev = headNode;
		size = 0;
	}

public:


	Iterator begin() const {
		return Iterator(headNode->next);
	}
	Iterator end() const {
		return Iterator(headNode);
	}

	/* --- Adding elements --- */
	Iterator insert_after(const TELEM& value, Iterator pNode) {
		return addNode(pNode.curr, pNode.curr->next, value);
	}
	Iterator insert_before(const TELEM& value, Iterator nNode) {
		return addNode(nNode.curr->prev, nNode.curr, value);
	}
	Iterator insert_front(const TELEM& value) {
		return insert_after(value, Iterator(headNode));
	}
	Iterator insert_back(const TELEM& value) {
		return insert_before(value, Iterator(headNode));
	}

	/* --- Deleting elements --- */
	Iterator delete_node(Iterator nd) {
		return delNode(nd.curr);
	}
	Iterator delete_front() {
		return(delete_node(Iterator(headNode->next)));
	}
	Iterator delete_back() {
		return(delete_node(Iterator(headNode->prev)));
	}

	/* --- Other --- */
	bool isEmpty() const {
		return size == 0;
	}
	int getSize() const {
		return size;
	}
	TELEM& operator[](int i) const {
		if (i < 0 || i >= size) throw std::runtime_error("Index out of range");

		return *(begin() + i);
	}
};