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
#include "baseWorld.h"
#include "ofxXmlSettings.h"

class challenge1 : public baseWorld{
public:
    
    void loadMap();
    
    //******** map **************************
    ofxXmlSettings XML;
    string message;
    vector<ofxBox2dPolygon>     polyLines;
    
};

#endif /* defined(__iPadInputExample__challenge1__) */
