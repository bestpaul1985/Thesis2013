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
    void callCharacter(int x, int y);
    
    //********box2d**************************
    ofxBox2d                world;
    
    baseCharacter character;
    
};
#endif /* defined(__rylic__baseWorld__) */
