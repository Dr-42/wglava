#pragma once

class RingBuf{
public:
	RingBuf(unsigned int size);
	~RingBuf();
	void Push(float val);
	void Cat(float* vals, int num);
	float Get(int index);
	unsigned int GetSize();
	unsigned int GetIndex();
private:
	float* buf;
	unsigned int size;
	int index;
};
