#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "character.h"


//create a new animation. This could be done optinally in your code andnot as a static, just by saying animation_t walkAnimation; walkAnimation.index =0, walkAnimation.frame=0 etc. I find this method the easiest though


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

character c;

};

#endif
