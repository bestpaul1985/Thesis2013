#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxiPhoneExternalDisplay.h" 

#include "ofxBox2d.h"
#include "ofxXmlSettings.h"
#include "dirctiveButton.h"
#include "jumpButton.h"

#include "Enemy.h"
#include "Bullet.h"
#include "gameEvent.h"


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
        void gameEvent(GameEvent &e);
        
        static bool shouldRemoveBullet(Bullet &b);
        static bool shouldRemoveEnemy(Enemy &b);
        
        vector <Bullet> bullets;
        vector <Enemy> enemy;
        vector <ofVec2f> holes;
        
        int maxBullets;
        int enemyKilled;
        int bulletsNum;
        bool bFire;
        ofPoint pos;
        ofPoint refillPos;
        string message;
        //******** map **************************
        ofxXmlSettings              XML;
        vector<ofxBox2dPolygon>     polyLines1;
        vector<ofxBox2dPolygon>     polyLines2;
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

        vector<ofPoint>         touchesTop;
        vector<ofPoint>         touchesTopPre;
        vector<ofPoint>         touchesBot;
        vector<ofPoint>         touchesBotPre;

};


