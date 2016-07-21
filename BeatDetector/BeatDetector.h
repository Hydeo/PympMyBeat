#ifndef BEATDETECTOR_INCLUDED
#define BEATDETECTOR_INCLUDED
#include <string>
#include <SFML/Audio.hpp>
#include <vector>
#include <deque>



class BeatDetector{
    public:
        BeatDetector();
        void initBuffer(std::string pathToFile);
        void InstantEnergy(int k);
        void LocalAverage();
        void Variance();
        bool Detection();
        std::vector<sf::Int16> getPlaySamples();

        double maxEnergy;
        double InstantEnergie;
        double localAverage;
        double variance;
        double sensibility;
        sf::SoundBuffer buffer;
        std::vector<sf::Int16> Buffer;

    private:
        std::vector<sf::Int16> playSamples;
        std::vector<float> EnergyHistoryBuffer;
        std::deque<double> SamplesHistoryBuffer;
        void addToSamplesHistory();
};


#endif // BEATDETECTOR_INCLUDED
