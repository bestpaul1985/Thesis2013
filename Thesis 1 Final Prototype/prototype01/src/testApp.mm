#include "testApp.h"
static int pts1[] = {0,1024-150,768/2,1024-150,768,1024-150};
static int nPts1  = 3*2;
static int pts2[] = {0,150,768/2,150,768,150};
static int nPts2  = 3*2;
//--------------------------------------------------------------
void testApp::setup(){	
	
	ofxAccelerometer.setup();
	ofEnableAlphaBlending();
	ofBackground(30,30,30);
    
    //***********box2d P1****************
    worldP1.init();
    worldP1.setGravity(0, 100);
    worldP1.createBounds();
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    for (int i=0; i<nPts1; i+=2) {
		float x = pts1[i];
		float y = pts1[i+1];
		polyLine1.addVertex(x, y);
	}
    polyLine1.setPhysics(0, 0, 0.2);
    polyLine1.create(worldP1.getWorld());
    
    //***********box2d P2****************
    worldP2.init();
    worldP2.setGravity(0, -100);
    worldP2.createBounds();
    worldP2.setIterations(1, 1);
    worldP2.setFPS(60);
    
    for (int i=0; i<nPts2; i+=2) {
		float x = pts2[i];
		float y = pts2[i+1];
		polyLine2.addVertex(x, y);
	}
    polyLine2.setPhysics(0, 0, 0.2);
    polyLine2.create(worldP2.getWorld());
    
    //**********buttons****************
    P1L.setup(10, ofGetHeight()-120, 0, 0);
    P1R.setup(20+115, ofGetHeight()-120, 1, 0);
    P1J.setup(ofGetWidth()-190, ofGetHeight()-115, 0, 0);
    P1F.setup(ofGetWidth()-105, ofGetHeight()-155, 1, 0);
    P2L.setup(ofGetWidth()-10-101, 120-95, 0, 180);
    P2R.setup(ofGetWidth()-20-101-115, 120-95, 1, 180);
    P2J.setup(190-96, 115-83, 0, 180);
    P2F.setup(105-77, 155-80,  1, 180);
    
    //********** Guy ******************
    myGuy.setup(chracater1.getPosition());
    chracater1.setPhysics(3, 0, 0.5);
    chracater1.setup(worldP1.getWorld(), ofGetWidth()/2, ofGetHeight()/2, myGuy.width/2, myGuy.height/2);
    chracater1.body->SetFixedRotation(true);
    //********** Girl *******************
    myGirl.setup(chracater2.getPosition());
    chracater2.setPhysics(3, 0, 0.5);
    chracater2.setup(worldP2.getWorld(), ofGetWidth()/2, ofGetHeight()/2, myGirl.width/2, myGirl.height/2);
    chracater2.body->SetFixedRotation(true);
}

//--------------------------------------------------------------
void testApp::update(){
    
    //*********** box2d P1*******************
    worldP1.update();
    ofPoint frc1(0,0);
    ofPoint frc2(0,0);
    if (P1L.bPressed) frc1.x = -100;
    if (P1R.bPressed) frc1.x = 100;
    chracater1.addForce(frc1,10);
    chracater1.setDamping(0.98f);
    
    //*********** box2d P2*******************
    worldP2.update();
    if (P2L.bPressed) frc2.x = 100;
    if (P2R.bPressed) frc2.x = -100;
    chracater2.addForce(frc2,10);
    chracater2.setDamping(0.98f);
    
    //*********** diffP1 *******************
    diffP1 = chracater1.getPosition()-lastPosP1;
    lastPosP1 = chracater1.getPosition();
    
    //*********** diffP2 *******************
    diffP2 = chracater2.getPosition()-lastPosP2;
    lastPosP2 = chracater2.getPosition();
    
    //*********** Guy *******************
    myGuy.update(chracater1.getPosition());
    
    //*********** Gril *******************
    myGirl.update(chracater2.getPosition());
}

//--------------------------------------------------------------
void testApp::draw(){
  
    
    
    myGuy.draw();
    myGirl.draw();
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    polyLine1.draw();
    polyLine2.draw();
    
    ofFill();
    ofSetColor(255, 255, 255,30);
    chracater1.draw();
    chracater2.draw();
    
   
    P1L.draw();
    P1R.draw();
    P1J.draw();
    P1F.draw();
    P2L.draw();
    P2R.draw();
    P2J.draw();
    P2F.draw();
   
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchDown(touch.x, touch.y, touch.id);
    P1R.touchDown(touch.x, touch.y, touch.id);    
    P1J.touchDown(touch.x, touch.y, touch.id);
    P1F.touchDown(touch.x, touch.y, touch.id);
    P2L.touchDown(touch.x, touch.y, touch.id);
    P2R.touchDown(touch.x, touch.y, touch.id);
    P2J.touchDown(touch.x, touch.y, touch.id);
    P2F.touchDown(touch.x, touch.y, touch.id);
    
    if (P1J.bPressed && fabs(diffP1.y)< 1) chracater1.setVelocity(0, -50);
    if (P2J.bPressed && fabs(diffP2.y)< 1) chracater2.setVelocity(0, 50);

   
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchMoved(touch.x, touch.y, touch.id);
    P1R.touchMoved(touch.x, touch.y, touch.id);
    P1J.touchMoved(touch.x, touch.y, touch.id);
    P1F.touchMoved(touch.x, touch.y, touch.id);
    P2L.touchMoved(touch.x, touch.y, touch.id);
    P2R.touchMoved(touch.x, touch.y, touch.id);
    P2J.touchMoved(touch.x, touch.y, touch.id);
    P2F.touchMoved(touch.x, touch.y, touch.id);

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    
    P1L.touchUp(touch.x, touch.y, touch.id);
    P1R.touchUp(touch.x, touch.y, touch.id);
    P1J.touchUp(touch.x, touch.y, touch.id);
    P1F.touchUp(touch.x, touch.y, touch.id);
    P2L.touchUp(touch.x, touch.y, touch.id);
    P2R.touchUp(touch.x, touch.y, touch.id);
    P2J.touchUp(touch.x, touch.y, touch.id);
    P2F.touchUp(touch.x, touch.y, touch.id);

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

