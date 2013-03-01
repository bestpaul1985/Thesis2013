//
//  key.h
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#ifndef __rylic__key__
#define __rylic__key__

#include <iostream>


#include "ofMain.h"
#include "ofxBox2d.h"

class key{
    
    void setup();
    void playPickUpSound();
    void playUseSound();
    
    // sound
    ofSoundPlayer               pickUpSound;
    ofSoundPlayer               useSound;
    
};

#endif /* defined(__rylic__key__) */
