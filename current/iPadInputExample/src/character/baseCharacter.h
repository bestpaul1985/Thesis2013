//
//  baseCharacter.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__baseCharacter__
#define __iPadInputExample__baseCharacter__

#include <iostream>
#include "ofMain.h"
#include "particle.h"

class baseCharacter{
public:
    void setup(float x, float y);
    void update(float x, float y);
    virtual void draw();
    
    particle center;
    float width;
    float height;
    bool  bReverse;
    int num;
};

#endif /* defined(__iPadInputExample__baseCharacter__) */
