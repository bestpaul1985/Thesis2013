//
//  ttBirds.h
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#ifndef __final02__ttBirds__
#define __final02__ttBirds__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttChar.h"

static animation_t _bird_fly = {   0,  0,  15,  1,  1,  75, 0,  -1, -1, 1 };

enum _bird_condition{
    BIRD_FLY,
    BIRD_ATTACK,
    BIRD_DEAD,
};


struct basicSprite_ttBirds {
	animation_t animation;
	ofPoint pos;
	float speed;
};

class ttBirds{
public:
    void setup(ofxBox2d &World,ofxSpriteSheetRenderer *render,ttChar &Target,float x, float y,int num);
    void update();
    void draw();
    void fly();
    
    _bird_condition                     condition;
    ofxBox2d                            *world;
    ofxBox2dCircle                      bird;
    ofxSpriteSheetRenderer *            spriteRenderer;
    vector <basicSprite_ttBirds * >     sprites;
    ofPoint                             frc;
    ofPoint                             getPos;
    
    ofRectangle                         killZone;
    ttChar                              *target;
    int                                 birdNum;
    bool                                flip;
};

#endif /* defined(__final02__ttBirds__) */
