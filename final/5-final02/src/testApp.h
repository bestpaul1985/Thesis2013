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
#include "ttEmoji.h"
#include "ttRope.h"
#include "ttRabit.h"
#include "mainMenu.h"
#include "inGameMenu.h"
#include "ttCatchgame.h"
#include "ttBirds.h"
enum game_condition {
    MAIN_MEUN,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
};

class testApp : public ofxiPhoneApp{
    public:
        void setup();
        void update();
        void draw();
        void exit();
        
        void drawScene(int level);
    
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
        void position(int level);
        void gamePlay(int level);
        void gameEnd(int level);
        game_condition condition;
    
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
        //mainMenu
        ofImage logo;
        ofImage mainMenuText;
        //gameMenu
        mainMenu main_menu;
        inGameMenu game_menu;
        //thorns
        ttThorn             thorns_A, thorns_B;
        //sky
        ttSky               sky;
        ofImage             skyBg;
        //Indictor
        ttIndicator         accIndictor;
        //rope
        ttRope rope_A, rope_B;
        //dog
        vector<ttDog>  dog_A;
        vector<ttDog>  dog_B;
        //rabit
        vector<ttRabit> rabit_A;
        vector<ttRabit> rabit_B;
        //rabit
        vector<ttBirds> birds_A;
        vector<ttBirds> birds_B;
        //booleans
        bool                bInSky_A,bInSky_B;
        bool                bStatistics;
        bool                levelOver_A, levelOver_B;
        bool                levelRester;
        //emoji
        ttEmoji emoji_A,emoji_B;
        ofImage image[5];
        //fonttype
        ofTrueTypeFont font;
        //render
        ofxSpriteSheetRenderer *rabit_Render;
        ofxSpriteSheetRenderer *dog_Render;
        ofxSpriteSheetRenderer *char_Render[5];
        ofxSpriteSheetRenderer *bird_Render;
        //gameEnd;
        ofImage gameEnd_bg;
        ofTrueTypeFont gameEnd_font;
        //minigame
        ttCatchgame catchGame;
    
        int timer;
};


