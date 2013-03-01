//
//  key.cpp
//  rylic
//
//  Created by Firm Read on 2/18/13.
//
//

#include "key.h"


void key::setup(){
    pickUpSound.loadSound("sound/Pickup_Rope.wav");
    pickUpSound.setMultiPlay(true);
    useSound.loadSound("sound/Use_rope.wav");
    useSound.setMultiPlay(false);
}




void key::playPickUpSound(){
    pickUpSound.play();
}


void key::playUseSound(){
    useSound.play();
}