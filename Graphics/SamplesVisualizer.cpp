#include <stdio.h>
#include <stdlib.h>


#include <iostream>
#include "SamplesVisualizer.h"

using namespace std;
using namespace sf;
SamplesVisualizer::SamplesVisualizer()
{
    this->gridCpt = 0;
}


deque<double> SamplesVisualizer::getSampleEnergyHistory()
{
    return this->SampleEnergyHistory;
}

void SamplesVisualizer::pushSampleLine(double sampleEnergy)
{
    this->SampleEnergyHistory.push_front(sampleEnergy);
    if(this->SampleEnergyHistory.size() > 800)
    {
        this->SampleEnergyHistory.pop_back();
    }
}


void  SamplesVisualizer::drawSamples(sf::RenderWindow& window, double maxEnergy)
{
    int energyFactor =  maxEnergy / (window.getSize().y / 2);
    if(this->gridCpt >= 800){
        this->gridCpt =0;
        window.clear();
    }

    for (std::deque<double>::iterator itor = this->SampleEnergyHistory.begin()+5; itor > this->SampleEnergyHistory.begin(); itor--)
    {
        energyFactor= (*itor / (maxEnergy / window.getSize().y))/2;

        if(energyFactor < 1 )
        {
            energyFactor = 1;
        }

        sf::Color randColor(rand() % 255 , rand() % 255 , rand() % 255);
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(this->gridCpt,250 + energyFactor),randColor),
            sf::Vertex(sf::Vector2f(this->gridCpt,250 - energyFactor),randColor)
        };
        window.draw(line,2,sf::Lines);
        this->gridCpt++;

    }

    window.display();

}







