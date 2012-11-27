#pragma once

#include "ofMain.h"
#include "timeLine.h"
#include "fft.h"
#include "fftOctaveAnalyzer.h"

#define BUFFER_SIZE 512

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioIn (float * input, int bufferSize, int nChannels);
    
    timeLine range1, range2, range3, range4, range5, range6;
    
    bool b1,b2,b3,b4,b5,b6;

    FFTOctaveAnalyzer   FFTanalyzer;
    
private:
    float * left;
    float * right;
    int bufferCounter;
    fft myfft;
    
    float magnitude [BUFFER_SIZE];
    float phase [BUFFER_SIZE];
    float power [BUFFER_SIZE];
    float freq [BUFFER_SIZE];
    
};
