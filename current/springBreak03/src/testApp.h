#define ITEM_NUMBER 10

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttSetData.h"
#include "ttControl.h"
#include "ttGround.h"
#include "ttRope.h"
#include "ttThorn.h"
class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();

        void drawScene(int iCameraDraw);
    
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);
    
        void contactStart_worldA(ofxBox2dContactArgs &e);
        void contactEnd_worldA(ofxBox2dContactArgs &e);
    
        void contactStart_worldB(ofxBox2dContactArgs &e);
        void contactEnd_worldB(ofxBox2dContactArgs &e);
    
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

        ofxBox2d        world_A,        world_B;
        ofxBox2dRect    charDummy_A,    charDummy_B;
        ofxBox2dCircle  ropeEnd_A,  ropeEnd_B;
        ofxBox2dRect    item[ITEM_NUMBER];
    
        ttChar  char_A;
        ttChar  char_B;
        int numFootContacts_A, numFootContacts_B;
    
        ttControl control_A;
        ttControl control_B;
    
        ttGround  ground_A, ground_B;
    
        ofRectangle view_A,view_B;
        ofPoint preTouch_A,preTouch_B;
        ofPoint camPos_A,camPos_B;
        ofPoint translate_A, translate_B;
        ofPoint orgPos_A, orgPos_B, currentPos_A, currentPos_B, offSet_A, offSet_B;
        //rope
        ttRope rope_A,rope_B;
        //thorns
        ttThorn thorns_A, thorns_B;
    
};


