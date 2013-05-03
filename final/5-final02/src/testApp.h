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
#include "ttDog.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttEmoji.h"
enum _rope_condition{
    R_NO_USE,
    R_PUSH,
    R_SWING,
    R_DESTROY,
};


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
        void position();
    
        _rope_condition     rope_condition_A,rope_condition_B;
    
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
        ofPoint             char_pos_A, char_pos_B;
    
        ofPoint             hook_end_A, hook_end_B;
        ofPoint             hook_start_A, hook_start_B;
        ofPoint             rope_end_A, rope_end_B;
        ofPoint             rope_start_A,rope_start_B;
        float               hook_pct_A, hook_pct_B;
        //thorns
        ttThorn             thorns_A, thorns_B;
        //sky
        ttSky               sky;
        //Indictor
        ttIndicator         accIndictor;
        //ropes
        ofxBox2dJoint       rope_joint;
        ofxBox2dCircle      rope_anchor;
        //dog
        ttDog dog;
        ttDog dog2;
        //booleans
        bool                bSwing_left,bSwing_right;
        bool                bInSky_A,bInSky_B;
        //emoji
        ttEmoji emoji;
};


