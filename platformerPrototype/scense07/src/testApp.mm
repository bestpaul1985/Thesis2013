#include "testApp.h"
static int pts1[] = {0,1024-150,768/2,1024-150,768,1024-150};
static int nPts1  = 3*2;

static int pts2[] = {0,150,768/2,150,768,150};
static int nPts2  = 3*2;

static int pts3[] = {0,800,130,800,160,800};;
static int nPts3  = 3*2;

static int pts4[] = {80,720,130,720,260,720,260, 1024-150};;
static int nPts4  = 4*2;
float a = 50;
static int pts5[] = {20+a,150,220+a,450,270+a,450};
static int nPts5  = 3*2;

static int pts6[] = {620+a,150,420+a,450,360+a,450};
static int nPts6  = 3*2;

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(30,30,30);
    ofEnableAlphaBlending();
    
 
    //************* Buttons A ***********
    bc1A.set(100, 0, 220);
    bc2A.set(100, 0, 220);
    bc3A.set(100, 0, 220);
    float w = 100;
    float h = 100;
    button1A.set(40, ofGetHeight()-h-30, w, h);
    button2A.set(60+w, ofGetHeight()-h-30, w, h);
    button3A.set(ofGetWidth()-140, ofGetHeight()-h-30,w, h);
    bGoleftA = false;
    bGoRightA = false;
    bJumpedA = false;
    bOntheWallA = true;
    //************* Buttons B ***********
    bc1B.set(100, 0, 220);
    bc2B.set(100, 0, 220);
    bc3B.set(100, 0, 220);
    w = 100;
    h = 100;
    button1B.set(ofGetWidth()-40-w, 30,  w, h);
    button2B.set(ofGetWidth()-70-2*w, 30, w, h);
    button3B.set(40, 30,w, h);
    bGoleftB = false;
    bGoRightB = false;
    bJumpedB = false;
    bOntheWallB = true;
    //********** box2d A ******************
    worldA.init();
    worldA.setGravity(0, 100);
//  worldA.registerGrabbing();
    worldA.createBounds();
    worldA.setIterations(1, 1);
    worldA.setFPS(60);
    
    //********** box2d B ******************
    worldB.init();
    worldB.setGravity(0, -100);
    //  worldB.registerGrabbing();
    worldB.createBounds();
    worldB.setIterations(1, 1);
    worldB.setFPS(60);
    
    //************* player A ***********
    b2dPlayerA.setPhysics(3, 0, 0.2);
    b2dPlayerA.setup(worldA.getWorld(),ofGetWidth()/2,ofGetHeight()/2,30,30);
    
    //************* player B ***********
    b2dPlayerB.setPhysics(3, 0, 0.2);
    b2dPlayerB.setup(worldB.getWorld(),ofGetWidth()/2,ofGetHeight()/2,30,30);
    
    //********** background A **************
    for (int i=0; i<nPts1; i+=2) {
		float x = pts1[i];
		float y = pts1[i+1];
		polyLine.addVertex(x, y);
	}
    polyLine.setPhysics(0, 0, 0.2);
    polyLine.create(worldA.getWorld());
    
    for (int i=0; i<nPts3; i+=2) {
		float x = pts3[i];
		float y = pts3[i+1];
		polyLine3.addVertex(x, y);
	}
    
    polyLine3.setPhysics(0, 0, 0.2);
    polyLine3.create(worldA.getWorld());
    
    for (int i=0; i<nPts4; i+=2) {
		float x = pts4[i];
		float y = pts4[i+1];
		polyLine4.addVertex(x, y);
	}
    
    polyLine4.setPhysics(0, 0, 0.2);
    polyLine4.create(worldA.getWorld());
    
    //********** background B **************
    for (int i=0; i<nPts2; i+=2) {
		float x = pts2[i];
		float y = pts2[i+1];
		polyLine2.addVertex(x, y);
	}
    polyLine2.setPhysics(0, 0, 0.2);
    polyLine2.create(worldB.getWorld());
   
    
    for (int i=0; i<nPts5; i+=2) {
		float x = pts5[i];
		float y = pts5[i+1];
		polyLine5.addVertex(x, y);
	}
    polyLine5.setPhysics(0, 0, 0.2);
    polyLine5.create(worldB.getWorld());
    
    for (int i=0; i<nPts6; i+=2) {
		float x = pts6[i];
		float y = pts6[i+1];
		polyLine6.addVertex(x, y);
	}
    polyLine6.setPhysics(0, 0, 0.2);
    polyLine6.create(worldB.getWorld());
    
    
    //********** items ***************
    h = 0;
    item1.set(15,830,30,30);
    itemState1 = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    worldA.update();
    worldB.update();
    //********* player A **********
    
    ofPoint frcA(0, 0);
    
    if (bGoleftA) {
        frcA.x = -100;
    }
    
    if (bGoRightA) {
        frcA.x = 100;
    }
   
    b2dPlayerA.addForce(frcA, 10);
    b2dPlayerA.setDamping(0.98f);
    //********* player B ********
    ofPoint frcB(0, 0);
    
    if (bGoleftB) {
        frcB.x = 100;
    }
    
    if (bGoRightB) {
        frcB.x = -100;
    }
    
    b2dPlayerB.addForce(frcB, 10);
    b2dPlayerB.setDamping(0.98f);
   
    //*********** postion different A *************
    ofPoint diffA = b2dPlayerA.getPosition() -lastPlayerPosA;
    
    if (diffA.length() != 0) {
      
    }
    
    if (fabs(diffA.y)<1){
        bOntheWallA = true;
    }else{
        bOntheWallA = false;
    }
    
    lastPlayerPosA = b2dPlayerA.getPosition();
    //*********** postion different B *************
    ofPoint diffB = b2dPlayerB.getPosition() -lastPlayerPosB;
    
    if (diffB.length() != 0) {
        
    }
    
    if (fabs(diffB.y)<1){
        bOntheWallB = true;
    }else{
        bOntheWallB = false;
    }
    
    lastPlayerPosB = b2dPlayerB.getPosition();
    
    
    //*********** Events A*****************
    switch (itemState1) {
        case 0:{
                ofPoint lenght;
                
                lenght.x = b2dPlayerA.getPosition().x - item1.x;
                lenght.y = b2dPlayerA.getPosition().y - item1.y;
                cout<<lenght.length()<<endl;

                if (lenght.length()<23) {
                    itemState1 = 1;
                }
            }
            break;
            
        case 1:{
            
            float frc;
            if(ofxAccelerometer.getForce().y > 0.1){
                frc = ofMap(ofxAccelerometer.getForce().y, 0.1, 1, 0, 20);
            }else{
                h = 0;
            }
            
            h+=frc;
            if (h> 680) {
                h = 680;
            }
            
                item1.set(b2dPlayerA.getPosition().x-15, b2dPlayerA.getPosition().y-15-h, 30, 30+h);
        }
            break;
            
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //********* middleLine **********
//    ofFill();
//    ofSetColor(214, 79, 42);
//    ofRect(0,ofGetHeight()/2-40, ofGetWidth(), 80);
//    
    //********* buttons A**********
    ofFill();
    if (bGoleftA) {
        bc1A.set(10, 0, 220, 125);
    }else{
        bc1A.set(100, 0, 220, 125);
    }
    
    if (bGoRightA) {
        bc2A.set(10, 0, 220, 125);
    }else{
        bc2A.set(100, 0, 220, 125);
    }
    
    if (bJumpedA) {
        bc3A.set(10, 0, 220, 125);
    }else{
        bc3A.set(100, 0, 220, 125);
    }
    ofSetColor(bc1A);
    ofRect(button1A);
    ofSetColor(bc2A);
    ofRect(button2A);
    ofSetColor(bc3A);
    ofRect(button3A);
    //********* buttons B **********
    ofFill();
    if (bGoleftB) {
        bc1B.set(10, 0, 220, 125);
    }else{
        bc1B.set(100, 0, 220, 125);
    }
    
    if (bGoRightB) {
        bc2B.set(10, 0, 220, 125);
    }else{
        bc2B.set(100, 0, 220, 125);
    }
    
    if (bJumpedB) {
        bc3B.set(10, 0, 220, 125);
    }else{
        bc3B.set(100, 0, 220, 125);
    }
    ofSetColor(bc1B);
    ofRect(button1B);
    ofSetColor(bc2B);
    ofRect(button2B);
    ofSetColor(bc3B);
    ofRect(button3B);
    
    //********* b2dplayer A**********
    ofFill();
    ofSetColor(52, 93, 106);
//    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofRect(b2dPlayerA.getPosition(), 80, 80);
//    ofSetRectMode(OF_RECTMODE_CORNER);
    b2dPlayerA.draw();
    //********* b2dplayer A**********
    ofFill();
    ofSetColor(52, 93, 106);
    b2dPlayerB.draw();
    //********* polylines A **********
    ofNoFill();
    ofSetColor(214, 79, 42);
    polyLine.draw();
    
    ofNoFill();
    ofSetColor(122, 138, 127);
    polyLine3.draw();
    polyLine4.draw();
    //********* polylines B **********
    ofNoFill();
    ofSetColor(214, 79, 42);
    polyLine2.draw();
    
    ofNoFill();
    ofSetColor(122, 138, 127);
    polyLine5.draw();
    polyLine6.draw();
	//******** Item 1 ************
    ofFill();
    ofSetColor(158,190,166);
    ofRect(item1);
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
    
    
    
    
    
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    if(rect3.inside(touch.x, touch.y)){
        touch.id = 2;
    };
    
    if(rect4.inside(touch.x, touch.y)){
        touch.id = 3;
    };

    
    //********* left ************

    if (touch.id ==0&& button1A.inside(touch.x, touch.y)) {
        bGoleftA = true;
    }
    
    if (touch.id ==3&& button1B.inside(touch.x, touch.y)) {
        bGoleftB = true;
    }
    //********* right ************
    
    if (touch.id ==0&& button2A.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }
    
    if (touch.id ==3&& button2B.inside(touch.x, touch.y)) {
        bGoRightB = true;
    }
    
    
    //********* jump ************
    if (touch.id == 1&& button3A.inside(touch.x, touch.y)&& bJumpedA==false&& bOntheWallA == true) {
        b2dPlayerA.setVelocity(b2dPlayerA.getVelocity().x, b2dPlayerA.getVelocity().y-40);
        bJumpedA = true;
    }
    
    if (touch.id == 2&& button3B.inside(touch.x, touch.y)&& bJumpedB==false&&bOntheWallB == true) {
        b2dPlayerB.setVelocity(b2dPlayerB.getVelocity().x, b2dPlayerB.getVelocity().y+40);
        bJumpedB = true;
    }
   
 
    

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    

    
    
        
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    if(rect3.inside(touch.x, touch.y)){
        touch.id = 2;
    };
    
    if(rect4.inside(touch.x, touch.y)){
        touch.id = 3;
    };
    
    //********* left ************

    if (touch.id ==0&& button1A.inside(touch.x, touch.y)) {
        bGoleftA = true;
    }else{
         bGoleftA = false;
    }
    
    if (touch.id ==3 && button1B.inside(touch.x, touch.y)) {
        bGoleftB = true;
    }else{
        bGoleftB = false;
    }
    
    //********* right ************
    
    if (touch.id ==0&& button2A.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }else{
        bGoRightA = false;
    }
    
    if (touch.id ==3&& button2B.inside(touch.x, touch.y)) {
        bGoRightB = true;
    }else{
        bGoRightB = false;
    }
    
     //********* jump ************
    if (touch.id == 1&& button3A.inside(touch.x, touch.y)&& bJumpedA==false&& bOntheWallA == true) {
//        b2dPlayerA.setVelocity(b2dPlayerA.getVelocity().x, b2dPlayerA.getVelocity().y-40);
//        bJumpedA = true;
    }else{
        bJumpedA = false;
    }
    
    if (touch.id == 2&& button3B.inside(touch.x, touch.y)&& bJumpedB==false && bOntheWallB == true) {
//        b2dPlayerB.setVelocity(b2dPlayerB.getVelocity().x, b2dPlayerB.getVelocity().y+40);
//        bJumpedB = true;
    }else{
        bJumpedB = false;
    }
	
	    
    
        
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    
    
    
    
    
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    if(rect3.inside(touch.x, touch.y)){
        touch.id = 2;
    };
    
    if(rect4.inside(touch.x, touch.y)){
        touch.id = 3;
    };
    
    //********* left ************
    
    if (touch.id ==0&& button1A.inside(touch.x, touch.y)) {
        bGoleftA = false;
    }
    
    if (touch.id ==3&& button1B.inside(touch.x, touch.y)) {
        bGoleftB = false;
    }
    
    //********* right ************
    
    if (touch.id ==0&& button2A.inside(touch.x, touch.y)) {
        bGoRightA = false;
    
    }
    
    if (touch.id ==3&& button2B.inside(touch.x, touch.y)) {
        bGoRightB = false;
        
    }
    //********* jump ************
    
    if (touch.id == 1&& button3A.inside(touch.x, touch.y)) {
        bJumpedA = false;
    }
    if (touch.id == 2&& button3B.inside(touch.x, touch.y)){
        bJumpedB = false;
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

