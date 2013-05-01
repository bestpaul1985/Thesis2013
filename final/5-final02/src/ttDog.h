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
static animation_t run = {   0,  0,  16,  1,  1,  45, 0,  -1, -1, 1 };

struct basicSprite_dog {
	animation_t animation;
	ofPoint pos;
	float speed;
};

class ttDog{
public:
    void setup(ofxBox2d &world, float x, float y);
    void update();
    void draw();
    ofxBox2dRect dog;
    ofxSpriteSheetRenderer * spriteRenderer;
    vector <basicSprite_dog * > sprites;
};



#endif /* defined(__final02__ttDog__) */
