// Copyright 2022 Zachary Gilbert
#include "CircularBuffer.h"
#include <stdint.h>
#include <iostream>
#include <exception>
CircularBuffer::CircularBuffer(int cap) {
    if (cap < 1) {
        throw std::invalid_argument("CircularBuffer constructor: "
        "capacity must be greater than zero.");
    }
    capacity = cap;
    bufferSize = 0;
    _ringBuffer = new int16_t[cap];
}
int CircularBuffer::getCapacity() {
    return capacity;
}
int CircularBuffer::size() {
    return bufferSize;
}
bool CircularBuffer::isEmpty() {
    if (bufferSize == 0) {
        return true;
    } else {
        return false;
    }
}
bool CircularBuffer::isFull() {
    if (bufferSize == capacity) {
        return true;
    } else {
        return false;
    }
}
void CircularBuffer::enqueue(int16_t x) {
    if (bufferSize == capacity) {
        throw std::runtime_error("enqueue: can't enqueue to a full ring");
    } else {
        bufferSize++;
        _ringBuffer[bufferSize - 1] = x;
    }
}
int16_t CircularBuffer::dequeue() {
    if (bufferSize == 0) {
        throw std::runtime_error("dequeue: can't dequeue an empty ring");
    } else {
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
    if (bufferSize == 0) {
        throw std::runtime_error("peek: can't return peek from an empty ring");
    } else {
        return _ringBuffer[0];
    }
}
