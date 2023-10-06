// Copyright 2022 Zachary Gilbert
#include "CircularBuffer.h"
#include "StringSound.h"
#include <math.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#define CONCERT_A 440.0    
#define SAMPLES_PER_SEC 44100
//Global variables for the starting note, and how many samples per second for the quality of the sound
std::vector<sf::Int16> makeSamples(StringSound& gs) { // NOLINT
    std::vector<sf::Int16> samples;
    gs.pluck(); //creates a pluck call
    int duration = 8;  // seconds
    int i; //temp variable for the loop
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }
    return samples; //we return the samples
}
int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300),
    "SFML Plucked String Sound"); //creates the piano roll
    sf::Event event;
    double freq; //keeps track of the frequency of the note
    std::vector<sf::Int16> samples; //we create this to keep track of the samples
    std::vector<std::vector<int16_t>> sample(37); // we want a samples size of 37
    std::vector<sf::Sound> sounds(37); // we want a sound size of 37
    std::vector<sf::SoundBuffer> soundBuffers(37); // we want a buffer size of 37
    std::string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' "; //used to keep track of the keyboard keys to assign a note per key press
for (int i = 0; i < 37; i++) {
        freq = CONCERT_A * pow(2, ((i - 24)/12.0)); //We create a starting frequency based off the starting note, and then we pitch it up or down depending on the key that was pressed
        StringSound gs1(freq); //Here we create the object that will hold all information about the string note, and the degredation of the note
        sample[i] = makeSamples(gs1); //creates the samples so we can audibly recreate them
        if (!soundBuffers[i].loadFromSamples(&sample[i][0], //Here we load the samples into the buffer so it can be played
        sample[i].size(), 2, SAMPLES_PER_SEC))
        throw std::runtime_error
        ("sf::SoundBuffer: failed to load from samples.");
    sounds[i].setBuffer(soundBuffers[i]); //Here we load the sound based off the buffer of the sound
    }
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode) { //This is for receiving the key that was pressed
                    int key;
                    key = keyboard.find(event.text.unicode);
                    if (key != -1) {
                        sounds[key].play(); //play the sound
                    }
                }
                default:
                break;
            }
            window.clear(); //clear window
            window.display(); //clear the display of any artifacts left behind
        }
    }
    return 0; //exit
}
