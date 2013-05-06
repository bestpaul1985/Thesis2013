//
//  ttRope.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttRope__
#define __final02__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttChar.h"
enum _rope_condition{
    R_NO_USE,
    R_PUSH,
    R_SWING,
    R_DESTROY,
    R_MINIGAME,
};

class ttRope{
public:
    void setup(ofxBox2d &_world_B,ttChar &_A, ttChar &_B,ofPoint &_rope_start_B,ofPoint &hook_start_A,ofPoint &hook_end_A,ofPoint &_accFrc, int CharNum);
    void update();
    void draw_swing(ofPoint screen_B);
    void draw_push();
    void draw_minigame(ofPoint End);
    ofxBox2d world_B;
    ttChar* A, *B;
    int charNum;
    _rope_condition condition;
    ofxBox2dJoint       rope_joint;
    ofxBox2dCircle      rope_anchor;
    float               hook_pct;
    bool                bSwing_left,bSwing_right;
    ofPoint             *rope_start;
    ofPoint             *hook_end;
    ofPoint             *hook_start;
    ofPoint             *accFrc;
    
};


#endif /* defined(__final02__ttRope__) */
