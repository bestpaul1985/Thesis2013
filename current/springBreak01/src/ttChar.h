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
#include "ttRopeJoint.h"
#include "ttControl.cpp"
class ttChar{
public:
    ttChar();
    void setup(ofxBox2d &characterWorld,
               ofxBox2d&dummyWorld,
//               ttControl&cont,
               ofPoint &Move,
               bool &smallLeft,
               bool &smallRight,
               bool &left,
               bool &right,
               ofPoint SetPos,
               int iCharNum);
    void update();
    void draw();

    ofxBox2dRect    character;
    ofxBox2dRect    Dummy;
    ttControl       *control;
    ofPoint         setPos;
    ofPoint         getPos;
    ofPoint          *move;
    
    float           setWidth;
    float           setHeight;
    
    bool           *bLeft;
    bool           *bRight;
    bool           *bSmallLeft;
    bool           *bSmallRight;
    bool           bFixedMove;
    int            charNum;
    
   
};

#endif /* defined(__thatThey__ttChar__) */
