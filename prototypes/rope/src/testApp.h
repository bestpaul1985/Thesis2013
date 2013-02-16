#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxiPhoneExternalDisplay.h" 

#include "ofxBox2d.h"
#include "ofxXmlSettings.h"

#include "particle.h"
#include "spring.h"
#include "rope.h"

class testApp : public ofxiPhoneApp, public ofxiPhoneExternalDisplay{
	
    ofxBox2d                worldP1;
    ofxBox2d                worldP2;

    ofxBox2dRect            character1;
    vector<ofxBox2dRect>    enemies;
    ofPoint                 diffP1;
    ofPoint                 lastPosP1;
    ofPoint                 offSet;
    
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
    
    
    
        //******** gameEvent **************************

        vector <ofVec2f> holes;
        
        int maxBullets;
        int enemyKilled;
        float bulletsNum;
        bool bFire;
        ofPoint pos;
        ofPoint refillPos;
        string message;
        //******** map **************************
        ofxXmlSettings              XML;
        vector<ofxBox2dPolygon>     polyLines1;
        vector<ofxBox2dPolygon>     polyLines2;
        //********buttons**************************

        bool                    bFixedButtonP1;
        bool                    bFixedButtonP2;

        vector<ofPoint>         touchesTop;
        vector<ofPoint>         touchesTopPre;
        vector<ofPoint>         touchesBot;
        vector<ofPoint>         touchesBotPre;
    
        rope myRope;
        ofxAccelerometerHandler ofxAccelerometer;

};


