#include "ringbuf.h"

RingBuf::RingBuf(unsigned int size){
	this->size = size;
	this->buf = new float[size];
	// Set all values to 0
	for(unsigned int i = 0; i < size; i++){
		this->buf[i] = 0;
	}
	this->index = 0;
}

RingBuf::~RingBuf(){
	delete[] this->buf;
}

void RingBuf::Push(float val){
	this->buf[this->index] = val;
	this->index = (this->index + 1) % this->size;
}

void RingBuf::Cat(float* vals, int num){
	for(int i = 0; i < num; i++){
		this->Push(vals[i]);
	}
}

float RingBuf::Get(int index){
	return this->buf[(this->index + index) % this->size];
}

unsigned int RingBuf::GetSize(){
	return this->size;
}

unsigned int RingBuf::GetIndex(){
	return this->index;
}

float RingBuf::operator [](int index){
	return this->Get(index);
}
