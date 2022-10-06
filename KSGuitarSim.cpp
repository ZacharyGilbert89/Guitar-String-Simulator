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
std::vector<sf::Int16> makeSamples(StringSound& gs) { // NOLINT
    std::vector<sf::Int16> samples;
    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }
    return samples;
}
int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300),
    "SFML Plucked String Sound");
    sf::Event event;
    double freq;
    std::vector<sf::Int16> samples;
    std::vector<std::vector<int16_t>> sample(37);
    std::vector<sf::Sound> sounds(37);
    std::vector<sf::SoundBuffer> soundBuffers(37);
    std::string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
for (int i = 0; i < 37; i++) {
        freq = CONCERT_A * pow(2, ((i - 24)/12.0));
        StringSound gs1(freq);
        sample[i] = makeSamples(gs1);
        if (!soundBuffers[i].loadFromSamples(&sample[i][0],
        sample[i].size(), 2, SAMPLES_PER_SEC))
        throw std::runtime_error
        ("sf::SoundBuffer: failed to load from samples.");
    sounds[i].setBuffer(soundBuffers[i]);
    }
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode) {
                    int key;
                    key = keyboard.find(event.text.unicode);
                    if (key != -1) {
                        sounds[key].play();
                    }
                }
                default:
                break;
            }
            window.clear();
            window.display();
        }
    }
    return 0;
}
