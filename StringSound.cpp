// Copyright 2022 Zachary Gilbert
#include "StringSound.h" //NOLINT
#include <math.h>
#include <random>
StringSound::StringSound(double frequency) {
    _cb = new CircularBuffer(ceil(44100/frequency));
}
StringSound::StringSound(std::vector<sf::Int16> init) {
    _cb = new CircularBuffer(init.size());
    for (int i = 0; i < _cb->getCapacity(); i++) {
            _cb->enqueue(init[i]);
    }
}
void StringSound::pluck() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-32768, 32767);
    if (_cb->isEmpty() == true) {
        for (int i = 0; i < _cb->getCapacity(); i++) {
            _cb->enqueue(distr(gen));
        }
    } else {
        for (int i = 0; i < _cb->getCapacity(); i++) {
            _cb->dequeue();
        }
    }
}
void StringSound::tic() {
    double newVibration;
    newVibration = .996 * (.5 * (_cb->dequeue() + _cb->peek()));
    _cb->enqueue(newVibration);
    _time++;
}
int StringSound::time() {
    return _time;
}
sf::Int16 StringSound::sample() {
    return _cb->peek();
}
StringSound::~StringSound() {}
