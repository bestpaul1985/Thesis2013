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
#include "ofxBox2d.h"

class ttRopeJoint{
    
public:
    void setup(ofxBox2d &world, int Num_Char);
    void update(bool fixedmove,bool &SwingLeft, bool &SwingRight, ofPoint diff, float length, ofPoint pos);
    void draw();
    
    ofxBox2dRect                    endRect;
    ofxBox2dRect 					startPoint;
    ofxBox2dJoint                   rope;
    int                             num_char;
    ofRectangle                     rect;
    
};


#endif /* defined(__thatTheyClassSwing2__ttRopeJoint__) */
