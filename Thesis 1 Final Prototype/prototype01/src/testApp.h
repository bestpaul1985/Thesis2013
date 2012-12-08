#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"

#include "dirctiveButton.h"
#include "jumpButton.h"
#include "character.h"

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
        
        ofxBox2d worldP1;
        directiveButton P1L;
        directiveButton P1R;
        jumpButton P1J;
    
        directiveButton P2L;
        directiveButton P2R;
        jumpButton P2J;
    
        character P1;
        character P2;
    
        ofImage guy;
        ofImage girl;
    
};


