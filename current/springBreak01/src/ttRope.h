//
//  ttRope.h
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#ifndef __springBreak01__ttRope__
#define __springBreak01__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttSetData.h"
#include "ttControl.h"
class ttRope{
public:
    void setup(ttChar &chraA, ttChar &chraB,ttControl &cont_A,ttControl &cont_B, int num);
    void setupContactListener();
    void update();
    void cameraUpdate(ofCamera cam_A, ofCamera cam_B);
    void accelerometerUpdate(ofPoint Acc);
    void draw();
    void swing();
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);

    
    ttChar *char_A;
    ttChar *char_B;
    ttControl *control_A;
    ttControl *control_B;
    ofxBox2d world;
    ofxBox2dRect dummy;
    ofxBox2dRect start;
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    ofxBox2dJoint          swingJoint;
    
    ofRectangle Directional_Touch_Area;
  
    ofPoint frc, dumScreen, ropeScreen;
    ofPoint preTouchPos;
    ofPoint diff;
    ofPoint prePos;
    float startTime;
    float duration;
    float dis;
    bool bFixRope;
    bool bSwing;
    
    int swingNum;
    int touchId;
    int ropeNum;
};

#endif /* defined(__springBreak01__ttRope__) */
