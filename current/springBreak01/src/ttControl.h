//
//  ttControl.h
//  thatTheyClass
//
//  Created by PengCheng on 3/12/13.
//
//

#ifndef __thatTheyClass__ttControl__
#define __thatTheyClass__ttControl__

#include "ofMain.h"
#include "ttRope.h"

class ttControl{

public:
    ttControl();
    void setup(int iCharNum);
    void ropeInfo(ttRope &Rope_A, ttRope &Rope_B);
    void draw();
    void touchDown(int x, int y, int TouchId);
    void touchMove(int x, int y, int TouchId);
    void touchUp(int x, int y, int TouchId);
    
    ofRectangle Directional_Touch_Area;
    ofPoint preTouchPos;
    ofPoint diff;

    ttRope *rope_A;
    ttRope *rope_B;
    float w;
    float h;
    float width;
    float height;
    float dis;
    int charNum;
    bool bLeft;
    bool bRight;
    bool bSmallLeft;
    bool bSmallRight;
    
    bool bSwingLeft;
    bool bSwingRight;
    int touchId;
   
};

#endif /* defined(__thatTheyClass__ttControl__) */
