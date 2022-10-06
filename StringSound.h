// Copyright 2022 Zachary Gilbert
#ifndef StringSound_H //NOLINT
#define StringSound_H //NOLINT
#include "CircularBuffer.h"
#include <vector>
#include <SFML/System.hpp>
class StringSound {
 public:
    explicit StringSound(double frequency);
    explicit StringSound(std::vector<sf::Int16> init);
    StringSound (const StringSound &obj) = delete;
    ~StringSound();
    void pluck();
    void tic();
    sf::Int16 sample();
    int time();
 private:
    CircularBuffer * _cb;
    int _time;
};

#endif //NOLINT