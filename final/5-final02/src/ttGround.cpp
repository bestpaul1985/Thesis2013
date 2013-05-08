//
//  ground.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttGround.h"


void ttGround::setup(int levelNum, int charNum, ofxBox2d &world){
   
    if (charNum == 0) {
        url[0] = "levelTxt/A/level1.txt";
        url[1] = "levelTxt/A/level2.txt";
        url[2] = "levelTxt/A/level3.txt";
        url[3] = "levelTxt/A/level4.txt";
        url[4] = "levelTxt/A/level5.txt";
        url[5] = "levelTxt/A/level6.txt";
        url[6] = "levelTxt/A/level6.txt";
        imgs[0] = "bg/ground/level01/A";
        imgs[1] = "bg/ground/level02/A";
        imgs[2] = "bg/ground/level03/A";
        imgs[3] = "bg/ground/level04/A";
        imgs[4] = "bg/ground/level05/A";
        imgs[5] = "bg/ground/level06/A";
        imgs[6] = "bg/ground/level07/A";
    }
    else{
        url[0] = "levelTxt/B/level1.txt";
        url[1] = "levelTxt/B/level2.txt";
        url[2] = "levelTxt/B/level3.txt";
        url[3] = "levelTxt/B/level1.txt";
        url[4] = "levelTxt/B/level1.txt";
        url[5] = "levelTxt/B/level1.txt";
        url[6] = "levelTxt/B/level6.txt";
        imgs[0] = "bg/ground/level01/B";
        imgs[1] = "bg/ground/level02/B";
        imgs[2] = "bg/ground/level03/B";
        imgs[3] = "bg/ground/level01/B";
        imgs[4] = "bg/ground/level01/B";
        imgs[5] = "bg/ground/level01/B";
        imgs[6] = "bg/ground/level01/B";
    }
    
    vector <string> strLines;
    levelNo = levelNum;
    charNo  = charNum;
    
    ifstream f;
    f.open(ofToDataPath(url[levelNum]).c_str());
    
    while (!f.eof()) {
        string ptStr;
        getline(f, ptStr);
        strLines.push_back(ptStr);
    }
    f.close();
    
    
    ofDirectory dir;
    int nFiles = dir.listDir(imgs[levelNum]);
    if (nFiles) {
        for (int i= 0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            bgImg.push_back(ofImage());
            bgImg.back().loadImage(filePath);
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
    ofSetColor(255,255);
    for (int i = 0 ; i< bgImg.size(); i++) {
        if (charNo == 0) {
            bgImg[i].draw(-512 + 1024*i, -384);
        }
        if (charNo == 1) {
            bgImg[i].draw(-512 + 1024*i, 384-bgImg[i].getHeight());
        }
    }
    
}

void ttGround::drawPolyLine(){
    ofSetColor(ofColor::blueViolet);
    for (int i=0; i<ground.size(); i++) {
		ground[i].draw();
	}
}


void ttGround::destroy(){
    bgImg.clear();
    for (int i=0; i<ground.size(); i++) {
        ground[i].destroy();
    }
}




