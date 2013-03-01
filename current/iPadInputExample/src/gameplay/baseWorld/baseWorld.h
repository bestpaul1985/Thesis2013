//
//  baseWorld.h
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#ifndef __rylic__baseWorld__
#define __rylic__baseWorld__

#include <iostream>
#include "ofMain.h"
#include "baseCharacter.h"
#include "ofxBox2d.h"
#include "ofxXmlSettings.h"

class baseWorld {
public:
    
    void setup();
    void callP1     (baseCharacter p1, int x, int y);
    void callP2     (baseCharacter p2, int x, int y);
    virtual void loadMap();
    virtual void loadImage();
    virtual void loadSound();
    
    // box2d
    ofxBox2d            world1,world2;
    
    // load characters
    baseCharacter       p1,p2;
    
};
#endif /* defined(__rylic__baseWorld__) */
