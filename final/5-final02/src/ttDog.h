//
//  ttDog.h
//  final02
//
//  Created by PengCheng on 4/30/13.
//
//

#ifndef __final02__ttDog__
#define __final02__ttDog__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttChar.h"
static animation_t _dog_run = {   0,  0,  15,  1,  1,  75, 0,  -1, -1, 1 };
enum _dog_condition{
    D_RUN,
    D_BITE,
};


struct basicSprite_dog {
	animation_t animation;
	ofPoint pos;
	float speed;
};

class ttDog{
public:
    void setup(ofxBox2d &world,ofxSpriteSheetRenderer *render,ttChar &Target,float x, float y,int num);
    void update();
    void draw();
    void run();
    
    
    
    ofxBox2dCircle                  dog;
    ofxSpriteSheetRenderer *        spriteRenderer;
    vector <basicSprite_dog * >     sprites;
    ofPoint                         frc;
    bool                            flip;
    ofPoint                         getPos;
    _dog_condition                  condition;
    ofRectangle                     killZone;
    ttChar                          *target;
    int                             dogNum;
};
#endif /* defined(__final02__ttDog__) */




















