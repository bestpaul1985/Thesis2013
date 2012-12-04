#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(30,30,30);
    ofSetCircleResolution(60);
    ofEnableSmoothing();
    
    //************* player1 ***********
    playerA.setInitialCondition(0, 0, 0, 0);
    bGoLeftA = false;
    bGoRightA = false;
    playerA.damping = 0.05f;
    
    //************* Buttons ***********
    bc1.setHex(0x0071bb);
    bc2.setHex(0x0071bb);
    bc3.setHex(0x0071bb);
    
    float w = 75;
    float h = 50;
    button1.set(20, ofGetHeight()-20-h, w, h);
    button2.set(40+w, ofGetHeight()-20-h, w, h);
    button3.set(ofGetWidth()-20-w, ofGetHeight()-20-h, w, h);

    //********** background **************
//    bgA.loadImage("IMG_80521.jpeg");
    //********** item 1 ******************
    itemPos1.set(200, 0);

}

//--------------------------------------------------------------
void testApp::update(){
    
   
    //********* players **********
    playerA.resetForce();
    frcA.set(0, 0);
    
    if (bGoLeftA) {
        frcA.x = -0.4;
    }
    
    if (bGoRightA) {
        frcA.x = 0.4;
    }
    
    if (bJumpA) {
        frcA.y = -0.5;
    }
    else if (playerA.pos.y <= 0){
        frcA.y = 0.5;
    }
    else if (playerA.pos.y > 0) {
        frcA.y = 0;
    }
    
    
    playerA.addForce(frcA.x, frcA.y);
    playerA.addDampingForce();
    playerA.update();
    

    
//----Button Color
    if (bGoLeftA) {
        bc1.setHex(0xf05a24);
    }else{
        bc1.setHex(0x0071bb);
    }
    
    if (bGoRightA) {
        bc2.setHex(0xf05a24);
    }else{
        bc2.setHex(0x0071bb);
    }
    
    if (bJumpA) {
        bc3.setHex(0xf05a24);
    }else{
        bc3.setHex(0x0071bb);
    }
    
    
    //********** item 1 ******************
    itemPos1 = itemPos1 - playerA.pos;
    
    //*********** Events *****************
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
//----Background
    ofPushMatrix();
    ofTranslate(-playerA.pos.x, ofGetHeight()/2);
    ofSetHexColor(0x5e462f);
    for (int i=0; i<100; i++) {
        ofRect(i*20, 0, 10, ofGetHeight()/2);
    }
    ofPopMatrix();
//        bgA.draw(-ofGetWidth()/2-playerA.pos.x,-ofGetHeight()-50,bgA.getWidth(), bgA.getHeight());
    
    
//----Player
    ofPushMatrix();
        ofTranslate(ofGetWidth()/3, ofGetHeight()/2 +350 +playerA.pos.y );

        //********* item *************
//        ofSetColor(255, 0, 220);
//        ofRect(itemPos1,40,40);
    
        ofSetHexColor(0xf0bb46);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(0, 0, 40, 80);
        ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();
    
//----Button
    ofPushMatrix();
        ofSetColor(bc1);
        ofRect(button1);
        ofSetColor(bc2);
        ofRect(button2);
        ofSetColor(bc3);
        ofRect(button3);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    }
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    }
    
    
    //********* left ************
    if (touch.id ==0 && button1.inside(touch.x, touch.y)) {
        bGoLeftA = true;
    }
    
    //********* right ************
    if (touch.id ==0 && button2.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }
    
    
    //********* jump ************
    if (touch.id == 1 && button3.inside(touch.x, touch.y)) {
        bJumpA = true;
    }
   
    
    

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    }
    
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    }
    
    //********* left ************
    if (touch.id ==0 && button1.inside(touch.x, touch.y)) {
        bGoLeftA = true;
    }else{
        bGoLeftA = false;
    }
    
    //********* right ************
    if (touch.id ==0 && button2.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }else{
        bGoRightA = false;
    }
    
    //********* jump ************
    if (touch.id == 1 && button3.inside(touch.x, touch.y)) {
        bJumpA = true;
    }else{
        bJumpA = false;
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth()/2, ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    }
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    }
    
    //********* left ************
    if (touch.id ==0 && button1.inside(touch.x, touch.y)) {
        bGoLeftA = false;
    }
    
    //********* right ************
    if (touch.id ==0 && button2.inside(touch.x, touch.y)) {
        bGoRightA = false;
    }
    
    //********* jump ************
    if (touch.id == 1 && button3.inside(touch.x, touch.y)) {
        bJumpA = false;
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

