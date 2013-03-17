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
#include "ofxBox2d.h"
#include "ttControl.h"
class ttRopeJoint{
    
public:
    void setup(ofxBox2d &World,ttRopeBasic &RopeBasic,ttControl &Control);
    void update();
    void swing();
    void draw();
    
    ofxBox2d                        *world;
    ofxBox2dRect                    endRect;
    ofxBox2dRect 					startRect;
    ofxBox2dJoint                   rope;
    
    ttRopeBasic                     *ropeBasic;
    ttControl                       *control;
    ofRectangle                     rect;
    
    int                             num_char;
    bool                            bSetup;
    
    ofPoint                         startPos;
    ofPoint                         endPos;
    ofPoint                         getPos;
    float                           startHight;
    float                           startWidth;
    float                           endWidth;
    float                           endHight;
    
};


#endif /* defined(__thatTheyClassSwing2__ttRopeJoint__) */
