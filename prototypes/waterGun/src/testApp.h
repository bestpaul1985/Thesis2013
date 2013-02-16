#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#include "Enemy.h"
#include "Bullet.h"
#include "gameEvent.h"

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
    
        void gameEvent(GameEvent &e);
    
        static bool shouldRemoveBullet(Bullet &b);
        static bool shouldRemoveEnemy(Enemy &b);
   
        vector <Bullet> bullets;
        vector <Enemy> enemy;
        vector <ofVec2f> holes;
    
        int maxBullets;
        int enemyKilled;
        bool bFire;
        ofPoint pos;
    
       
};


