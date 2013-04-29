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
#include "ttThorn.h"
#include "ttSky.h"
#include "ttIndicator.h"
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
    
        void screen();
    
        ofxBox2d            world_A,        world_B;
        ofxBox2dRect        charDummy_A,    charDummy_B;
        ofxBox2dCircle      ropeEnd_A,  ropeEnd_B;
        ttChar              char_A,char_B;
        int                 numFootContacts_A, numFootContacts_B;
        ttControl           control;
        ttGround            ground_A, ground_B;
        ofRectangle         view_A,view_B;
        ofPoint             preTouch_A,preTouch_B;
        ofPoint             camPos_A,camPos_B;
        ofPoint             translate_A, translate_B;
        ofPoint             final_translate_A, final_translate_B;
        ofPoint             screen_A, screen_B;
        ofPoint             camera_A, camera_B;
      
        //thorns
        ttThorn             thorns_A, thorns_B;
        //sky
        ttSky               sky;
        //Indictor
        ttIndicator         accIndictor;
        //ropes
        ofPolyline          rope_A, rope_B;
};


