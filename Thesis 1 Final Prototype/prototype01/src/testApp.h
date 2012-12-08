#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"

#include "dirctiveButton.h"
#include "jumpButton.h"
#include "guy.h"
#include "girl.h"

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
    
        //********box2d**************************
        ofxBox2d                worldP1;
        ofxBox2d                worldP2;
        ofxBox2dPolygon         polyLine1;
        ofxBox2dPolygon         polyLine2;
        //********buttons**************************
        directiveButton         P1L;
        directiveButton         P1R;
        directiveButton         P2L;
        directiveButton         P2R;
        jumpButton              P1J;
        jumpButton              P2J;
        jumpButton              P1F;
        jumpButton              P2F;
        //******** guy *********************
        guy                     myGuy;
        ofxBox2dRect            chracater1;
        ofPoint                 diffP1;
        ofPoint                 lastPosP1;
        //******** girl *********************
        girl                     myGirl;
        ofxBox2dRect            chracater2;
        ofPoint                 diffP2;
        ofPoint                 lastPosP2;
    
};


