#pragma once

#include <complex>

class RingBuf {
public:
    RingBuf(unsigned int size);
    ~RingBuf();
    void Push(float val);
    void Cat(float* vals, int num);
    float Get(int index);
    unsigned int GetSize();
    unsigned int GetIndex();
    float operator[](int index);
    void fft_analyze(float dt);
    float get_fft(int index);
	size_t fft_size;
private:
    float* buf;
    std::complex<float>* fft_buf;
    unsigned int size;
    int index;
    void fft(float in[], size_t stride, std::complex<float> out[], size_t n);
};

