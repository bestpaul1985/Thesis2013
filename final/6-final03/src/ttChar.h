#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttSetData.h"

//-----------------------------------------------------------------------------
static animation_t GIRL_RUN =       {   0,  0,  6,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t GIRL_PUSH_ROPE = {   0,  0,  8,  1,  9,  75, 0,  1, -1, 1 };
static animation_t GIRL_HOOK_ROPE = { 24,  0,  7,  1,  1,  75, 0,  -1, -1, 1 };

static animation_t BOY_RUN =        {   0,  0,  13,  1,  2,  75, 0,  -1, -1, 1 };
static animation_t BOY_PUSH_ROPE =  {   0,  0,  8,  1,  9,  75, 0,  1, -1, 1 };
static animation_t BOY_HOOK_ROPE =  {   0,  0,  7,  1,  1,  75, 0,  -1, -1, 1 };

enum _char_condition{
    C_STOP,
    C_LEFT,
    C_RIGHT,
    C_PUSH_ROPE,
    C_SWING_ROPE,
    C_HOOK_ROPE,
    C_DEAD,
};


struct Sprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};
//-----------------------------------------------------------------------------
class ttChar{
public:
   
    _char_condition condition;
    
    void setup(ofxBox2d &world, ofPoint SetPos, int CharNum);
    void update();
    void draw();
    void dead();
    
    ofxBox2dRect    character;
    ofxSpriteSheetRenderer * spriteRenderer;
    ofxSpriteSheetRenderer * spriteRenderer2;
    ofxSpriteSheetRenderer * spriteRenderer3;
	Sprite * sprites[4];
    
    bool moveLeft;
    ofPoint getPos;
    int charNum;
    float angle;
    int step;
   
};

#endif /* defined(__thatThey__ttChar__) */