#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    
	box2d.init();
	box2d.setGravity(0, 100);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	
	startPoint.setup(box2d.getWorld(), ofGetWidth()/2, 0, 4);
    
    endPoint.setPhysics(5.0, 0.0, 0.0);
    endPoint.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2+10, 30);
    endPoint.body->SetLinearDamping(0.1);
    
    endRect.setPhysics(5.0, 0, 0);
    endRect.setup(box2d.getWorld(),ofGetWidth()/2, ofGetHeight()/2+10, 30,60);
    endRect.body->SetLinearDamping(0.5);
    endRect.body->SetFixedRotation(true);
    control.setup(1);
	
    rope.setup(box2d.getWorld(), startPoint.body, endRect.body);
    rope.setLength(800);
    rope.setFrequency(0);
    

}

//--------------------------------------------------------------
void testApp::update(){
    
    box2d.update();
    ofPoint frc(0,0);
    if (control.bSwingLeft) {
        frc.x = ofMap(control.diff.x, 0, -90, 0, 50,true);
//        endPoint.setVelocity(-frc.x, 0);
        endRect.setVelocity(-frc.x, 0);
        control.bSwingLeft = false;
    }
    
    if (control.bSwingRight) {
        frc.x = ofMap(control.diff.x, 0, 90, 0, 50,true);
//        endPoint.setVelocity(frc.x, 0);
        endRect.setVelocity(frc.x, 0);
        control.bSwingRight = false;
    }
    
    float diffX = endRect.getPosition().x - startPoint.getPosition().x;
    float diffY = endRect.getPosition().y - startPoint.getPosition().y;
    float angleTo = atan2(diffY, diffX);
    endRect.setAngle(PI/2 + angleTo);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetHexColor(0xf2ab01);
	startPoint.draw();
	
    ofFill();
    ofSetHexColor(0x01b1f2);
//    endPoint.draw();
	endRect.draw();
    ofSetHexColor(0x444342);
    rope.draw();
	
	control.draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control.touchDown(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control.touchMove(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control.touchUp(touch.x, touch.y, touch.id);
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

