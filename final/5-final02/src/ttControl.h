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
    
    void setup();
    void draw();
    void touchDown(int x, int y, int TouchId);
    void touchMove(int x, int y, int TouchId);
    void touchUp(int x, int y, int TouchId);
    
    ofRectangle Directional_Touch_Area, rope_Area;
    ofPoint preTouchPos;
    ofPoint diff;
    
    ofPoint orgPos[4];
    int  RAD;
    bool bTouch[4];
    int touchID[4];
    bool bAllTouch;
  
   
};

#endif /* defined(__thatTheyClass__ttControl__) */
