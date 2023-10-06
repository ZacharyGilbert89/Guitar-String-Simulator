// Copyright 2022 Zachary Gilbert
#ifndef CircularBuffer_H //NOLINT
#define CircularBuffer_H //NOLINT
#include <stdint.h>
#include <iostream>
class CircularBuffer {
 public:
    explicit CircularBuffer(int cap);
    int size(); //gets the size
    bool isEmpty(); //sees if the buffer is empty or not
    bool isFull();  //sees if the buffer is full or not
    void enqueue(int16_t x); //function for enqueuing the buffer
    int16_t dequeue(); //function to dequeue the buffer
    int16_t peek(); //function to return the peek 
    int getCapacity(); //function to get the capacity of the buffer
 private:
    int capacity; //variable to keep track of the capacity
    int bufferSize; //variable to keep track of the size of the buffer
    int16_t* _ringBuffer; //Gets the buffer ring
};

#endif //NOLINT
