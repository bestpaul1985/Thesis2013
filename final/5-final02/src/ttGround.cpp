//
//  ground.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttGround.h"


void ttGround::setup(int levelNum, int charNum, ofxBox2d &world){
    vector <string> strLines;
    levelNo = levelNum;
    charNo  = charNum;
    
	if (levelNo == 0) {
        if (charNo == 0 ) {
            ifstream f;
            f.open(ofToDataPath("levelTxt/level02_A.txt").c_str());
            
            while (!f.eof()) {
                string ptStr;
                getline(f, ptStr);
                strLines.push_back(ptStr);
            }
            f.close();
            
            
            ofDirectory dir;
            int nFiles = dir.listDir("sprites/bg/1A");
            if (nFiles) {
                for (int i= 0; i<dir.numFiles(); i++) {
                    string filePath = dir.getPath(i);
                    bgImg.push_back(ofImage());
                    bgImg.back().loadImage(filePath);
                }
            }
//            bgImg.loadImage("sprites/bg/slices/lv1_worldA_01.png");
        }
        
        if (charNo == 1) {
            ifstream f;
            f.open(ofToDataPath("levelTxt/level02_B.txt").c_str());
            while (!f.eof()) {
                string ptStr;
                getline(f, ptStr);
                strLines.push_back(ptStr);
            }
            f.close();
            
            
            ofDirectory dir;
            int nFiles = dir.listDir("sprites/bg/1B");
            if (nFiles) {
                for (int i= 0; i<dir.numFiles(); i++) {
                    string filePath = dir.getPath(i);
                    bgImg.push_back(ofImage());
                    bgImg.back().loadImage(filePath);
                }
            }
//            bgImg.loadImage("sprites/bg/lv1_worldB.png");
        }
    }
    
    
	for (int i=0; i<strLines.size(); i++) {
		vector <string> pts = ofSplitString(strLines[i], ",");
		if(pts.size() > 0) {
			ofxBox2dPolygon poly;
			for (int j=0; j<pts.size(); j+=2) {
				if(pts[j].size() > 0) {
					float x = ofToFloat(pts[j]);
					float y = ofToFloat(pts[j+1]);
					poly.addVertex(x, y);
				}
			}
            poly.setPhysics(0.0f, 0.0f, 0.1f);
			poly.create(world.getWorld());
			ground.push_back(poly);
		}
	}
    
    
}


void ttGround::draw(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255,255);
    for (int i = 0 ; i< bgImg.size(); i++) {
        if (levelNo == 1) {
//            float imgMul = bgImg[0].width*(ofGetHeight()/2)/bgImg[0].height;
            float imgMul = 483*(384)/386;
            if (charNo == 0) {
                ofSetColor(255,255);
                bgImg[i].draw(-410 + (imgMul*i)-i ,-250, imgMul, 384);
            }
            if (charNo == 1) {
                bgImg[i].draw(-410 + (imgMul*i)-i ,-133, imgMul, 384);
            }
        }
    }
}

void ttGround::drawPolyLine(){
    ofSetColor(ofColor::blueViolet);
    for (int i=0; i<ground.size(); i++) {
		ground[i].draw();
	}
}