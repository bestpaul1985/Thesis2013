//
//  ttEmoji.h
//  springBreak05
//
//  Created by Firm Read on 4/10/13.
//
//

#ifndef __springBreak05__ttEmoji__
#define __springBreak05__ttEmoji__

#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"
static animation_t EMOJI_LOVE =         {  0,   1,  3,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_HAPPY =        {  24,  1,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_SURPRISE =     {  48,  1,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_LAUGHING =     {  72,  1,  1,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t EMOJI_ANGRY =        {  96,  1,  1,  1,  1,  75, 0,  -1, -1, 1 };

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

enum _emoji_step{
    S_START,
    S_WAIT,
    S_END,
};
class ttEmoji{
public:
    
    void setup();
    void update();
    void draw();
    void timer();
    emoji_Sprite * sprites[5];
    ofxSpriteSheetRenderer * renderer;
    _emoji_condition condition;
    
    float startTime;
    float duration;
    float alpha;
    float speed;
    _emoji_step step;
};
#endif /* defined(__springBreak05__ttEmoji__) */
