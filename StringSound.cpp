// Copyright 2022 Zachary Gilbert
#include "StringSound.h" //NOLINT
#include <math.h>
#include <random>
StringSound::StringSound(double frequency) {
    _cb = new CircularBuffer(ceil(44100/frequency)); //creates a buffer based off the inputted frequency
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
    if (_cb->isEmpty() == true) { //checks to see if the buffer has been cleared yet, if its clear, then we update the buffer
        for (int i = 0; i < _cb->getCapacity(); i++) {
            _cb->enqueue(distr(gen));
        }
    } else {
        for (int i = 0; i < _cb->getCapacity(); i++) {
            _cb->dequeue(); //starts the dequeue process if the buffer is not empty
        }
    }
}
void StringSound::tic() { //this function creates the degredation of the frequency of the note, similar to a guitar string slowly decreasing its frequency
    double newVibration; //variable to hold teh degredation amount
    newVibration = .996 * (.5 * (_cb->dequeue() + _cb->peek()));
    _cb->enqueue(newVibration); //here we load the buffer with new degraded samples
    _time++; //Duration of the note
}
int StringSound::time() {
    return _time; //returns the time of the sample (IE: how long the note is to be played)
}
sf::Int16 StringSound::sample() {
    return _cb->peek(); //returns the peek of the sample
}
StringSound::~StringSound() {} //deconstructor
