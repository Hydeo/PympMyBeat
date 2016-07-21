#include <iostream>

#include "GPIOC/GPIO.h"
#include "Graphics/SamplesVisualizer.h"
#include "BeatDetector/BeatDetector.h"

#include <chrono>
#include <thread>

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctime>
#include <cstdio>

sf::Mutex GlobalMutex;
using namespace sf;
using namespace std;




int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Nombre d'arguments erroné : PympMyBeat [-wav path]";
        return -1;
    }

    double maxEnergy =0;
    SamplesVisualizer sv;
    bool firstLoop = true;
    GPIO gpio18("18");
    gpio18.gpio_init();
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    window.clear();
    sf::Clock Clock;
    float FrameTime;


    std::vector<sf::Int16> Buffer;
    std::vector<float> EnergyHistoryBuffer;
    EnergyHistoryBuffer.resize(43, 0.f);
    std::deque<double> SamplesHistoryBuffer;

    cout<< "arg : "<< argv[1]<<endl;
    BeatDetector bd;
    bd.initBuffer(argv[1]);


    for(int k =0; k < (bd.buffer.getSampleCount()/1024)-1; k++)
    {



        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close Event
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

        }

        //--- Framerate de la fenetre SFML -----------
        FrameTime = Clock.getElapsedTime().asSeconds();
        std::cout << "Framerate - "<< k <<": " << 1.f / FrameTime << std::endl;
        Clock.restart();
        //--------------

        //GlobalMutex.lock();

        bd.InstantEnergy(k);

        if(bd.InstantEnergie > maxEnergy)
        {
            maxEnergy = bd.InstantEnergie;
        }

        sv.pushSampleLine(bd.InstantEnergie);
        sv.drawSamples(window, maxEnergy);


        //---------------------- Playing sound --------------------------------
        sf::SoundBuffer playBuffer;
        playBuffer.loadFromSamples(&bd.getPlaySamples()[0],bd.getPlaySamples().size(),1,44100);
        sf::Sound Sound(playBuffer);
        Sound.play();
        clock_t tima_a = clock();
        do{}while(Sound.getStatus()==SoundSource::Playing);

        //---------------------------------------------------------------------
        bd.LocalAverage();
        bd.Variance();
        if(bd.Detection())
        {
            gpio18.gpio_setval("1");
        }
        else
        {
            gpio18.gpio_setval("0");
        }

        if(firstLoop)
        {
            //music.play();
            firstLoop = false;
        }

        if(!firstLoop)
        {
            clock_t time_b = clock();
        }



    }
    gpio18.gpio_unexport();

    cout << "Press enter to quit..."<<endl;
    do    {    }    while(cin.get() !='\n');

    return 1;

}
