//
//  bullet.h
//  waterGun
//
//  Created by PengCheng on 2/10/13.
//
//

#ifndef __waterGun__bullet__
#define __waterGun__bullet__

#include "ofMain.h"

class Bullet {
    
public:
    
    ofVec2f pos, vel;
    bool    bRemove;
    
    void update() {
        pos += vel;
        vel *= 0.99; // slowdown in a long time
    }
    
    void draw() {
        ofSetColor(20);
        ofCircle(pos, 2);
    }
    
};

#endif /* defined(__waterGun__bullet__) */
