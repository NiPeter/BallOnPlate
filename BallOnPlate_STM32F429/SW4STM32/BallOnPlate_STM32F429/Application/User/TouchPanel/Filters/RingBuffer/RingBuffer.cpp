/*
 * RingBuffer.cpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#include "RingBuffer.hpp"

template <typename T>
RingBuffer<T>::RingBuffer(unsigned int size):_Size(size){
	_Buffer = new T[_Size];
	_Head = 0;
	_Tail = 0;

	_Status.Empty = true;
	_Status.Full = false;
}

template <typename T>
RingBuffer<T>::~RingBuffer(){
	delete[] _Buffer;
}

template <typename T>
void RingBuffer<T>::Write(T data){

	_Buffer[_Tail] = data; // Wpisz do bufora
	Inc(_Tail);	// Inkrementuj ogon

	if( IsEmpty() ) _Status.Empty = false; // Je�eli by� pusty to ju� nie b�dzie

	if( IsFull() ) {
		Inc(_Head);	// Je�eli by� pe�ny to przesuwamy g�ow�
		return;	// i mo�emy pomin�c kolejny krok...
	}

	// Je�eli bufor nie by� pe�ny wcze�niej i
	if(_Tail == _Head) _Status.Full = true; // ... je�eli ogon i g�owa to to samo to bufor pe�ny

}

template <typename T>
T RingBuffer<T>::Read(void){
	if(IsEmpty()) return 0; // Jak pusty to zwracamy 0

	T data = _Buffer[_Head]; // Zapisz co wskazuje g�owa
	Inc(_Head);

	if( IsFull() ) _Status.Full = false; // Je�eli by� pe�ny to ju� nie jest
	if( _Head == _Tail ) _Status.Empty = true; // Je�eli wskazuj� to samo to bufor jest pusty

	return data;
}

template <typename T>
void RingBuffer<T>::Inc(unsigned int &i){
	unsigned int tmp = i;

	tmp++;
	i = (tmp>=_Size) ? 0 : tmp;

}

template <typename T>
bool RingBuffer<T>::IsEmpty(void){
	return _Status.Empty;
}

template <typename T>
bool RingBuffer<T>::IsFull(void){
	return _Status.Full;
}

template <typename T>
unsigned int  RingBuffer<T>::Size(void){
	return _Size;
}


template class RingBuffer<float>;


