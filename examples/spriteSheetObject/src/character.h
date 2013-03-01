//
//  character.h
//  spriteSheetExample
//
//  Created by PengCheng on 3/1/13.
//
//

#ifndef __spriteSheetExample__character__
#define __spriteSheetExample__character__

#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"
static animation_t walkAnimation =
{	0,	/* .index			(int) - this is the index of the first animation frame. indicies start at 0 and go left to right, top to bottom by tileWidth on the spriteSheet		*/
    0,	/* .frame			(int) - this is the current frame. It's an internal variable and should always be set to 0 at init													*/
    4,	/* .totalframes		(int) - the animation length in frames																												*/
    1,	/* .width			(int) - the width of each animation frame in tiles																									*/
    1,	/* .height			(int) - the height of each animation frame in tiles																									*/
    200,	/* .frameduration	(unsigned int) - how many milliseconds each frame should be on screen. Less = faster																*/
    0,	/* .nexttick		(unsigned int) - the next time the frame should change. based on frame duration. This is an internal variable and should always be set to 0 at init	*/
    -1,	/* .loops			(int) - the number of loops to run. -1 equals infinite. This can be adjusted at runtime to pause animations, etc.									*/
    -1,	/* .finalindex		(int) - the index of the final tile to draw when the animation finishes. -1 is the default so total_frames-1 will be the last frame.				*/
    1	/* .frameskip		(int) - the incrementation of each frame. 1 should be set by default. If you wanted the animation to play backwards you could set this to -1, etc.	*/
};

//a quick and dirty sprite implementation
struct basicSprite {
    animation_t animation;	// a variable to store the animation this sprite uses
    ofPoint pos;			// the position on the screen this sprite will be drawn at
    float speed;			// the speed at which this sprite moves down the screen
};


class character{

public:
    void initialization();
    void update();
    void draw();
    
    ofxSpriteSheetRenderer * spriteRenderer;	// our spriteRenderer
	vector<basicSprite *> sprites;
    
    
private:
    
  

};



#endif /* defined(__spriteSheetExample__character__) */
