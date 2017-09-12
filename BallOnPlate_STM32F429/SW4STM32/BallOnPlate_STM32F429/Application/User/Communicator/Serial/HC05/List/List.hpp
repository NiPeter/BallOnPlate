/*
 * List.hpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_SERIAL_LIST_HPP_
#define APPLICATION_USER_SERIAL_LIST_HPP_



#include "cmsis_os.h"


/***	Declarations	***/

template <typename T> class Node;

template <typename T> class List;

/**************************/



/**
 * LIST CLASS
 */
/********************************************************/
template <typename T>
class List {

private:
	Node<T> *head;

public:
	List() { head = 0; };
	~List();

	void Push(T data);
	T Pop();
	int Count();
	bool IsEmpty();
};
/********************************************************/



/**
 * NODE CLASS
 */
/********************************************************/
template <typename T>
class Node {
	T data;
	Node<T>* next;

public:
	Node() {next = 0;};

	void SetData(T aData) { data = aData; };
	void SetNext(Node* aNext) { next = aNext; };
	T Data() { return data; };
	Node* Next() { return next; };
};
/********************************************************/



#endif /* APPLICATION_USER_SERIAL_LIST_HPP_ */
