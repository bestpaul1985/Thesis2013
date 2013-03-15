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
class ttControl{

public:
    ttControl();
    void setup(int iCharNum);
    void draw();
    void touchDown(int x, int y, int TouchId);
    void touchMove(int x, int y, int TouchId);
    void touchUp(int x, int y, int TouchId);
    
    ofRectangle Directional_Touch_Area;
    ofPoint preTouchPos;
    ofPoint diff;
    
    float w;
    float h;
    float width;
    float height;
    float dis;
    float Swingdis;
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
