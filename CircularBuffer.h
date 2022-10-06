// Copyright 2022 Zachary Gilbert
#ifndef CircularBuffer_H //NOLINT
#define CircularBuffer_H //NOLINT
#include <stdint.h>
#include <iostream>
class CircularBuffer {
 public:
    explicit CircularBuffer(int cap);
    int size();
    bool isEmpty();
    bool isFull();
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek();
    int getCapacity();
 private:
    int capacity;
    int bufferSize;
    int16_t* _ringBuffer;
};

#endif //NOLINT