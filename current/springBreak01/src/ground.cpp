//
//  ground.cpp
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#include "ground.h"


void ground::setup(string levelTxt, ofxBox2d &world){
    ifstream f;
	f.open(ofToDataPath(levelTxt).c_str());
	vector <string> strLines;
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
			poly.create(world.getWorld());
			ground.push_back(poly);
		}
	}
}


void ground::draw(){
    
    for (int i=0; i<ground.size(); i++) {
		ground[i].draw();
	}
}