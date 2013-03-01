//
//  challenge1.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__challenge1__
#define __iPadInputExample__challenge1__

#include <iostream>
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "baseWorld.h"

class challenge1 : public baseWorld{
public:
    
    void loadMap();
    void loadImage();
    void loadSound();
    
    // background images
    ofImage                     bgImg;
    ofImage                     bgP1;
    ofImage                     bgP2;
    
    // background music
    ofSoundPlayer               bgm;
    
    // map
    ofxXmlSettings              XML;
    ofxXmlSettings              XML2;
    string                      message;
    vector<ofxBox2dPolygon>     polyLines1;
    vector<ofxBox2dPolygon>     polyLines2;
    
};

#endif /* defined(__iPadInputExample__challenge1__) */
