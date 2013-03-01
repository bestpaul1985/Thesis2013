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
                tempPolyline.create(world1.getWorld());
                polyLines1.push_back(tempPolyline);
            }
            XML.popTag();
        }
    }
    if (XML2.loadFile("tutorialLevelP2.xml")) {
        int strokeNum = XML2.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML2.pushTag("STROKE",i);
            int ptNum = XML2.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML2.getValue("PT:X", 0, j);
                    int y = XML2.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2f);
                tempPolyline.create(world2.getWorld());
                polyLines2.push_back(tempPolyline);
            }
            XML2.popTag();
        }
    }
    
}

void challenge1::loadImage(){
    bgImg.loadImage("image/back.jpg");
    bgP1.loadImage("image/terraingrey.png");
    bgP2.loadImage("image/terrainbrown.png");
}

void challenge1::loadSound(){
    bgm.loadSound("sound/takkreverse.wav");
    bgm.setLoop(true);
    bgm.play();
    bgm.setVolume(0.5f);
}


