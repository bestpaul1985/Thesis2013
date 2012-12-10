//
//  xmlRecorder.h
//  emptyExample
//
//  Created by PengCheng on 11/1/12.
//
//

#ifndef __emptyExample__xmlRecorder__
#define __emptyExample__xmlRecorder__

#include "ofMain.h"
#include "ofxXmlSettings.h"
class xmlRecorder{

public:
    xmlRecorder();
    void addPoint(int x, int y, int attributevalue);
    void setInitialXml();
    void saveFile();
    void clear();
    ofxXmlSettings XML;

    string xmlStructure;
    vector<ofPoint> points;
    int lastTagNumber;

};

#endif /* defined(__emptyExample__xmlRecorder__) */
