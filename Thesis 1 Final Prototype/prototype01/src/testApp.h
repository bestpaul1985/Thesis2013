#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"

#include "dirctiveButton.h"
#include "jumpButton.h"
#include "guy.h"
#include "girl.h"
#include "keys.h"
#include "chests.h"


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
        bool                    bFixedButtonP1;
        bool                    bFixedButtonP2;
        //******** guy *********************
        guy                     myGuy;
        ofxBox2dRect            chracater1;
        ofPoint                 diffP1;
        ofPoint                 lastPosP1;
        //******** girl *********************
        girl                    myGirl;
        ofxBox2dRect            chracater2;
        ofPoint                 diffP2;
        ofPoint                 lastPosP2;
    
        //******** Keys *********************
        keys                    key1;
        ofxBox2dRect            keysubstitute1;
        keys                    key2;
        ofxBox2dRect            keysubstitute2;
    
        int                     keyState1;
        bool                    key1UsedP1;
        bool                    key1UsedP2;
    
        int                     keyState2;
        bool                    key2UsedP1;
        bool                    key2UsedP2;
        //********* passing belts*********************
        ofPolyline              beltP1;
        ofPolyline              beltP2;
        float                   beltPctP1;
        float                   beltPctP2;
    
        //********* chests *********************
        chests                  myChest1;
        chests                  myChest2;
        ofxBox2dRect            chestSub1;
        ofxBox2dRect            chestSub2;
};

