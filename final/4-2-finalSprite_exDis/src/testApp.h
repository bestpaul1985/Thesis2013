#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxiPhoneExternalDisplay.h"
#include "ofxBox2d.h"
#include "ttChar.h"
#include "ttSetData.h"
#include "ttControl.h"
#include "ttGround.h"
#include "ttRope.h"
#include "ttThorn.h"
#include "ttSky.h"
#include "ttIndicator.h"
class testApp : public ofxiPhoneApp, public ofxiPhoneExternalDisplay{
	
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
    
        void screen();
    
        ofxBox2d        world_A,        world_B;
    
        ttChar  char_A;
        ttChar  char_B;
        int numFootContacts_A, numFootContacts_B;
    
        ttControl control;
           
        ttGround  ground_A, ground_B;
    
        ofPoint translate_A, translate_B;
        ofPoint screen_A, screen_B;
        ofPoint camera_A, camera_B;
        //rope
        ttRope rope_A,rope_B;
        //thorns
        ttThorn thorns_A, thorns_B;
        //sky
        ttSky sky;
        //Indictor
        ttIndicator accIndictor;
};


