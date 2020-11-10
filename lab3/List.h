#pragma once
#include"Iterator.h"
#include <fstream>
#include<iostream>
//#include"Refernces.h"

using namespace std;
template <class T>
class List {

	struct ListNode {
		T data;
		ListNode* next;
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List() {
		head = NULL;
		last = new iterator(head);
		first = new iterator(head);
	};
	~List() {
		while (head != NULL) {
			ListNode* tmp = head->next;
			delete[] head;
			head = tmp;
		}
	};
	
	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element


	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type& val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(const node_type val); //Adds an element to the beginning of a list.
  
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.


	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void	Print();//Dumps list into the screen
	void load(const char* filename);
	typename List<T>::node_type parseFrom(char* str);
private:
	node_type* head;
	iterator* first, * last;
};

template<class T>
typename List<T>::iterator List<T>::begin() {
	return *first;
}

template<class T>
typename List<T>::iterator List<T>::end() {

	return *last;
}
template<class T>
void List<T>::clear()
{
	while (head != NULL) {
		ListNode* tmp = head->next;
		delete[] head;
		head = tmp;
		first = new iterator(head);
		last = new iterator(head);
	}
}

template<class T>
inline bool List<T>::empty()
{ 
	if (head == NULL)
		return true;
	return false;
}

template<class T>
typename List<T>:: iterator List<T>::find(const node_type& val)
{
	if (head != NULL) {
		ListNode* tmp = head;
		while (tmp != NULL) {
			if (tmp->data == val.data)
				return  iterator(tmp);
			tmp = tmp->next;
		}
	}
	else {
		return *first;
	}
}

template<class T>
void List<T>::pop_front()
{
	if (head != NULL) {
		ListNode* tmp = head->next;
		delete[] head;
		head = tmp;
		first = new iterator(head);
	}
}

template<class T>
void List<T>::push_front(const node_type val)
{
	if (head != NULL) {
		ListNode* tmp = new ListNode;
		tmp->next = head;
		tmp->data = val.data;
		head = tmp;
		first = new iterator(head);
	}
	else {
		ListNode* tmp = new ListNode;
		tmp->next = NULL;
		tmp->data = val.data;
		head = tmp;
		first = new iterator(head);
		last = new iterator(head->next);

	}
}
template<class T>
inline int List<T>::size()
{
	int  count = 0;
	if (head != NULL) {
		ListNode* tmp = head;
		while (tmp != NULL) {
			count++;
			tmp = tmp -> next;
		}
	}
	return count;
}

template<class T>
inline void List<T>::splice(iterator _Where, List<T>& _Right)
{
	if (_Where == NULL) {
		return;
	}
	else {
		ListNode tmp = (*_Where).data;
		this->remove((*_Where).data);
		_Right.push_front(tmp);
	}
}

template<class T>
inline void List<T>::Print()
{
	ListNode *tmp = head;
	while (tmp != NULL) {
		tmp->Print();
		printf("\n");
		tmp = tmp -> next;
	}
}

template<class T>
void List<T>::load(const char* filename)
{

	ifstream file;
	file.open(filename);
	char str[55];
	while (!file.eof()) {
		file.getline(str, 55);
		//file >> str;
		//cout << str;
		
		push_front(parseFrom(str));
 	}
}

template <class T>
typename List<T>::node_type List<T>::parseFrom(char* str) {
	T element; 
	element.parseFrom(str);
	return element;
}


template<class T>
void List<T>::remove(const node_type val)
{
	int count = this->size(), chack = -1;
	if (count != 0) {
		ListNode* q = head;
		if (q->data == val.data) {
			this->pop_front();
		}
		else {
			int delli = 0;
			ListNode* tmp = head, * dell = head, * mem = head;
			q = head;
			while (q != NULL) {
				delli++;
				if (q->data == val.data) {
					tmp = q->next;
					dell = q;
					break;
				}
				q = q->next;
			}
			int z = 0;
			while (mem != NULL)
			{
				z++;
				if (z == delli - 1) {
					mem->next = tmp;
					//delete[] dell;
					return;
				}
				mem = mem->next;
			}
		}
	}
}


