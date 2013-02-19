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
#include "dualWorld.h"
#include "ofxXmlSettings.h"

class challenge1 : public dualWorld{
public:
    
    void loadMap();
    
    //******** map **************************
    ofxXmlSettings XML;
    ofxXmlSettings XML2;
    string message;
    vector<ofxBox2dPolygon>     polyLines1;
    vector<ofxBox2dPolygon>     polyLines2;
    
};

#endif /* defined(__iPadInputExample__challenge1__) */
