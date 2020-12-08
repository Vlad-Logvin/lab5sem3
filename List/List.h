#pragma once
#include <iostream>

using namespace std;

template <typename T>
class List
{
private:
	template <typename T>						//Node of List
	class Node
	{
	public:
		Node* next;								//pointer to next Node
		Node* prev;								//pointer to previous Node
		T value;								//value
		Node(T value = T(), Node* next = nullptr, Node* prev = nullptr)
		{
			this->value = value;
			this->next = next;
			this->prev = prev;
		}
	};

	int size;									//size of List
	Node<T>* tail;								//pointer to tail Node
	Node<T>* head;								//pointer to head Node
public:
	List();
	~List();

	List(const List& list);
	List<T>& operator=(const List& list);

	class Iterator
	{
	private:
		Node<T>* pointer;
	public:
		Iterator(Node<T>* pointer)
		{
			this->pointer = pointer;
		}
		Iterator operator++(int)
		{
			Iterator it = *this;
			pointer = pointer->next;
			return it;
		}
		Iterator operator++()
		{
			pointer = pointer->next;
			return pointer;
		}
		Iterator operator--(int)
		{
			Iterator it = *this;
			pointer = pointer->prev;
			return it;
		}
		Iterator operator--()
		{
			pointer = pointer->prev;
			return pointer;
		}
		Iterator operator+(int index)
		{
			Iterator it = *this; 
			for (int i = 0; i < index; i++)
			{
				it.pointer = it.pointer->next;
			}
			return it;
		}
		T& operator*()
		{
			return pointer->value;
		}
		bool operator==(const Iterator& itr) {
			return pointer == itr.pointer;
		}
		bool operator!=(const Iterator& itr)
		{
			return pointer != itr.pointer;
		}
	};

	Iterator begin() const						//begin pointer
	{
		return Iterator(this->head);
	}
	Iterator end() const						//end pointer
	{
		if (this->tail != nullptr)
		{
			return Iterator(this->tail->next);
		}
		else
		{
			return Iterator(nullptr);
		}
	}

	Iterator rbegin() const						//reverse begin pointer
	{
		if (this->head != nullptr)
		{
			return Iterator(this->head->prev);
		}
		else
		{
			return Iterator(nullptr);
		}
	}
	Iterator rend() const						//reverce end pointer
	{
		return Iterator(this->tail);
	}

	void push_back(T value);					//add to tail
	void push_front(T value);					//add to head
	int getSize();								//return size
	T& operator[](int index);					//get element by index
	T& front();									//adress of head
	T& back();									//adress of tail
	void pop_back();							//delete from tail
	void pop_front();							//delete from head
	void clear();								//clear all list
	bool isEmpty();								//returns whether there are elements in list
	void insert(T value, int index);			//add element by index
	void removeAt(int index);					//delete element by index
	void reverse();								//reverse list
	//ostream& operator<<(ostream& os);			//console output
	//bool operator==(const List<T>& list);		//returns true if two lists has similar size
};


template<typename T>
inline List<T>::List()
{
	this->size = 0;
	this->tail = nullptr;
	this->head = nullptr;
}

template<typename T>
inline List<T>::~List()
{
	clear();
}

template<typename T>
inline List<T>::List(const List& list)
{
	this->tail = nullptr;
	this->head = nullptr;

	this->size = list.size;

	if (list.head != nullptr && list.tail != nullptr)
	{
		Node<T>* tempHead = list.head;

		Node<T>* temp = new Node<T>(tempHead->value, tempHead->next);
		this->head = temp;

		while (tempHead->next)
		{
			tempHead = tempHead->next;
			temp->next = new Node<T>(tempHead->value, nullptr, temp);
			temp = temp->next;
		}
		this->tail = temp;
	}
}

template<typename T>
inline List<T>& List<T>::operator=(const List& list)
{
	if (this->size != 0)
	{
		this->clear();
	}
	this->tail = nullptr;
	this->head = nullptr;

	this->size = list.size;

	if (list.head != nullptr)
	{
		Node<T>* tempHead = list.head;

		Node<T>* temp = new Node<T>(tempHead->value, tempHead->next);
		this->head = temp;

		while (tempHead->next)
		{
			tempHead = tempHead->next;
			temp->next = new Node<T>(tempHead->value, nullptr, temp);
			temp = temp->next;
		}
		this->tail = temp;
	}
	return *this;
}

template<typename T>
inline void List<T>::push_back(T value)
{
	if (this->tail == nullptr)
	{
		this->head = this->tail = new Node<T>(value);
	}
	else
	{
		this->tail = new Node<T>(value, nullptr, this->tail);
		this->tail->prev->next = this->tail;
	}
	this->size++;
}

template<typename T>
inline void List<T>::push_front(T value)
{
	if (this->head == nullptr)
	{
		this->head = this->tail = new Node<T>(value);
	}
	else
	{
		this->head = new Node<T>(value, this->head);
		this->head->next->prev = this->head;
	}
	this->size++;
}

template<typename T>
inline int List<T>::getSize()
{
	return this->size;
}

template<typename T>
inline T& List<T>::operator[](int index)
{
	Node<T>* temp = head;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp->value;
}

template<typename T>
inline T& List<T>::front()
{
	if (this->head != nullptr)
	{
		return this->head->value;
	}
}

template<typename T>
inline T& List<T>::back()
{
	if (this->tail != nullptr)
	{
		return this->tail->value;
	}
}

template<typename T>
inline void List<T>::pop_back()
{
	if (size != 0)
	{
		Node<T>* temp = tail;
		tail = tail->prev;
		if (tail != nullptr)
		{
			tail->next = nullptr;
		}
		delete temp;
		size--;
	}
}

template<typename T>
inline void List<T>::pop_front()
{
	if (size != 0)
	{
		Node<T>* temp = head;
		head = head->next;
		if (head != nullptr)
		{
			head->prev = nullptr;
		}
		delete temp;
		size--;
	}
}

template<typename T>
inline void List<T>::clear()
{
	Node<T>* temp = head;
	for (int i = 0; i < size; i++)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
	tail = nullptr;
	head = nullptr;
	size = 0;
}

template<typename T>
inline bool List<T>::isEmpty()
{
	return (size == 0);
}

template<typename T>
inline void List<T>::insert(T value, int index)
{
	if (index == 0)
	{
		this->push_front(value);
	}
	else if (index == size - 1)
	{
		this->push_back(value);
	}
	else if (index <= size / 2)
	{
		Node<T>* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		temp->next = new Node<T>(value, temp->next, temp);
		temp->next->next->prev = temp->next;
		size++;
	}
	else if (index > size / 2)
	{
		Node<T>* temp = tail;
		for (int i = size - 1; i > index; i--)
		{
			temp = temp->prev;
		}
		temp->prev = new Node<T>(value, temp, temp->prev);
		temp->prev->prev->next = temp->prev;
		size++;
	}
}

template<typename T>
inline void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		this->pop_front();
	}
	else if (index == size - 1)
	{
		this->pop_back();
	}
	else if (index <= size / 2)
	{
		Node<T>* temp = head;
		for (int i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		Node<T>* deleteNode = temp->next;
		temp->next = deleteNode->next;
		deleteNode->next->prev = temp;
		delete deleteNode;
		size--;
	}
	else if (index > size / 2)
	{
		Node<T>* temp = tail;
		for (int i = size - 1; i > index + 1; i--)
		{
			temp = temp->prev;
		}
		Node<T>* deleteNode = temp->prev;
		temp->prev = deleteNode->prev;
		deleteNode->prev->next = temp;
		delete deleteNode;
		size--;
	}
}

template<typename T>
inline void List<T>::reverse()
{
	Node<T>* temp = tail;
	for (int i = 0; i < size; i++)
	{
		Node<T>* temporary = temp->next;
		temp->next = temp->prev;
		temp->prev = temporary;
		temp = temp->next;
	}
	temp = head;
	head = tail;
	tail = temp;
}

//template<typename T>
//inline ostream& List<T>::operator<<(ostream& os)
//{
//	Node<T>* temp = this->head;
//	for (int i = 0; i < this->size; i++)
//	{
//		os << temp->value << " ";
//		temp = temp->next;
//	}
//
//	return os;
//}
//
//template<typename T>
//inline bool List<T>::operator==(const List<T>& list)
//{
//	return (this->size == list.size);
//}

