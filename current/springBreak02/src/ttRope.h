//
//  ttRope.h
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#ifndef __springBreak02__ttRope__
#define __springBreak02__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttRope{
public:
    void setup(ofPoint &offset);
    void updateAccelerometer(ofPoint acc);
    void update();
    void draw();
    
    ofPoint *offSet;
    
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    
    float length;
    int ropeNum;
    
};

#endif /* defined(__springBreak02__ttRope__) */
