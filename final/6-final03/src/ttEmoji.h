//
//  ttEmoji.h
//  final03
//
//  Created by PengCheng on 5/3/13.
//
//

#ifndef __final03__ttEmoji__
#define __final03__ttEmoji__

#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"


static animation_t EMOJI_LOVE =         {  0,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_HAPPY =        {  24,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_SURPRISE =     {  48,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_LAUGHING =     {  72,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_ANGRY =        {  96,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };

struct emoji_Sprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};
enum _emoji_condition{
    E_NONE,
    E_LOVE,
    E_HAPPY,
    E_SURPRISE,
    E_LAUGHING,
    E_ANGRY,
};


class ttEmoji{
public:
    void setup();
    void update();
    void draw();
    
    emoji_Sprite * sprites[5];
    ofxSpriteSheetRenderer * renderer;
    _emoji_condition condition;
};


#endif /* defined(__final03__ttEmoji__) */
