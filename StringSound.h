// Copyright 2022 Zachary Gilbert
#ifndef StringSound_H //NOLINT
#define StringSound_H //NOLINT
#include "CircularBuffer.h"
#include <vector>
#include <SFML/System.hpp>
class StringSound { //StringSound Class
 public:
    explicit StringSound(double frequency); //constructor
    explicit StringSound(std::vector<sf::Int16> init);//constructor
    StringSound (const StringSound &obj) = delete;
    ~StringSound(); //deconstructor
    void pluck(); //function for the pluck simulation
    void tic(); //function for the degredation of the note
    sf::Int16 sample(); //variable to hold the samples
    int time(); //time of the note
 private:
    CircularBuffer * _cb; //Circuler buffer
    int _time; //time of the sound
};

#endif //NOLINT
