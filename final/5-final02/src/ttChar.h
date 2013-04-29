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
static animation_t walkAnimation_boy = {   0,  0,  19,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t ropeAnimation_boy = {   24,  0,  7,  1,  1,  75, 0,  1, -1, 1 };

static animation_t walkAnimation_girl = {   0,  0,  24,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t ropeAnimation_girl = {   24,  0,  7,  1,  1,  75, 0,  1, -1, 1 };

struct basicSprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};


//-----------------------------------------------------------------------------
class ttChar{
public:
   
    
    _condition condition;
    
    void setup(ofxBox2d &world, ofPoint SetPos, int CharNum);
    void update();
    void draw();
    
    ofxBox2dRect    character;
    ofxSpriteSheetRenderer * spriteRenderer;
	vector <basicSprite * > sprites;
    
    bool moveLeft;
    ofPoint getPos;
    int charNum;
   
};

#endif /* defined(__thatThey__ttChar__) */