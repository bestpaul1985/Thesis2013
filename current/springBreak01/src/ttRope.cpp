//
//  ttRope.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttRope.h"

void ttRope::setup(ofxBox2d &world,ttChar &chra_A,ttChar &chra_B,ofPoint &accFrc,int num){

    ofRectangle temp(550, 500, 10, 10);
    rope.setPhysics(20.0f, 0.0f, 0.0f);
    rope.setup(world.getWorld(), temp);
    char_A = &chra_A;
    char_B = &chra_B;
    frc = &accFrc;
    charNum = num;
}


void ttRope::draw(ofCamera cam_A, ofCamera cam_B){
   
    if (charNum == 0) {
        ofPoint screenA;
        screenA = cam_A.worldToScreen(char_A->getPos);
        ofPoint worldB;
        worldB =  cam_B.screenToWorld(screenA);

        if (frc->y>-0.13) {
             rope.setPosition(worldB.x, worldB.y);
        }else{
            float y = rope.getPosition().y;
            rope.setPosition(worldB.x, y);
        }
        
        ofPoint diff;
        diff = screenA-worldB;
        ofPushMatrix();
        ofTranslate(diff.x, 0);
        rope.draw();
        ofPopMatrix();
//        cout<<"screenA: "<<screenA <<"  worldB: "<< worldB <<" diff:"<<diff<<endl;
    }
    
    
}