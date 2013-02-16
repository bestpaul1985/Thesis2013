#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
	ofBackground(30,30,30);
    
    //************* player1 ***********
    playerA.setInitialCondition(0, 0,0,0);
    bGoleftA = false;
    bGoRightA = false;
    playerA.damping = 0.05f;
    //************* Buttons ***********
    bc1.set(100, 0, 220);
    bc2.set(100, 0, 220);
    bc3.set(100, 0, 220);
    float w = 100;
    float h = 100;
    button1.set(50, ofGetHeight()-h-50, w, h);
    button2.set(80+w, ofGetHeight()-h-50, w, h);
    button3.set(ofGetWidth()-150, ofGetHeight()-h-50,w, h);
    
    //********** background **************
    bgA.loadImage("IMG_80521.jpeg");
    //********** item 1 ******************
    itemPos1.set(200, 0);

}

//--------------------------------------------------------------
void testApp::update(){
    
   
    //********* players **********
    playerA.resetForce();
    frcA.set(0, 0);
    
    if (bGoleftA) {
        frcA.x = -0.4;
    }
    
    if (bGoRightA) {
        frcA.x = 0.4;
    }
    
    if (bJumpA) {
        frcA.y = -0.5;
    }
    
    
    playerA.addForce(frcA.x, frcA.y);
    playerA.addDampingForce();
    playerA.update();
    
    //********* bgA **********
    
    
    //********** item 1 ******************
    itemPos1 = itemPos1 - playerA.pos;
    
    //*********** Events *****************
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()-150);
    
        //********* bg A *************
        ofSetColor(255);
        bgA.draw(-ofGetWidth()/2-playerA.pos.x,-ofGetHeight()-50,bgA.getWidth(), bgA.getHeight());
        ofSetColor(255, 0, 220);
        ofRect(itemPos1,40,40);
    
        //********* players **********
        ofSetColor(255);
        ofCircle(0, 0, 50);
    ofPopMatrix();
    

    ofPushMatrix();
        //********* buttons **********

        if (bGoleftA) {
            bc1.set(255, 0, 220);
        }else{
            bc1.set(100, 0, 220);
        }
        
        if (bGoRightA) {
            bc2.set(255, 0, 220);
        }else{
            bc2.set(100, 0, 220);
        }
        
        if (bJumpA) {
            bc3.set(255, 0, 220);
        }else{
            bc3.set(100, 0, 220);
        }
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
    
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    //********* left ************

    if (touch.id ==0&& button1.inside(touch.x, touch.y)) {
        bGoleftA = true;
    }//********* right ************
    
    else if (touch.id ==0&& button2.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }
    
    
    //********* jump ************
    
    if (touch.id == 1&& button3.inside(touch.x, touch.y)) {
        bJumpA = true;
        
        cout<<"ok"<<endl;
    }
   
    
    

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    
    
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    //********* left ************

    if (touch.id ==0&& button1.inside(touch.x, touch.y)) {
        bGoleftA = true;
    }else{
         bGoleftA = false;
    }
    
    //********* right ************
    
    if (touch.id ==0&& button2.inside(touch.x, touch.y)) {
        bGoRightA = true;
    }else{
        bGoleftA = false;
    }
    
    //********* jump ************
    
    if (touch.id == 1&& button3.inside(touch.x, touch.y)) {
        bJumpA = true;
    }else{
        bGoleftA = false;
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    if(rect1.inside(touch.x, touch.y)){
        touch.id = 0;
    };
    if(rect2.inside(touch.x, touch.y)){
        touch.id = 1;
    };
    
    //********* left ************
    
    if (touch.id ==0&& button1.inside(touch.x, touch.y)) {
        bGoleftA = false;
    }
    //********* right ************
    
    if (touch.id ==0&& button2.inside(touch.x, touch.y)) {
        bGoRightA = false;
    
    }
    //********* jump ************
    
    if (touch.id == 1&& button3.inside(touch.x, touch.y)) {
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

