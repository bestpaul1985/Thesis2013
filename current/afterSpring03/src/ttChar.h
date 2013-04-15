//
//  ttChar.h
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttSetData.h"
#include "ttControl.h"
#include "ttRope.h"
class ttChar{
public:
    void setup(ofxBox2d &characterWorld,
               ttControl &ctrl,
               ofPoint SetPos,
               ofPoint &Acc,
               int iCharNum);
    
    void moveLeft();
    void moveRight();
    void update();
    void draw();
    void copyRope(vector<ofxBox2dRect> Rects, vector<b2RevoluteJoint*> Joints, ofPoint screen);
    void initializeRope(ofPoint charPos, ofPoint screen);
    void controlRope();
    void destroyRope();
    void destroyRect();
    void swing();
    void drawBox2dObject();
    void dead();
    void drawRope();
    
    ofxBox2dRect    character;
    ofxBox2d        world;
    ttRope          *rope;
    
    ofPoint         setPos;
    ofPoint         getPos;
    ofPoint         prePos;
    ofPoint         *accFroce;
    float           setWidth;
    float           setHeight;
    float           adjustedHeight;
    float           alpha;
    float           startTime;
    bool            bFixedMove;
    bool            bSwing;
    bool            bInSky;
    bool            mirrorLeft;
    bool            bReset;
    bool            bHookIt;
    bool            bDead;
    bool            bDestroyRect;
    bool            bAccLeft;
    bool            bAccRight;
    bool            bDouPressed;
    bool            bRopeInControl;
    int             charNum;
    int             step;
    int             deadStep;
    int             numFootContacts;
    int             jointSize;
    int             hold_Num;
    int             rectSize;
    
    ttControl       *control;
    vector<ofImage> walkSprite, hangSprite, pullSprite;
    
    ofxBox2dCircle  start;
    ofxBox2dJoint   joint;
    
    ofColor         color;
    
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
};

#endif /* defined(__thatThey__ttChar__) */
