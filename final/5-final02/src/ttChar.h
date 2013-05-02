#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSpriteSheetRenderer.h"
#include "ttControl.h"
#include "ttSetData.h"

//-----------------------------------------------------------------------------
static animation_t GIRL_RUN =       {   0,  0,  24,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t GIRL_PUSH_ROPE = {   24,  0,  7,  1,  1,  75, 0,  1, -1, 1 };

static animation_t BOY_RUN =        {   0,  0,  19,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t BOY_PUSH_ROPE =  {   0,  0,  9,  1,  9,  75, 0,  1, -1, 1 };

enum _char_condition{
    C_STOP,
    C_LEFT,
    C_RIGHT,
    C_PUSH_ROPE,
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
	Sprite * sprites[2];
    
    bool moveLeft;
    ofPoint getPos;
    int charNum;
   
};

#endif /* defined(__thatThey__ttChar__) */