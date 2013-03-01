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
#include "ofxBox2d.h"

class baseCharacter{
public:
    void setup(float x, float y);
    void update(float x, float y);
    virtual void draw();
    void playJumpSound();
    
    //initial data
    particle center;
    float width;
    float height;
    
    ofxBox2dRect            charHitBox;
    ofPoint                 diff;
    ofPoint                 lastPos;
    ofPoint                 offSet;
    
    //sprite management
    bool  bReverse;     //direction
    int num;            //mode number
    
    
    
    //playsound
    ofSoundPlayer jump;
};

#endif /* defined(__iPadInputExample__baseCharacter__) */
