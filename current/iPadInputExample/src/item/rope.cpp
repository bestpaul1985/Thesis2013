//
//  rope.cpp
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#include "rope.h"


void rope::setup(){
    pickUpSound.loadSound("sound/Pickup_Rope.wav");
    pickUpSound.setMultiPlay(true);
    useSound.loadSound("sound/Use_rope.wav");
    useSound.setMultiPlay(false);
}


void rope::playPickUpSound(){
    pickUpSound.play();
}


void rope::playUseSound(){
    useSound.play();
}