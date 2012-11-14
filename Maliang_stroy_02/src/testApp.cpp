#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    gameStep=0;
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    bg.loadImage("image/bg.jpg");
    car.loadImage("image/car.png");
    start.loadImage("image/start.png");
    missionS.loadImage("image/missionS.png");
    missionL.loadImage("image/missionF.png");
    location.loadImage("image/location.png");
    myFont1.loadFont("BABYK___.TTF", 25);
    myFont2.loadFont("BABYK___.TTF", 80);
    pct = 0;
//    ofEnableSmoothing();
    ofxXmlSettings tempXml;
    
    if (tempXml.loadFile("roadLayout.xml")) {
        int strokeNum = tempXml.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            tempXml.pushTag("STROKE",i);
            int ptNum = tempXml.getNumTags("PT");
            if (ptNum>0) {
                ofPolyline tempLine;
                for (int j=0; j<ptNum; j++) {
                    int x = tempXml.getValue("PT:X", 0, j);
                    int y = tempXml.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x, y);
                    tempLine.addVertex(tempP);
                }
                roadLayout.push_back(tempLine);
            }
            tempXml.popTag();
        }
    }
    
    myCar.damping = 0.13f;
    myCar.setInitialCondition(50, 600, 0, 0);
    myCar.img =& car;
    
}

//--------------------------------------------------------------
void testApp::update(){
    switch (gameStep) {
        case 0:
            savedTime = ofGetElapsedTimef();
            break;
        case 1:{
                myCar.resetForce();
                ofPoint forc;
                forc = myRoad.VF.getForceFromPos(myCar.pos.x, myCar.pos.y);
                myCar.addForce(forc.x, forc.y);
                myCar.addDampingForce();
                myCar.update();
                
                ofRectangle destination(900, 140, 70, 50);
                if (destination.inside(myCar.pos)) {
                    gameStep=2;
                    totalTime = ofGetElapsedTimef()-savedTime;
                    savedTime = ofGetElapsedTimef();
                }
        }
            break;
        case 2:
            break;
    }
        

}

//--------------------------------------------------------------
void testApp::draw(){
    
    switch (gameStep) {
        case 0:
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofSetColor(180);
            bg.draw(0, 0);
            myCar.draw();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofSetColor(255);
            start.draw(512,384);
            ofSetRectMode(OF_RECTMODE_CORNER);
            break;
        case 1:{
            float time = ofGetElapsedTimef()-savedTime;
            
                ofSetColor(255);
                bg.draw(0, 0);
                ofSetColor(255);
                myRoad.draw();
                ofSetColor(255);
                location.draw(925,150);
                ofSetColor(255);
                myCar.draw();
                myFont1.drawString("TIME: "+ofToString(time,1), 450, 50);

            }
            break;
        case 2:{
            float time = totalTime;
            float animationTime;
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofSetColor(180);
            bg.draw(0, 0);
            ofSetColor(180);
            myRoad.draw();
            ofSetColor(180);
            myCar.draw();
            ofSetColor(255);
            float fontWidth = myFont2.stringWidth("TIME: "+ofToString(time,1));
            ofPoint orgPos(480,50);
            ofPoint desPos(ofGetWidth()/2-fontWidth/2,400);
            ofPoint fontPos;
            float speed = 0.03f;
            pct+=speed;
            if (pct>1) {
                pct=1;
                animationTime = ofGetElapsedTimef()-savedTime;
            }
            
            
            if (animationTime>1.5) {
                if (time>30) {
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    missionL.draw(512,384);
                }else{
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    missionS.draw(512,384);
                }
                
            }else{
                fontPos.x = (1-pct)*orgPos.x+pct*desPos.x;
                fontPos.y = (1-pct)*orgPos.y+pct*desPos.y;
                
                myFont2.drawString("TIME: "+ofToString(time,1), fontPos.x,fontPos.y);
                
            }
        }
            break;

    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (gameStep) {
        case 0:
            break;
        case 1:{
                if (key==' ') {
                    myRoad.clear();
                }else if(key=='d'){
                    myRoad.VFdraw=!myRoad.VFdraw;
                    
                }
        }
            break;
    }
    
        
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
   
    
    switch (gameStep) {
        case 0:
            break;
        case 1:{
        
                if (button==0) {
                    bool bMouse = true;
                    for (int i=0; i<roadLayout.size(); i++) {
                        if(roadLayout[i].inside(x, y)){bMouse=false;}
                    }
                    if (bMouse) { myRoad.mouseDragged(x, y);}                       
                }
            }
            break;
    }


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    switch (gameStep) {
        case 0:{
            
            ofRectangle rect(450, 555, 150, 50);
            if (rect.inside(x,y)) {
                gameStep=1;
            }
        }
            break;
        case 1:{
            if (button==0) {
                bool bMouse = true;
                for (int i=0; i<roadLayout.size(); i++) {
                    if(roadLayout[i].inside(x, y)){bMouse=false;}
                }
                if (bMouse) { myRoad.mousePressed(x, y);}
            }
        }
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    switch (gameStep) {
        case 0:
            break;
        case 1:{
            myRoad.mouseReleased();
        }
            break;
    }
    
    
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