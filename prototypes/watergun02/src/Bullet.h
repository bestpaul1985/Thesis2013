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


class Bullet{
    
public:
    
    ofVec2f pos, vel;
    float   size;
    bool    bRemove;
    
    Bullet(){
     size = 15;
    
    }
    
    void update() {
        pos += vel;
        vel *= 0.99; // slowdown in a long time
    }
    
    void draw() {
        
        ofPushMatrix();
            ofSetColor(220,0,30);
            ofTranslate(pos.x, pos.y);
            ofRect(0,0, size,size);
        ofPopMatrix();
    }
    
};

#endif /* defined(__waterGun__bullet__) */
