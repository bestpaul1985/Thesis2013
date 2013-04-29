#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttControl.h"

enum _condition
{
    C_STOP,
    C_LEFT,
    C_RIGHT,
    C_PUSH_ROPE,
    C_HOOK_ROPE,
};
//-----------------------------------------------------------------------------
static animation_t walkAnimation = {   0,  0,  24,  1,  1,  45, 0,  -1, -1, 1 };
static animation_t ropeAnimation = {   25,  0,  6,  1,  1,  45, 0,  1, -1, 1 };

struct basicSprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};


//-----------------------------------------------------------------------------
class ttChar{
public:
   
    
    _condition condition;
    void setup(ofxBox2d &world, ofPoint SetPos, int charNum);
    void update();
    void draw();
    
    ofxBox2dRect    character;
    ofxSpriteSheetRenderer * spriteRenderer;
	vector <basicSprite * > sprites;
    
    bool moveLeft;
   
};

#endif /* defined(__thatThey__ttChar__) */