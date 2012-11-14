#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "road.h"
#include "particle.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        road myRoad;
        ofxXmlSettings xml;
        ofImage bg;
        vector<ofPolyline> roadLayout;
        particle myCar;
        ofImage car;
        ofImage start;
        ofImage missionS;
        ofImage missionL;
        ofImage location;
        int gameStep;
        float savedTime;
        float totalTime;
        ofTrueTypeFont myFont1;
        ofTrueTypeFont myFont2;
        float pct;
};
