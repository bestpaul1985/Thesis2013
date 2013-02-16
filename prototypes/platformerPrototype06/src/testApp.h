#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "player1particle.h"
#include "ofxBox2d.h"

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
    
        //----------player1
        player1particle playerA;
        ofPoint frcA;
        bool bGoLeftA, bGoRightA, bJumpA;
        //----------UI
        ofRectangle button1,button2,button3;
        ofColor bc1,bc2,bc3;
        //----------Box2d
        ofxBox2d worldA;
        //----------Background------
//        ofImage bgA;
        //----------item 1----------
        ofPoint itemPos1;



};


