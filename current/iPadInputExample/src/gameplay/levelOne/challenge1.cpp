//
//  challenge1.cpp
//  iPadInputExample
//
//  Created by Firm Read on 2/17/13.
//
//

#include "challenge1.h"
void challenge1::loadMap(){
    
    if (XML.loadFile("tutorialLevelP1.xml")) {
        int strokeNum = XML.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML.pushTag("STROKE",i);
            int ptNum = XML.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML.getValue("PT:X", 0, j);
                    int y = XML.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2f);
                tempPolyline.create(world.getWorld());
                polyLines.push_back(tempPolyline);
            }
            XML.popTag();
        }
    }
    
    
}