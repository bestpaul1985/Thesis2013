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
#include "ttRopeExplorer.h"
#include "ttSetData.h"
#include "ofxBox2d.h"
#include "ttControl.h"

class ttRopeJoint{
    
public:
    void setup(ofxBox2d &World,
               ttRopeBasic &RopeBasic,
               ttRopeExplorer &RopeExplorer,
               ttControl &Control
               );
    
    void update();
    void swing();
    void draw();
    
    ofxBox2d                        *world;
    ofxBox2dCircle                  anchor;
    vector<ofxBox2dJoint>           joints;
    vector<ofxBox2dCircle>          circles;
    
    ttRopeBasic                     *ropeBasic;
    ttRopeExplorer                  *ropeExplorer;
    ttControl                       *control;
    ofRectangle                     rect;
   
    float                           startTime;
    float                           duration;
    bool                            bNewRope;
    bool                            bStop;

};


#endif /* defined(__thatTheyClassSwing2__ttRopeJoint__) */
