//
//  challenge2.h
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#ifndef __iPadInputExample__challenge2__
#define __iPadInputExample__challenge2__

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

#endif /* defined(__iPadInputExample__challenge2__) */
