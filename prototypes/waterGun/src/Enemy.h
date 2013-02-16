//
//  enemy.h
//  waterGun
//
//  Created by PengCheng on 2/10/13.
//
//

#ifndef __waterGun__enemy__
#define __waterGun__enemy__

#include "ofMain.h"

class Enemy{
public:
    
    ofVec2f          pos, vel;
    float            size;
    vector <ofVec2f> squashPts;
    bool             bSquashed;
    bool             bRemove;
    float            timeEnemyKilled;
    
    Enemy(){
        
        bRemove       = false;
        bSquashed     = false;
        size          = 10;
        timeEnemyKilled = 0;
        
        int nPts = 10;
        for(int i=0; i<nPts; i++) {
            squashPts.push_back(ofVec2f(ofRandom(-4, 4), ofRandom(-4, 4)));
        }
    }
    
    void update() {
        
        if(!bSquashed) {
            pos += vel;
            float speed = 0.03;
            vel.x += ofRandom(-speed, speed);
            vel.y += ofRandom(-speed, speed);
        } else {
            float timeDead = ofGetElapsedTimef() - timeEnemyKilled;
            if(timeDead > 0.3) {
                bRemove = true;
            }
        }
        
        
    };
    void draw(){
        
        if(!bSquashed) {
            
            ofSetHexColor(0x688736);
            
            ofPushMatrix();
            ofTranslate(pos);
            ofCircle(0,0, size);
            ofPopMatrix();
        }else{
            ofSetHexColor(0xE32289);
            for(int i=0; i<squashPts.size(); i++) {
                ofCircle(pos + squashPts[i], 2);
            }
            
        }
        
    };

    
};
#endif /* defined(__waterGun__enemy__) */
