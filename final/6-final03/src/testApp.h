#define SCENE_NUMBER 5

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "baseScene.h"
#include "openingScene.h"
#include "springScene.h"
//example scenes
#include "circleScene.h"
#include "squareScene.h"
#include "imageScene.h"
#include "ofxSpriteSheetRenderer.h"
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
        void levelLoader();
    
        baseScene * scenes[SCENE_NUMBER];
        int currentScene;
    
        ofImage image[5];
        ofImage skyBg;
        ofImage cloud01;
        ofImage cloud02;
        ofImage cloud03;
        ofxSpriteSheetRenderer *dog_render;
        ofxSpriteSheetRenderer *rabit_render;
        ofxSpriteSheetRenderer *char_render[5];
        ofxBox2d            world_A,        world_B;
    };


