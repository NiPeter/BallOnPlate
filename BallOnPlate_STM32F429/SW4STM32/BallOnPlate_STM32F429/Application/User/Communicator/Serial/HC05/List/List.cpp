/*
 * List.cpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */



#include "List.hpp"

/**
 * Push a node to the list
 */
/********************************************************/
template <typename T>
void List<T>::Push(T data) {

    // Create a new node
    Node<T>* newNode = (Node<T>*)pvPortMalloc( sizeof(Node<T>) );
    newNode->SetData(data);
    newNode->SetNext(NULL);

    // Create a temp pointer
    Node<T> *tmp = head;

    if ( tmp != NULL ) {
    	// Nodes already present in the list
    	// Parse to end of list
    	while ( tmp->Next() != NULL ) {
    		tmp = tmp->Next();
    	}

    	// Point the last node to the new node
    	tmp->SetNext(newNode);
    }
    else {
    // First node in the list
    head = newNode;
    }
}
/********************************************************/



/**
 * Pop a node from the list
 */
/********************************************************/
template <typename T>
T List<T>::Pop( void ) {

	// Create a temp pointer
	Node<T>* tmp = head;

	// No nodes
	if ( IsEmpty() ) return 0;

	// Last node of the list
	if ( tmp->Next() == NULL ) head = NULL;
		else head = tmp->Next();

	T data = tmp->Data();
	vPortFree(tmp);

	return data;
}
/********************************************************/



/**
 * Get list size
 */
/********************************************************/
template <typename T>
int List<T>::Count( void ){
	Node<T>* tmp = head;
	int cnt = 1;

	// List empty
	if( IsEmpty() ) return 0;


	while(tmp->Next() != NULL){
		tmp = tmp->Next();
		cnt++;
	}
	return cnt;
}
/********************************************************/



/**
 * Returns 1 if list is empty, otherwise returns 0.
 */
/********************************************************/
template <typename T>
bool List<T>::IsEmpty(){
	return (head == NULL);
}
/********************************************************/



/**
 * List Destructor
 */
/********************************************************/
template <typename T>
List<T>::~List(){

	while( !IsEmpty() ) Pop();

}
/********************************************************/



/********************************************************/

template class List<float>;

template class List<int>;

template class List<char>;



