//
//  ttRabit.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttRabit__
#define __final02__ttRabit__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"

enum rabit_condition{
    RB_RUN,
    RB_STAND,
    RB_STOP,
};

static animation_t animation_run = {   0,  0,  21,  2,  3,  75, 0,  -1, -1, 1 };
static animation_t animation_stand = {   22,  0,  3,  2,  3,  75, 0,  -1, -1, 1 };
static animation_t animation_stop = {   0,  0,  1,  2,  3,  75, 0,  -1, -1, 1 };

struct basicSprite_rabit {
	animation_t animation;
	ofPoint pos;
	float speed;
};
//-------------------------------------------
class ttRabit{
public:
    
    void setup(ofxBox2d *world,ofxSpriteSheetRenderer *render, float x, float y,int num);
    void update();
    void draw();
    void run();
    
    ofxBox2dCircle                  rabit;
    ofxSpriteSheetRenderer *        rabitRender;
    vector <basicSprite_rabit*>     rabitSprites;
    ofPoint                         frc;
    bool                            flip;
    ofPoint                         getPos;
    rabit_condition                 condition;
    ofRectangle                     detectZone;
    int                             rabitNum;
};


#endif /* defined(__final02__ttRabit__) */
