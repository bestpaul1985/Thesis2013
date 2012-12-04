#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
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
        ofxBox2dRect b2dPlayerA;
        //----------player2
        ofxBox2dRect b2dPlayerB;
        //----------UI A
        bool                bGoleftA,bGoRightA,bJumpedA,bOntheWallA;
        ofRectangle         button1A,button2A,button3A;
        ofColor             bc1A,bc2A,bc3A;
        ofPoint             lastPlayerPosA;
    
        //----------UI B
        bool                bGoleftB,bGoRightB,bJumpedB,bOntheWallB;
        ofRectangle         button1B,button2B,button3B;
        ofColor             bc1B,bc2B,bc3B;
        ofPoint             lastPlayerPosB;
    
        //----------Box2d
        ofxBox2d            worldA;
        ofxBox2d            worldB;
        ofxBox2dRect        ground;
        //----------Background
        ofxBox2dPolygon     polyLine;
        ofxBox2dPolygon     polyLine2;
        ofxBox2dPolygon     polyLine3;
        ofxBox2dPolygon     polyLine4;
        ofxBox2dPolygon     polyLine5;
        ofxBox2dPolygon     polyLine6;
    
        //-------Items
        ofRectangle        item1;
        int itemState1;
        float h;

};


