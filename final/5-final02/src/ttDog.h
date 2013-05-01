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
static animation_t RUN = {    0,  0,  6,  1,  0.71,  75, 0,  -1, -1, 1  };


struct DogSprite {
	animation_t animation;
	ofPoint pos;
};
class ttDog{
public:
    void setup(ofxBox2d &world, float x, float y);
    void update();
    void draw();
    ofxBox2dRect dog;
    ofxSpriteSheetRenderer * renderer;
    DogSprite *  sprites[1];

};



#endif /* defined(__final02__ttDog__) */
