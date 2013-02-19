//
//  soundInput.h
//  rylic
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __rylic__soundInput__
#define __rylic__soundInput__

#include <iostream>
#include "ofMain.h"

class soundInput{
public:
    void setup();
    //draw soundwave
    void drawScopeOpen(int x, int y);
    void drawWave(int i, float buffer);
    void drawLog();
    void drawScopeClose();
    
    int intx, inty;
    int height;
    
    //sound setup
    void bufferSizeCheck(int bufferSize);
    void volumeFeedback();
    
    int	initialBufferSize;
    int	sampleRate;
    int	drawCounter;
    int bufferCounter;
    
    //draw volume circle
    void updateVolCircle();
    void drawVolCircle(int x, int y, float scale);
    
    
    //volume feedback
    float curVol;
	int numCounted;
    float smoothedVol;
    float scaledVol;

};


#endif /* defined(__rylic__soundInput__) */
