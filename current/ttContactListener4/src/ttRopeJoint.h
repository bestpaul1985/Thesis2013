//
//  ttRopeJoint.h
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#ifndef __thatTheyClassSwing2__ttRopeJoint__
#define __thatTheyClassSwing2__ttRopeJoint__

#include "ofMain.h"
#include "ofxBox2d.h"

#include "ofMain.h"
#include "ttRopeBasic.h"
#include "ttSetData.h"
#include "ofxBox2d.h"
#include "ttControl.h"

class ttRopeJoint{
    
public:
    void setup(ofxBox2d &World,ttRopeBasic &RopeBasic,ttControl &Control);
    void contact();
    void update();
    void swing();
    void draw();
    
    ofxBox2d                        *world;
    ofxBox2dCircle                  anchor;
    vector<ofxBox2dJoint>           joints;
    vector<ofxBox2dCircle>          circles;
    
    ofxBox2dCircle                  *lastPoint;
    ttRopeBasic                     *ropeBasic;
    ttControl                       *control;
    ofRectangle                     rect;
    ofPoint                         getLastPos;
    float                           startTime;
    float                           duration;
    bool                            bNewRope;
    bool                            bStop;
    bool                            bHooking;
    float                           speed;
    float                           toLength;
    float                           ropeLength;

};


#endif /* defined(__thatTheyClassSwing2__ttRopeJoint__) */
