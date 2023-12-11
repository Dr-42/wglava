#include "ringbuf.h"

RingBuf::RingBuf(unsigned int size){
	this->size = size;
	this->buf = new float[size];
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
