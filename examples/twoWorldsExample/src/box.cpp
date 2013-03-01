//
//  box.cpp
//  twoWorldExample
//
//  Created by Firm Read on 3/1/13.
//
//

#include "box.h"

void box::setup(ofxBox2d world1, ofxBox2d world2){
    
    // we can also have a vector of any shape that is
    // shared between both worlds
    for(int i=0; i<20; i++) {
        
        ofxBox2dRect r;
        r.setPhysics(1, 0.7, 0.9);
        
        // add to world A
        if(i <= 9) {
            r.setup(world1.getWorld(), 250+ofRandom(-50, 50), 10, ofRandom(10,30), ofRandom(10,30));
        }
        
        // add to world B
        else {
            r.setup(world2.getWorld(), 750+ofRandom(-50, 50), 10, ofRandom(10,30), ofRandom(10,30));
        }
        
        // add to one vector
        sharedRects.push_back(r);
    }
}


void box::draw(){
    // Shared Rects
    for (int i=0; i<sharedRects.size(); i++) {
        ofSetHexColor(0x2F9BA1);
        ofFill();
        sharedRects[i].draw();
    }
    
}