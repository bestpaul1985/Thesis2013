#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    for (int i=0; i < 11; i++) {
        ofPoint p;
        p.set(0,0);
        touchesTopPre.push_back(p);
        touchesTop.push_back(p);
        touchesBotPre.push_back(p);
        touchesBot.push_back(p);
    }
    
	ofxAccelerometer.setup();
	ofBackground(30,30,30);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    
    
    myRope.setup();
    
    //********gameEvent**********************
    bFire = false;
    enemyKilled = 0;
    maxBullets = 30;
    pos.set(50, ofGetHeight()/2);
    
    ofVec2f p(650, 800);
    holes.push_back(p);

    bulletsNum = 15;
//    refillPos.set(20, 850);
    //********world**************************
    worldP1.init();
    worldP1.setGravity(0, 100);
    //  worldP1.createBounds();
    ofPoint one(0,ofGetHeight());
    ofPoint two(3000,ofGetHeight());
    worldP1.createGround(one, two);
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    worldP1.createBounds();
   
    worldP2.init();
    worldP2.setGravity(0, 100);
    worldP2.createGround(one, two);
    worldP2.setIterations(1, 1);
    worldP2.setFPS(60);
    worldP2.createBounds();
    
    
    //**********buttons****************
    bFixedButtonP1 = false;
    
    //***********map************************
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
                tempPolyline.setPhysics(0, 0, 0.2);
                tempPolyline.create(worldP1.getWorld());
                polyLines1.push_back(tempPolyline);
               
            }
            XML.popTag();
        }
    }
    
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
                tempPolyline.setPhysics(0, 0, 0.2);
                tempPolyline.create(worldP2.getWorld());
                polyLines2.push_back(tempPolyline);
                
            }
            XML.popTag();
        }
    }
    
    //***************character**********************************
    character1.setPhysics(3, 0, 0.5);
  
//    character1.setDensity();
//    character1.setBounce();
//    character1.setFriction();
    character1.setup(worldP1.getWorld(), 200, 500, 30,30);
    character1.body->SetFixedRotation(true);
    character1.setDamping(0.01f);
}


//--------------------------------------------------------------
void testApp::update(){
    
    if (ofGetFrameNum()<10){
        
        //set it to mirror if it isn't already
        
        if (!ofxiPhoneExternalDisplay::isMirroring()){
            
            //code from the internet to get it to mirror on exteral screens
            
            ofxiPhoneExternalDisplay::mirrorOn();
            
            ofxiPhoneExternalDisplay::isMirroring();
            
        }
    }
    
    myRope.update();
    myRope.headMoveToPos(character1.getPosition().x, character1.getPosition().y);
    
    //***********world*******************************
    worldP1.update();
    worldP2.update();

    //*********** diffP1 ********************************
    diffP1 = character1.getPosition()-lastPosP1;
    
    //***********character1*******************************
    ofPoint frc1(0,0);
    ofPoint frc2(0,0);
 
    
    character1.addForce(frc1,10);
    
    
    //*********** get lastPos ***************
    lastPosP1 = character1.getPosition();
    
    //*********** gameEvent******************
    
    
    
        if ((int)ofRandom(0,10)==1 && bulletsNum<30) {
            bulletsNum += 0.3;
            
        }
    
    
    
    
    //*********** Accelerometer *******************
    ofPoint gravity = ofxAccelerometer.getForce();
    float speedP1, speedP2;
    cout << gravity.y <<endl;
    
    if (gravity.y>0.3) {
        speedP1 = 0.01f;
    }else{
        speedP1 = -0.01f;}
    
    if (gravity.y< -0.3) {
        speedP2 = 0.01f;
    }else{
        speedP2 = -0.01f;
    }
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(242, 208, 59);
    for (int i=0; i<polyLines1.size(); i++) {
        polyLines1[i].draw();
    }
 
    
    ofSetColor(71, 217, 191);
	character1.draw();
    
    ofPushMatrix();
    ofTranslate(character1.getPosition().x+10, character1.getPosition().y+character1.getHeight());
    ofRotateZ(180);
    ofSetColor(31, 117, 151);
    float height = ofMap(bulletsNum, 0, 30, 0, character1.getHeight()*2);
    ofRect(0, 0, 20, height);
    ofPopMatrix();

    
    
    //*********gameEvents***************************************
    
    ofSetColor(245, 128, 146);
    myRope.draw();
//    ofRect(refillPos,50,10);
//
//    for(int i=0; i<holes.size(); i++) {
//        ofSetColor(0,48,86);
//        ofCircle(holes[i], 40);
//    }
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    myRope.headLock();
    
    ofRectangle top;
    ofRectangle bot;
    top.set(0, 0, ofGetWidth(), ofGetHeight()/2);
    bot.set(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    if (top.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesTopPre[touch.id] = p;
    }
    
    if (bot.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesBotPre[touch.id] = p;
    }
    
    
        
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    
    
    ofRectangle top;
    ofRectangle bot;
    top.set(0, 0, ofGetWidth(), ofGetHeight()/2);
    bot.set(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    if (top.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesTop[touch.id] = p;
    }
    
    if (bot.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesTop[touch.id] = p;
    }
    
    if (touch.y<300) {
        myRope.tailLock();
        myRope.tailMoveToPos(touch.x, touch.y);
    }
    else{
        myRope.tailUnlock();
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    myRope.headUnlock();
    
    ofRectangle top;
    ofRectangle bot;
    top.set(0, 0, ofGetWidth(), ofGetHeight()/2);
    bot.set(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    if (top.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesTop[touch.id] = p;
    }
    
    if (bot.inside(touch.x, touch.y)) {
        ofPoint p;
        p.set(touch.x, touch.y);
        touchesBot[touch.id] = p;
    }
    
    
    for (int i=0; i<11; i++) {
        ofPoint p;
        p =  touchesBot[i] - touchesBotPre[i];
        float radius = atan2(p.x, p.y);
        float angle = ofRadToDeg(radius);
        
//        cout<<angle<<endl;
        
        if (angle >= 10 && angle < 100) {
            ofPoint frc;
            frc.set(100, 0);
            character1.addForce(frc, 100);
        }else if(angle>= 100 && angle < 170){
            
            ofPoint frc;
            frc.set(100, 50);
            character1.addForce(frc, 100);
            
        }else if (angle < 0 && angle > -100){
            ofPoint frc;
            frc.set(-100, 0);
            character1.addForce(frc, 100);
        
        }else if (angle <= -100 && angle > -180) {
            ofPoint frc;
            frc.set(-100, 0);
            character1.addForce(frc, 100);
        }
       
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

