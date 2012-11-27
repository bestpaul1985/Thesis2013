#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetWindowShape(650, 1000);
    ofBackground(40);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
    float speedMod = ofGetElapsedTimef()*1200;
    
    ofPushMatrix();
        ofTranslate(0, speedMod);
        
        int d = 100;

        //deal with left button
        ofSetColor(0, 169,157);
        if (bLeft == false) {
            left.draw(50, 50, speedMod, false);
        }
        else if (bLeft == true){
            left.draw(50, 50, speedMod, true);
        }
        //up
        
        ofSetColor(0, 114, 188);
        if (bUp == false) {
            up.draw(50 + d, 50,speedMod, false);
        }
        else if (bUp == true){
            up.draw(50 + d, 50, speedMod, true);
        }
        
        //right
        ofSetColor(247, 148, 29);
        if (bRight == false) {
            right.draw(50 +d*2, 50,speedMod, false);
        }
        else if (bRight == true){
            right.draw(50 +d*2, 50, speedMod, true);
        }
        //down
        ofSetColor(168, 100, 168);
        if (bDown == false) {
            down.draw(50+d*3, 50,speedMod, false);
        }
        else if (bDown == true){
            down.draw(50+d*3, 50, speedMod, true);
        }
        //Z
        ofSetColor(255, 245, 104);
        if (bZ == false) {
            buttonZ.draw(50+d*4, 50,speedMod, false);
        }
        else if (bZ == true){
            buttonZ.draw(50+d*4, 50, speedMod, true);
        }
        //X
        ofSetColor(242, 108, 79);
        if (bX == false) {
            buttonX.draw(50+d*5, 50,speedMod, false);
        }
        else if (bX == true){
            buttonX.draw(50+d*5, 50, speedMod, true);
        }
        
    
    ofPopMatrix();
    
    ofSetLineWidth(1);
    ofSetColor(255);
    ofLine(0, ofGetHeight()*6/7, ofGetWidth(), ofGetHeight()*6/7);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
//    if (key != 0) {
//        cout << key << endl;
//    }
    
    
    if (key == 356) {
        bLeft  =   true;
    }
    if (key == 357) {
        bUp    =   true;
    }
    if (key == 358) {
        bRight =   true;
    }
    if (key == 359) {
        bDown  =   true;
    }
    
    
    if (key == 'z' || key =='Z'){
        bZ     =   true;
    }
    if (key == 'x' || key =='X'){
        bX     =   true;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    
    if (key == 356) {
        bLeft  =   false;
    }    
    if (key == 357) {
        bUp    =   false;
    }
    if (key == 358) {
        bRight =   false;
    }
    if (key == 359) {
        bDown  =   false;
    }
    
    
    if (key == 'z' || key =='Z'){
        bZ = false;
    }
    if (key == 'x' || key =='X'){
        bX = false;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}