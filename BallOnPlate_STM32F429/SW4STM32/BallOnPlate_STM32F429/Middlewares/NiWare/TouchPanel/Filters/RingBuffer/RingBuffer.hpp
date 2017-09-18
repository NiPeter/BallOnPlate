/*
 * RingBuffer.hpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_TOUCHPANEL_RINGBUFFER_HPP_
#define APPLICATION_USER_TOUCHPANEL_RINGBUFFER_HPP_



template <typename T>
class RingBuffer{
	unsigned int _Size;
	T* _Buffer;

	unsigned int _Head;
	unsigned int _Tail;

	struct{
		bool Empty 	: 1;
		bool Full	: 1;
	} _Status;

public:
	RingBuffer(unsigned int size = 10);
	~RingBuffer();
	void Write(T data);
	T Read(void);
	unsigned int Size(void);

	const T* GetBufferPtr( void ){ return _Buffer;};

	bool IsEmpty(void);
	bool IsFull(void);
private:
	void Inc(unsigned int &i);
	void TailInc(void);
	void HeadInc(void);

};

#endif /* APPLICATION_USER_TOUCHPANEL_RINGBUFFER_HPP_ */
