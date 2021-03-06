#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();	
    ofBackground(30,30,30);
    ofxAccelerometer.setup();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    // initialize the bike object
    bikeWidth = 50;
    ofPoint p1(0,ofGetHeight()-bikeWidth/2);
    ofPoint p2(ofGetWidth(), ofGetHeight()-bikeWidth/2);
    bike.setInitialCondition(p1,p2,0.5, 1.0);
    bikePct = 0.5;
    lastTime1 = ofGetElapsedTimef();
    lastTime2 = ofGetElapsedTimef();
    duration1 = 1.5;
    duration2 = 2;
    bDead = false;
    
    //butterflies
    //here to set the net
    wind.set(0.03,-0.03,0.05);
    RepulsionForce.set(3, 0.1f);
    float springiness = 0.01f;
    float distance = 5;
    dump = 0.1f;
    
    // spring for the panel
    particle myParticle;
    myParticle.setInitialCondition(384,256,0,0);
    BFparticles.push_back(myParticle);
    myParticle.setInitialCondition(384+200,256,0,0);
    BFparticles.push_back(myParticle);
    
	
	BFparticles[0].bFixed = true;
	
	for (int i = 1; i < BFparticles.size(); i++){
		spring mySpring;
		mySpring.distance		= 100;
		mySpring.springiness	= 0.01f;
		mySpring.particleA = & (BFparticles[0]);
		mySpring.particleB = & (BFparticles[i]);
		BFsprings.push_back(mySpring);
	}
    
    bSpring = true;
    angle=0;
    
    // for the net
    float x = 125*-sin(ofDegToRad(angle));
    float y = 125*cos(ofDegToRad(angle));
    ofSetColor(0, 220, 255);
    netFirst.set(x, y); // set first point
    x = 175*-sin(ofDegToRad(angle));
    y = 175*cos(ofDegToRad(angle));
    netLast.set(x, y); //set last point
    
    particle tempParticle;
    tempParticle.setInitialCondition(netFirst.x, netFirst.y, 0, 0);
    nets.push_back(tempParticle);
    
    for (int i = 0; i < 6; i++){
		particle myParticle;
		float x =  10 * cos ( (i / 10.0) * TWO_PI);
		float y =  10 * sin ( (i / 10.0) * TWO_PI);
		myParticle.setInitialCondition(x,y ,0,0);
        myParticle.damping = dump;
		nets.push_back(myParticle);
	}
    
    tempParticle.setInitialCondition(netLast.x, netLast.y, 0, 0);
    nets.push_back(tempParticle);
    
    // set up the net's spring
    for (int i = 0; i < nets.size()-1; i++){
		spring mySpring;
		mySpring.distance		= distance;
		mySpring.springiness	= springiness;
		mySpring.particleA = & (nets[i]);
		mySpring.particleB = & (nets[(i+1)]);
		netSprings.push_back(mySpring);
	}
    
    
    //bfixed first and last points
    nets[0].bFixed=true;
    nets[nets.size()-1].bFixed=true;
    
    // butterflys
    tempParticle.setInitialCondition(-ofGetWidth()/2+100, ofGetHeight()/4-100, 0, 0);
    butterFlies.push_back(tempParticle);
    float tempAlpha = 255;
    alphas.push_back(tempAlpha);
    pct = 0;
    speed = 0.004f;
    duration = 1;
    lastTime = ofGetElapsedTimef();
    bPanel = true;
    orgPos.set(-ofGetWidth()/2, ofGetHeight()/4-115);
    finalPos.set(-10, ofGetHeight()/4-115);
    butterfliesPostion = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (bDead ==false) {
        // bike
        float speed = ofMap(ofxAccelerometer.getForce().x, -1, 1, -0.03, 0.03);
        bikePct+=speed;
        if (bikePct>1) {
            bikePct=1;
        }else if(bikePct<0){
            bikePct=0;
        }
        bike.interpolateByPct(bikePct);
        
        // obstacle1
        if (ofGetElapsedTimef()-lastTime1>duration1) {
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
            lastTime1=ofGetElapsedTimef();
        }
        // obstacle2
        duration2 = ofRandom(1.8,2.6);
        if (ofGetElapsedTimef()-lastTime2>duration2) {
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
            lastTime2=ofGetElapsedTimef();
        }
      
        //erase useless objects
        
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
    
    //here for butterflies
    //update the panel
    
    for (int i = 0; i < BFparticles.size(); i++){
        BFparticles[i].resetForce();
    }
    
    for (int i = 0; i < BFparticles.size(); i++){
        for (int j = 0; j < i; j++){
            BFparticles[i].addRepulsionForce(BFparticles[j], 20, 0.03);
        }
    }
    
    if (bSpring==true) {
        for (int i = 0; i < BFsprings.size(); i++){
            BFsprings[i].update();
        }
    }
    if (bPanel) {
        
        for (int i = 0; i < BFparticles.size(); i++){
            BFparticles[i].addDampingForce();
            BFparticles[i].update();
        }
    }
    
    //calculate the angle of the panel
    angle = RAD_TO_DEG*(BFparticles[1].pos.x)/80;
    
    
    //get the position of the points
    float x = 125*-sin(ofDegToRad(angle));
    float y = 125*cos(ofDegToRad(angle));
    ofSetColor(0, 220, 255);
    netFirst.set(x, y);
    x = 175*-sin(ofDegToRad(angle));
    y = 175*cos(ofDegToRad(angle));
    netLast.set(x, y);
    x = 138*-sin(ofDegToRad(angle+10));
    y = 138*cos(ofDegToRad(angle+10));
    ofPoint middlePoint(x, y);
    x = 150*-sin(ofDegToRad(angle));
    y = 150*cos(ofDegToRad(angle));
    
    
    //update the net
    nets[0].setInitialCondition(netFirst.x, netFirst.y, 0, 0);
    nets[nets.size()-1].setInitialCondition(netLast.x, netLast.y, 0, 0);
    
    for (int i = 0; i < nets.size(); i++){
        nets[i].resetForce();
    }
    
    for (int i = 0; i < nets.size(); i++){
        nets[i].addRepulsionForce(x, y, 30, 0.2f);
        for (int j = 0; j < i; j++){
            nets[i].addRepulsionForce(nets[j], RepulsionForce.x, RepulsionForce.y);
        }
    }
    
    for (int i = 0; i < netSprings.size(); i++){
        netSprings[i].update();
    }
    
    
    for (int i = 0; i < nets.size()/2; i++){
        nets[i].addForce(wind.x, wind.y);
        nets[i].addDampingForce();
        nets[i].update();
    }
    
    nets[nets.size()/2].addForce(wind.x, wind.y);
    nets[nets.size()/2].addDampingForce();
    nets[nets.size()/2].update();
    
    for (int i = nets.size()/2+1; i < nets.size(); i++){
        nets[i].addForce(wind.x, wind.y);
        nets[i].addDampingForce();
        nets[i].update();
    }
    
    
    // update butterFlies
    
    switch (butterfliesPostion) {
        case 0:{
            pct+=speed;
            butterFlies[0].pos.x= pct*finalPos.x+(1-pct)*orgPos.x;
            butterFlies[0].pos.y= pct*finalPos.y+(1-pct)*orgPos.y+15*sin(ofGetElapsedTimef()*10);
            vector<ofPoint> verts;
            for (int i=0; i<nets.size(); i++) {
                ofPoint temp;
                temp.set(nets[i].pos.x, nets[i].pos.y);
                verts.push_back(temp);
            }
            ofPolyline line;
            line.addVertices(verts);
            if (line.inside(butterFlies[0].pos.x-5, butterFlies[0].pos.y)) {
                bPanel = false;
                speed = 0;
                butterfliesPostion=3;
            }
            
            
            if(pct>1){
                pct=0;
                speed = 0;
                orgPos=finalPos;
                vector<ofPoint> postions;
                ofPoint tempPos;
                tempPos.set(0, -ofGetHeight()/4);
                postions.push_back(tempPos);
                tempPos.set(ofGetWidth()/2, -ofGetHeight()/4*3);
                postions.push_back(tempPos);
                tempPos.set(-ofGetWidth()/2, -ofGetHeight()/4*3);
                postions.push_back(tempPos);
                finalPos.set(postions[int(ofRandom(3))]);
                lastTime = ofGetElapsedTimef();
                butterfliesPostion=1;
            }
            
        }
            break;
            
        case 1:{
            pct+=speed;
            pct = powf(pct, 0.5);
            butterFlies[0].pos.x= pct*finalPos.x+(1-pct)*orgPos.x+25*-cos(ofGetElapsedTimef()*10);
            butterFlies[0].pos.y= pct*finalPos.y+(1-pct)*orgPos.y+15*sin(ofGetElapsedTimef()*10);
            vector<ofPoint> verts;
            for (int i=0; i<nets.size(); i++) {
                ofPoint temp;
                temp.set(nets[i].pos.x, nets[i].pos.y);
                verts.push_back(temp);
            }
            ofPolyline line;
            line.addVertices(verts);
            if (line.inside(butterFlies[0].pos.x-5, butterFlies[0].pos.y)) {
                bPanel = false;
                speed = 0;
                butterfliesPostion=3;
            }
            if (ofGetElapsedTimef()-lastTime>duration) {
                speed=0.01f;
                butterfliesPostion=2;
                
            }
        }
            break;
        case 2:{
            alphas[0]-=3;
            pct+=speed;
            butterFlies[0].pos.x= pct*finalPos.x+(1-pct)*orgPos.x+12*-cos(ofGetElapsedTimef()*15);
            butterFlies[0].pos.y= pct*finalPos.y+(1-pct)*orgPos.y+12*sin(ofGetElapsedTimef()*15);
            vector<ofPoint> verts;
            for (int i=0; i<nets.size(); i++) {
                ofPoint temp;
                temp.set(nets[i].pos.x, nets[i].pos.y);
                verts.push_back(temp);
            }
            ofPolyline line;
            line.addVertices(verts);
            if (line.inside(butterFlies[0].pos.x-5, butterFlies[0].pos.y)) {
                bPanel = false;
                speed = 0;
                butterfliesPostion=3;
            }
            if (pct>1) {
                speed = 0.004;
                finalPos = orgPos;
                orgPos.set(-ofGetWidth()/2, ofGetHeight()/4-115);
                pct = 0;
                alphas[0]=255;
                butterfliesPostion=0;
            }
        }
            break;
            
        case 3:{
            butterFlies[0].pos.x= pct*finalPos.x+(1-pct)*orgPos.x+7*cos(ofGetElapsedTimef()*50);
            butterFlies[0].pos.y= pct*finalPos.y+(1-pct)*orgPos.y+7*sin(ofGetElapsedTimef()*50);
            alphas[0]-=3;
            if(alphas[0]<0){
                alphas[0]=0;
                butterFlies.erase(butterFlies.begin()+0);
                alphas.erase(alphas.begin()+0);
                butterfliesPostion=4;
            }
            
        }
            break;
            
        case 4:{
            particle tempParticle;
            tempParticle.setInitialCondition(-ofGetWidth()/2+100, ofGetHeight()/4-100, 0, 0);
            butterFlies.push_back(tempParticle);
            float tempAlpha = 255;
            alphas.push_back(tempAlpha);
            pct = 0;
            speed = 0.004f;
            orgPos.set(-ofGetWidth()/2, ofGetHeight()/4-115);
            finalPos.set(ofRandom(-35,-25), ofGetHeight()/4-115);
            butterfliesPostion = 0;
            bPanel = true;
        }
            break;
            
            
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0, 220, 255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(bike.pos.x, bike.pos.y, bikeWidth, 50);
    ofSetColor(255, 0, 220);
    for (int i=0; i<rocks.size(); i++) {
        float w = ofMap(rocks[i].pos.y, ofGetHeight()/2, ofGetHeight(), 10, 220);
        ofRect(rocks[i].pos.x, rocks[i].pos.y, w, 10);
    }
    
    //butteflies
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/4);
        ofSetColor(0, 220, 255);
        ofLine(netLast.x, netLast.y, 0, 0);
        for(int i=0; i<netSprings.size();i++){
            netSprings[i].draw();
        }
        //  draw butterflies
        ofSetColor(255, 0, 220, alphas[0]);
        ofCircle(butterFlies[0].pos.x, butterFlies[0].pos.y, 10);
    ofPopMatrix();

    
    //layouts
    ofSetColor(220, 255, 0);
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
    

    if (touch.id==0&&touch.y<ofGetHeight()/2) {
        BFlastMouse.set(touch.x,touch.y);
        bSpring = false;
    }

    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    if (touch.id==0&&touch.y<ofGetHeight()/2) {
        ofPoint diff;
        if (BFlastMouse.x<touch.x) {
            diff.x= touch.x-BFlastMouse.x;
            diff.y = touch.y-BFlastMouse.y;
            float length = diff.length();
            float goback = ofMap(length, 0, 100, 0, 90, true);
            BFparticles[1].pos.x = 384 + 100 - goback;
            
        }
    }

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if (touch.id==0&&touch.y<ofGetHeight()/2) {
        bSpring = true;
    }
    
   
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    if (touch.y>ofGetHeight()/2) {
        bDead = false;
        rocks.clear();
        diffs.clear();
    }
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

