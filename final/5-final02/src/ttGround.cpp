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
        url[0] = "levelTxt/A/level1var1A.txt";
        url[1] = "levelTxt/A/level1var2A.txt";
        url[2] = "levelTxt/A/level1var3A.txt";
        
        url[3] = "levelTxt/A/level2var1A.txt";
        url[4] = "levelTxt/A/level2var2A.txt";
        url[5] = "levelTxt/A/level2var3A.txt";

        url[6] = "levelTxt/A/level04_A.txt";
        
        imgs[0] = "bg/ground";
        imgs[1] = "bg/ground";
        imgs[2] = "bg/ground";
    }
    else{
        url[0] = "levelTxt/B/level1var1B.txt";
        url[1] = "levelTxt/B/level1var2B.txt";
        url[2] = "levelTxt/B/level1var3B.txt";
        
        url[3] = "levelTxt/B/level2var1B.txt";
        url[4] = "levelTxt/B/level2var2B.txt";
        url[5] = "levelTxt/B/level2var3B.txt";

        url[6] = "levelTxt/B/level04_B.txt";
        
        imgs[0] = "bg/1B";
        imgs[1] = "bg/1B";
        imgs[2] = "bg/1B";
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
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255,255);
    for (int i = 0 ; i< bgImg.size(); i++) {
        if (levelNo == 1) {
            float imgMul = bgImg[0].width*(ofGetHeight()/2)/bgImg[0].height;
 //            float imgMul = 483*(384)/386;
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


void ttGround::destroy(){
    bgImg.clear();
    for (int i=0; i<ground.size(); i++) {
        ground[i].destroy();
    }
}




