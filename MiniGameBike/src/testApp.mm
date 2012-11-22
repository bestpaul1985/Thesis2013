#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);	
	ofBackground(30,30,30);
    // initialize the accelerometer
	ofxAccelerometer.setup();
    // initialize the bike object
    bikeWidth = 50;
    ofPoint p1(0,ofGetHeight()-bikeWidth/2);
    ofPoint p2(ofGetWidth(), ofGetHeight()-bikeWidth/2);
    bike.setInitialCondition(p1,p2,0.5, 1.0);
    bikePct = 0.5;
    lastTime = ofGetElapsedTimef();
    duration = 1.5;
    bDead = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (bDead ==false) {

        float speed = ofMap(ofxAccelerometer.getForce().x, -1, 1, -0.02, 0.02);
        bikePct+=speed;
        if (bikePct>1) {
            bikePct=1;
        }else if(bikePct<0){
            bikePct=0;
        }
        bike.interpolateByPct(bikePct);
        
        
        if (ofGetElapsedTimef()-lastTime>duration) {
            particle tempRock;
            ofPoint tempPosStart;
            ofPoint tempPosEnd;
            ofPoint diff;
            float scaler = 0.5;
            int which = ofRandom(0,3);
            tempPosStart.x = ofMap(which, 0, 2, ofGetWidth()/2-50, ofGetWidth()/2+50);
            tempPosStart.y = ofGetHeight()/2;
            tempPosEnd.x = ofMap(which, 0, 2, 150, ofGetWidth()-150);
            tempPosEnd.y=ofGetHeight();
            tempRock.setInitialCondition(tempPosStart.x, ofGetHeight()/2, 0, 2);
            rocks.push_back(tempRock);
            diff = tempPosEnd - tempPosStart;
            diff.normalize();
            diffs.push_back(diff*scaler);
            
            int which2 = ofRandom(0,3);
            
            if (which2 != which) {
                tempPosStart.x = ofMap(which2, 0, 2, ofGetWidth()/2-50, ofGetWidth()/2+50);
                tempPosStart.y = ofGetHeight()/2;
                tempPosEnd.x = ofMap(which2, 0, 2, 150, ofGetWidth()-150);
                tempPosEnd.y=ofGetHeight();
                tempRock.setInitialCondition(tempPosStart.x, ofGetHeight()/2, 0, 2);
                rocks.push_back(tempRock);
                diff = tempPosEnd - tempPosStart;
                diff.normalize();
                diffs.push_back(diff*scaler);
            }
            lastTime=ofGetElapsedTimef();
        }
        
      
        
        
        
        for (int i=0; i<rocks.size(); i++) {
            rocks[i].resetForce();
            rocks[i].addForce(diffs[i].x, diffs[i].y);
            rocks[i].addDampingForce();
            rocks[i].update();
            if (rocks[i].pos.y>ofGetHeight()) {
                rocks.erase(rocks.begin()+i);
                diffs.erase(diffs.begin()+i);
            }
        }
    
    }
    // judge if there is a collision
    for (int i=0; i<rocks.size(); i++) {
        float rectAx1, rectAx2, rectAy1, rectAy2;
        float rectBx1, rectBx2, rectBy1,rectBy2;
        float w = ofMap(rocks[i].pos.y, ofGetHeight()/2, ofGetHeight(), 10, 220);
        rectAx1 = rocks[i].pos.x-w/2;
        rectAx2 = rocks[i].pos.x+w/2;
        rectAy1 = rocks[i].pos.y-5;
        rectAy2 = rocks[i].pos.y+5;
        rectBx1 = bike.pos.x-bikeWidth/2;
        rectBx2 = bike.pos.x+bikeWidth/2;
        rectBy1 = bike.pos.y-25;
        rectBy2 = bike.pos.y+25;
        if (rectAx1 < rectBx2 && rectAx2 > rectBx1 &&
            rectAy1 < rectBy2 && rectAy2 > rectBy1) {
             bDead = true;
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 0, 220);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(bike.pos.x, bike.pos.y, bikeWidth, 50);
    for (int i=0; i<rocks.size(); i++) {
        float w = ofMap(rocks[i].pos.y, ofGetHeight()/2, ofGetHeight(), 10, 220);
        ofRect(rocks[i].pos.x, rocks[i].pos.y, w, 10);
    }
    
    
    ofPoint line1Start(0,ofGetHeight()/2);
    ofPoint line1End(ofGetWidth(),ofGetHeight()/2);
    ofPoint line2Start(ofGetWidth()/2,ofGetHeight()/2-30);
    ofPoint line2End(ofGetWidth()/2,ofGetHeight()/2+30);
    ofPoint intersection;
    ofLine(line1Start,line1End);
    ofLine(line2Start,line2End);
    ofLine(ofGetWidth()/2-50, ofGetHeight()/2, 50, ofGetHeight());
    ofLine(ofGetWidth()/2+50, ofGetHeight()/2, ofGetWidth()-50, ofGetHeight());
    ofLineSegmentIntersection(line1Start, line1End, line2Start, line2End, intersection);
    ofDrawBitmapString("Pos: "+ofToString(intersection)+"\nAceelerometer: "+ ofToString(ofxAccelerometer.getForce()), 100,100);
    
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if (touch.id == 0) {
        bDead = false;
    }
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

