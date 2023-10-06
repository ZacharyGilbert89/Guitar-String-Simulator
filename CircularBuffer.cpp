// Copyright 2022 Zachary Gilbert
#include "CircularBuffer.h"
#include <stdint.h>
#include <iostream>
#include <exception>
CircularBuffer::CircularBuffer(int cap) {
    if (cap < 1) { //checks to see if the capiacty is atleast initialized
        throw std::invalid_argument("CircularBuffer constructor: "
        "capacity must be greater than zero.");
    }
    capacity = cap; //sets the capicity based off the parameters
    bufferSize = 0;
    _ringBuffer = new int16_t[cap];
}
int CircularBuffer::getCapacity() {
    return capacity; //gets the capacity
}
int CircularBuffer::size() {
    return bufferSize; //gets the buffersize
}
bool CircularBuffer::isEmpty() { //check to see if the buffer is empty
    if (bufferSize == 0) {
        return true;
    } else {
        return false;
    }
}
bool CircularBuffer::isFull() { //checks to see if the buffer is full
    if (bufferSize == capacity) {
        return true;
    } else {
        return false;
    }
}
void CircularBuffer::enqueue(int16_t x) {
    if (bufferSize == capacity) { //if the buffer is already full, we cannot proceed
        throw std::runtime_error("enqueue: can't enqueue to a full ring");
    } else { //else increase the buffer size as we enqueue
        bufferSize++;
        _ringBuffer[bufferSize - 1] = x;
    }
}
int16_t CircularBuffer::dequeue() {
    if (bufferSize == 0) { //checks to see if the buffer is already empty
        throw std::runtime_error("dequeue: can't dequeue an empty ring");
    } else {              //else we start clearing the buffer
        int16_t temp;
        temp = _ringBuffer[0];
        for (int i = 0; i < bufferSize; i++) {
        _ringBuffer[i] = _ringBuffer[i + 1];
        }
        bufferSize--;
        return temp;
    }
}
int16_t CircularBuffer::peek() {
    if (bufferSize == 0) { //sees if the buffer is empty, if it is empty, we cannot return the peek
        throw std::runtime_error("peek: can't return peek from an empty ring");
    } else {
        return _ringBuffer[0]; //we return the peek
    }
}
