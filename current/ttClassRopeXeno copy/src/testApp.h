#define ITEM_NUMBER 10

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttRope.h"
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

    ttRope rope_A;
    ttRope rope_B;
};


