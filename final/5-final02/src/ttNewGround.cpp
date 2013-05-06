//
//  ttNewGround.cpp
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#include "ttNewGround.h"

void ttNewGround::setup(string url, ofxBox2d &World){
    world = &World;
    
    vector <string> strLines;
    ifstream f;
    f.open(ofToDataPath(url).c_str());
    
    while (!f.eof()) {
        string ptStr;
        getline(f, ptStr);
        strLines.push_back(ptStr);
    }
    f.close();
    
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
			poly.create(world->getWorld());
			ground = poly;
		}
	}
}



void ttNewGround::draw(){
    ofSetColor(30);
    if (ground.alive) {
        ground.draw();
    }
}


void ttNewGround::destroy(){
    ground.destroy();
}











