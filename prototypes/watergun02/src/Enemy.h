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
#include "ofxBox2d.h"
class Enemy : public ofxBox2dRect{
public:
    
    ofVec2f          pos, vel;
    vector <ofVec2f> squashPts;
    bool             bSquashed;
    bool             bRemove;
    float            timeEnemyKilled;
    
    Enemy(){
        
        bRemove       = false;
        bSquashed     = false;
      
        timeEnemyKilled = 0;
        
        int nPts = 10;
        for(int i=0; i<nPts; i++) {
            squashPts.push_back(ofVec2f(ofRandom(-8, 8), ofRandom(-8, 8)));
        }
    }
    
    void update() {
      
        
        if(!bSquashed) {
//            pos += vel;
//            float speed = 0.03;
//            vel.x += ofRandom(-speed, speed);
//            vel.y += ofRandom(-speed, speed);
        } else {
            float timeDead = ofGetElapsedTimef() - timeEnemyKilled;
            if(timeDead > 0.6) {
                bRemove = true;
            }
        }
        
        
    }
    
    
    void draw(){
        
        float width = getWidth();
        float height = getHeight();
        
        if(!bSquashed) {
//          ofSetHexColor(0x688736);
            ofSetColor(0, 161, 217);
            ofPushMatrix();
                ofTranslate(getPosition().x, getPosition().y);
                ofRect(0,0,width,height);

            ofPopMatrix();
        }else{
//            ofSetHexColor(0xE32289);
            ofSetColor(0, 161, 217);
            for(int i=0; i<squashPts.size(); i++) {
                ofCircle(getPosition() + squashPts[i], 5);
            }
            
        }
        
    }

    
};
#endif /* defined(__waterGun__enemy__) */
