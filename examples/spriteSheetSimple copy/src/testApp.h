#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSpriteSheetRenderer.h"

static animation_t walkAnimation = {   0,  0,  20,  1,  1,  75, 0,  -1, -1, 1 };


struct basicSprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	
	ofxSpriteSheetRenderer * spriteRenderer;
	vector <basicSprite * > sprites;
};

#endif
