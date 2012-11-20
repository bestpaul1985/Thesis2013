#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "stepButton.h" 
#include "ofxBox2d.h"


#define N_STEPS 10


class Data {
public:
	int	 ID;
	bool bHit;
	bool bDestroy;
};

// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	CustomParticle() {
	}
	ofColor color;
	vector		<ofxBox2dJoint>		joints;	
	void draw() {
		float radius = getRadius();
		
		glPushMatrix();
		glTranslatef(getPosition().x, getPosition().y, 0);
		
		ofSetColor(color.r, color.g, color.b);
		ofFill();
		ofCircle(0, 0, radius);	
		
		glPopMatrix();
		
	}
};

//------------------------------

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
    
        //my stuff------------------------------------
		int rect_x;
		int rect_y;
		int rect_jianju;
		int rect_gaoju;
		int rect_size;

		int a;
		int b;
		int c;
		bool clicked;
	
	
	
	
	
		
        // metronome stuff
        float startTime;
        float intervalTime;
        int nTicks;
        bool bTick;
        
        float bpm;
        
        stepButton myStep[N_STEPS]; 
		stepButton myStep_1[N_STEPS]; 
		stepButton myStep_2[N_STEPS]; 
        
        ofSoundPlayer   kick; 
		ofSoundPlayer   hat;
		ofSoundPlayer   snare;
	
	
	//----------box2d-----------------------------------
	float							px, py;
	bool							bDrawLines;
	bool							bMouseForce;
	
	ofxBox2d						box2d;
	ofxBox2dPolygon					polyLine;

	float r;
					
	vector		<CustomParticle>	customParticles;
	vector		<CustomParticle>	customParticles1;

	vector		<ofxBox2dRect>		boxes;	
	//--------joints--------------------
	CustomParticle					anchor,anchor1;			  
	vector		<ofxBox2dCircle>	circles;		 
	vector		<ofxBox2dJoint>		joints;	
	
	
	//---contactslistener------
	
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);

};

#endif
