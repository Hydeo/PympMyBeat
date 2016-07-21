#include "BeatDetector.h"
#include <iostream>

using namespace std;

BeatDetector::BeatDetector()
{
    this->maxEnergy = 0;
    this->InstantEnergie = 0;
    this->localAverage = 0;
    this->variance = 0;
    this->sensibility = 0;
}

void BeatDetector::initBuffer(string pathFile)
{
    if(!this->buffer.loadFromFile(pathFile))
    {
        cout << "Buffering "<< pathFile <<" Failed ! \n";
    }

    for(int i=0; i<this->buffer.getSampleCount(); i++)
    {
        Buffer.push_back(this->buffer.getSamples()[i]);
    }

    cout<< " Buffering "<< pathFile <<" OK !\n";

}

void BeatDetector::InstantEnergy(int k)
{
    this->playSamples.clear();
    this->InstantEnergie = 0;
    for (std::vector<sf::Int16>::iterator itor = Buffer.begin()+1024*k; itor < Buffer.begin()+1024*(k+1); itor++)
    {
        this->InstantEnergie += (*itor);
        if(this->InstantEnergie < 0)
            this->InstantEnergie = this->InstantEnergie *-1;
        this->playSamples.push_back(*itor);
    }
    addToSamplesHistory();

}

void BeatDetector::LocalAverage()
{
    this->localAverage=0;
    for (std::deque<double>::iterator itor = this->SamplesHistoryBuffer.begin(); itor < this->SamplesHistoryBuffer.end(); itor++)
    {
        this->localAverage += (*itor);
    }
    this->localAverage = this->localAverage *((double)(1./this->SamplesHistoryBuffer.size()));
}

void BeatDetector::Variance()
{
    this->variance = 0;
    for (std::deque<double>::iterator itor = this->SamplesHistoryBuffer.begin(); itor < this->SamplesHistoryBuffer.end(); itor++)
    {
        this->variance += (*itor - this->localAverage);
    }
    this->variance = this->variance * ((double)(1./this->SamplesHistoryBuffer.size()));
}

bool BeatDetector::Detection()
{
    this->sensibility = (-0.0025714 * variance) + 1.5142857;
    if( this->sensibility*this->localAverage < this->InstantEnergie)
    {
        std::cout << " WE HAVE A BEAT! " << std::endl;
        return true;
    }
    std::cout << " No BEAT! " << std::endl;
    return false;
}

std::vector<sf::Int16> BeatDetector::getPlaySamples()
{
    return this->playSamples;
}


void BeatDetector::addToSamplesHistory()
{
    this->SamplesHistoryBuffer.push_front(this->InstantEnergie);
    if(this->SamplesHistoryBuffer.size() > 43)
    {
        this->SamplesHistoryBuffer.pop_back();
    }
}
