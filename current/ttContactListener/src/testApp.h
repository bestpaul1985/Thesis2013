#define ITEM_NUMBER 10

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttRopeBasic.h"
#include "ttRopeJoint.h"
#include "ttRopeData.h"
#include "ttGroundData.h"
#include "ttControl.h"
class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);
    
        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);
    
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

    ofxBox2d        world_A,        world_B;
    ofxBox2dRect    charDummy_A,    charDummy_B;
    ofxBox2dCircle  ropeEnd_A,  ropeEnd_B;
    ofxBox2dRect    item[ITEM_NUMBER];
    ofxBox2dPolygon ground_A, ground_B;
    
    ttChar  char_A;
    ttChar  char_B;

    ttRopeBasic rope_A;
    ttRopeBasic rope_B;
    
    ttRopeJoint ropeJoint_A;
    ttRopeJoint ropeJoint_B;
    
    ttControl control_A;
    ttControl control_B;
    
    ofxBox2d  obstacle;
    
   
    
};


