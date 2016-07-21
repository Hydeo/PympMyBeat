PMB: smflBeatDetection.cpp
	g++  -std=c++11 smflBeatDetection.cpp GPIOC/GPIO.cpp Graphics/SamplesVisualizer.cpp BeatDetector/BeatDetector.cpp -o PympMyBeat-App -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
