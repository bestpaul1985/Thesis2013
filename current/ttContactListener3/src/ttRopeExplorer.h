//
//  ttRopeJoint.h
//  thatTheyClassSwing2
//
//  Created by PengCheng on 3/15/13.
//
//

#ifndef __thatTheyClassSwing2__ttRopeExplorer__
#define __thatTheyClassSwing2__ttRopeExplorer__

#include "ofMain.h"
#include "ofxBox2d.h"

#include "ofMain.h"
#include "ttRopeBasic.h"
#include "ofxBox2d.h"
#include "ttSetData.h"
#include "ttControl.h"
class ttRopeExplorer{
    
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
    bool                            bStop;
    ofPoint                         startPos;
    ofPoint                         endPos;
    ofPoint                         getPos;
    string                          name;
    float                           startHight;
    float                           startWidth;
    float                           endWidth;
    float                           endHight;
    
    float                           speed;
    float                           length;
    float                           dis;
};


#endif /* defined(__thatTheyClassSwing2__ttRopeJoint__) */
