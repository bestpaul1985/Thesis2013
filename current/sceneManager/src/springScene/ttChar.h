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
class ttChar{
public:
    void setup(ofxBox2d &characterWorld,
               ttControl &ctrl_A,
               ttControl &ctrl_B,
               ofPoint SetPos,
               int iCharNum);
    
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
    
    ofPoint         setPos;
    ofPoint         getPos;
    ofPoint         prePos;
    float           setWidth;
    float           setHeight;
    float           adjustedHeight;
    float           alpha;
    float           startTime;
    bool            bFixedMove;
    bool            bSwing;
    bool            mirrorLeft;
    bool            bReset;
    bool            bHookIt;
    bool            bDead;
    bool            bDestroyRect;
    int             charNum;
    int             step;
    int             deadStep;
    int             numFootContacts;
    int             jointSize;
    int             hold_Num;
    int             rectSize;
    ttControl       *control_A;
    ttControl       *control_B;
    vector<ofImage> sprite;
    
    ofxBox2dCircle  start;
    ofxBox2dJoint   joint;
    
    ofColor         color;
    
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
};

#endif /* defined(__thatThey__ttChar__) */
