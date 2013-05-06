//
//  ground.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ttGround.h"


void ttGround::setup( int charNum, ofxBox2d &world){
    vector <string> strLines;
    charNo  = charNum;
    
	if (levelNo == 0) {
        if (charNo == 0 ) {
            ifstream f;
            f.open(ofToDataPath("levelTxt/level01_A.txt").c_str());
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
                    bgImg1.push_back(ofImage());
                    bgImg1.back().loadImage(filePath);
                }
            }
            //2
            ifstream f2;
            f2.open(ofToDataPath("levelTxt/level02_A.txt").c_str());
            
            while (!f2.eof()) {
                string ptStr;
                getline(f2, ptStr);
                strLines.push_back(ptStr);
            }
            f2.close();
            ofDirectory dir2;
            int nFiles2 = dir2.listDir("sprites/bg/2A");
            if (nFiles2) {
                for (int i= 0; i<dir2.numFiles(); i++) {
                    string filePath = dir2.getPath(i);
                    bgImg2.push_back(ofImage());
                    bgImg2.back().loadImage(filePath);
                }
            }
            
            ifstream f3;
            f3.open(ofToDataPath("levelTxt/level02_A.txt").c_str());
            
            while (!f3.eof()) {
                string ptStr;
                getline(f3, ptStr);
                strLines.push_back(ptStr);
            }
            f3.close();
            ofDirectory dir3;
            int nFiles3 = dir3.listDir("sprites/bg/2A");
            if (nFiles3) {
                for (int i= 0; i<dir3.numFiles(); i++) {
                    string filePath = dir3.getPath(i);
                    bgImg2.push_back(ofImage());
                    bgImg2.back().loadImage(filePath);
                }
            }

        }
        
        if (charNo == 1) {
            ifstream f;
            f.open(ofToDataPath("levelTxt/level01_B.txt").c_str());
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
                    bgImg0.push_back(ofImage());
                    bgImg0.back().loadImage(filePath);
                }
            }
            
            ifstream f1;
            f1.open(ofToDataPath("levelTxt/level01_B.txt").c_str());
            while (!f.eof()) {
                string ptStr;
                getline(f1, ptStr);
                strLines.push_back(ptStr);
            }
            f1.close();
            
            
            ofDirectory dir1;
            int nFiles1 = dir1.listDir("sprites/bg/1B");
            if (nFiles1) {
                for (int i= 0; i<dir1.numFiles(); i++) {
                    string filePath = dir1.getPath(i);
                    bgImg1.push_back(ofImage());
                    bgImg1.back().loadImage(filePath);
                }
            }
            
            ifstream f2;
            f2.open(ofToDataPath("levelTxt/level01_B.txt").c_str());
            while (!f2.eof()) {
                string ptStr;
                getline(f2, ptStr);
                strLines.push_back(ptStr);
            }
            f2.close();
            
            
            ofDirectory dir2;
            int nFiles2 = dir2.listDir("sprites/bg/1B");
            if (nFiles2) {
                for (int i= 0; i<dir2.numFiles(); i++) {
                    string filePath = dir2.getPath(i);
                    bgImg1.push_back(ofImage());
                    bgImg1.back().loadImage(filePath);
                }
            }
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


void ttGround::draw(int levelNum){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255,255);
    
    

   
    if (levelNum == 0) {
        for (int i = 0 ; i< bgImg0.size(); i++) {
    //            float imgMul = bgImg[0].width*(ofGetHeight()/2)/bgImg[0].height;
            float imgMul = 483*(384)/386;
            if (charNo == 0) {
                ofSetColor(255,255);
                bgImg0[i].draw(-410 + (imgMul*i)-i ,-250, imgMul, 384);
            }
            if (charNo == 1) {
                bgImg0[i].draw(-410 + (imgMul*i)-i ,-133, imgMul, 384);
            }
        }
    }
    
    if (levelNum == 1) {
        for (int i = 0 ; i< bgImg1.size(); i++) {
            float imgMul = 483*(384)/386;
            if (charNo == 0) {
                ofSetColor(255,255);
                bgImg1[i].draw(-410 + (imgMul*i)-i ,-250, imgMul, 384);
            }
            if (charNo == 1) {
                bgImg1[i].draw(-410 + (imgMul*i)-i ,-133, imgMul, 384);
            }
        }
    }
    
    if (levelNum == 2) {
        for (int i = 0 ; i< bgImg2.size(); i++) {
            float imgMul = 483*(384)/386;
            if (charNo == 0) {
                ofSetColor(255,255);
                bgImg2[i].draw(-410 + (imgMul*i)-i ,-250, imgMul, 384);
            }
            if (charNo == 1) {
                bgImg2[i].draw(-410 + (imgMul*i)-i ,-133, imgMul, 384);
            }
        }
    }
}

void ttGround::drawPolyLine(int levelNum){
    ofSetColor(ofColor::blueViolet);
    if (levelNum == 0) {
        ground[0].draw();

    }
    if (levelNum == 1) {
        ground[1].draw();
        
    }
    if (levelNum == 1) {
        ground[1].draw();
        
    }
}







			
