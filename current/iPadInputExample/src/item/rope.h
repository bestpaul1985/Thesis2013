//
//  rope.h
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#ifndef __rylic__rope__
#define __rylic__rope__

#include <iostream>
#include "ofMain.h"
#include "ofxBox2d.h"

class rope{
    
    void setup();
    void playPickUpSound();
    void playUseSound();
    
    ofSoundPlayer               pickUpSound;
    ofSoundPlayer               useSound;
};

#endif /* defined(__rylic__rope__) */
