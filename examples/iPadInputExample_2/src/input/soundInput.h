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
    void drawScopeOpen(int x, int y);
    void drawWave(int i, float buffer);
    void drawLog();
    void drawScopeClose();
    void bufferSizeCheck(int bufferSize);
    
    int	initialBufferSize;
    int	sampleRate;
    int	drawCounter;
    int bufferCounter;
    
    int intx, inty;
    int height;
};

#endif /* defined(__rylic__soundInput__) */
