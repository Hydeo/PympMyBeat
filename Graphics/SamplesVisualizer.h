#ifndef SamplesVisualizer_INCLUDED
#define SamplesVisualizer_H_INCLUDED
#include <string>
#include <deque>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
/*
Cette classe gère l'interface graphique
*/

class SamplesVisualizer{
    public:
        SamplesVisualizer();
        deque<double> getSampleEnergyHistory();
        void pushSampleLine(double sampleEnergy);
        void drawSamples(sf::RenderWindow& windown, double maxEnergy);
    private:
        deque<double> SampleEnergyHistory;
        int gridCpt;
};

#endif
