//
//  ground.h
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#ifndef __springBreak01__ttGround__
#define __springBreak01__ttGround__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttGroundVisual{
public:
    
    int x, y, w, h;
    void setup(int _x, int _y, float _w, float _h){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    void draw(){
        
        ofPushMatrix();
        ofTranslate(x, y);
        ofScale(w/200, h/30);
        
        ofFill();
        ofSetColor(255);
        ofBeginShape();
        ofVertex(0,0);
        ofVertex(55,-10);
        ofVertex(166,-7);
        ofVertex(200,0);
        ofVertex(168,11);
        ofVertex(49,19);
        ofVertex(0,0);
        ofEndShape();
        
        ofNoFill();
        ofSetColor(0);
        ofBeginShape();
        ofVertex(0,0);
        ofVertex(55,-10);
        ofVertex(166,-7);
        ofVertex(200,0);
        ofVertex(168,11);
        ofVertex(49,19);
        ofVertex(0,0);
        ofEndShape();
        ofPopMatrix();
        ofFill();
    }
};



class ttGround{
    public:
    void setup( int levelNum, int charNum, ofxBox2d &world);
    void draw();
    void drawPolyLine();
    void drawGroundShape(int x, int y, float w, float h);
    void destroy();
    vector <ofPolyline>			lines;
    vector <ofxBox2dPolygon>	ground;
    
    vector <ttGroundVisual> drawGround;
    int prevX, prevY;
    
    vector<ofImage> bgImg;
    int levelNo, charNo;
    string url[7];
    string imgs[7];
    
};

#endif /* defined(__springBreak01__ground__) */
