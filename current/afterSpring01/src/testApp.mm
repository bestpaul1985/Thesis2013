#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-10);
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 10);
    //Map
    ground_A.setup(1, 0, world_A);
    ground_B.setup(1, 1, world_B);
    
    
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    
    //contorl
    control.setup();
    
    //char
    char_A.setup(world_A,control,ofPoint(50,0),ofxAccelerometer.getForce(),0);
    char_B.setup(world_B,control,ofPoint(50,0),ofxAccelerometer.getForce(),1);
    
    //translate
    translate_A.set(384,250);
    translate_B.set(384,768-250);
    screen();
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    
    //sky
    sky.setup();
    
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    rope_A.setup(ofxAccelerometer.getForce(),screenA,screenB,char_A.getPos,char_B.getPos,control,0);
    rope_B.setup(ofxAccelerometer.getForce(),screenA,screenB,char_A.getPos,char_B.getPos,control,1);
}
//--------------------------------------------------------------
void testApp::contactStart_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.bDead = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (aData&&aData->name == "thorn") {
                char_A.bDead = true;
            }
        }
        
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
            
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_A--;
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_A--;
        }
    }
}
//--------------------------------------------------------------
void testApp::contactStart_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
                char_B.bDead = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (aData&&aData->name == "thorn") {
                char_B.bDead = true;
            }
        }
    }

}
//--------------------------------------------------------------
void testApp::contactEnd_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        if (aData && aData->name == "footSenser"){
            numFootContacts_B--;
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B--;
        } 
    }
}
//--------------------------------------------------------------
void testApp::update(){
    
    world_A.update();
    world_B.update();
    
    //no jump in sky
    if (numFootContacts_A<=0) {
        char_A.bInSky = true;
    }else{
        char_A.bInSky = false;
    }
    
    if (numFootContacts_B<=0) {
        char_B.bInSky = true;
    }else{
        char_B.bInSky = false;
    }

    //Character
    char_A.update();
    char_B.update();
    //screen
    screen();
   
    //rope update
    
    if (!control.bAllTouch) {
        rope_A.update();
        rope_B.update();
    }
    //character ropeA
    
    if (char_A.bDouPressed && rope_B.bReady && char_A.joints.empty()) {
        char_A.copyRope(rope_B.rects, rope_B.joints, screenA);
        rope_B.bReady = false;
        rope_B.destroy();
    }else if(char_A.bDouPressed && !char_A.joints.empty()&& !char_A.bRopeInControl){
        char_A.controlRope();
    }else if(char_A.bDouPressed && !char_A.joints.empty()&& char_A.bRopeInControl){
        char_A.swing();
    }else if(!char_A.bDouPressed && !char_A.joints.empty()&& char_A.bSwing){
        char_A.character.setVelocity(char_A.rects.back().getVelocity().x * 3, char_A.character.getVelocity().y);
        char_A.destroyRope();
        char_A.bSwing = false;
    }
    
    if (char_B.bDouPressed && rope_A.bReady && char_B.joints.empty()) {
        char_B.copyRope(rope_A.rects, rope_A.joints, screenB);
        rope_A.bReady = false;
        rope_A.destroy();
    }else if(char_B.bDouPressed && !char_B.joints.empty()&& !char_B.bRopeInControl){
        char_B.controlRope();
    }else if(char_B.bDouPressed && !char_B.joints.empty()&& char_B.bRopeInControl){
        char_B.swing();
    }else if(!char_B.bDouPressed && !char_B.joints.empty()&& char_B.bSwing){
        char_B.character.setVelocity(char_B.rects.back().getVelocity().x * 3, char_B.character.getVelocity().y);
        char_B.destroyRope();
        char_B.bSwing = false;
    }
    
    
    
    if (!rope_A.bInitialize && !rope_B.bInitialize && !control.bAllTouch) {
        char_B.destroyRope();
        rope_A.bRopeInUse = false;
        char_A.destroyRope();
        rope_B.bRopeInUse = false;
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control.draw();
    
    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(ofPoint(translate_A.x,translate_A.y+char_A.getPos.y),2), 50,50);
    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(ofPoint(translate_B.x,translate_B.y+char_B.getPos.y),2), 750,700);
}
//-------------------------------------------------------------
void testApp::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(translate_A.x-char_A.getPos.x,translate_A.y);
        ground_A.draw();
//        ground_A.drawPolyLine();
//        char_A.drawBox2dObject();
//        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(translate_B.x-char_B.getPos.x,translate_B.y);
        ground_B.draw();
//        ground_B.drawPolyLine();
//        char_B.drawBox2dObject();
//        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
        
        ofPushMatrix();
        ofTranslate(translate_A.x-char_A.getPos.x,translate_A.y);
        char_A.draw();
        char_A.drawRope();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(translate_B.x-char_B.getPos.x,translate_B.y);
        char_B.draw();
        char_B.drawRope();
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofTranslate(translate_A.x-char_A.getPos.x,translate_A.y);
        char_A.drawRope();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(translate_B.x-char_B.getPos.x,translate_B.y);
        char_B.drawRope();
        ofPopMatrix();
        
        rope_A.draw();
        rope_B.draw();
    }
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    control.touchDown(touch.x, touch.y,touch.id);
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control.touchMove(touch.x, touch.y,touch.id);
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control.touchUp(touch.x, touch.y,touch.id);
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
//--------------------------------------------------------------
void testApp::screen(){
    
    screenA.x = translate_A.x - char_A.getPos.x,
    screenA.y = translate_A.y;
    
    screenB.x = translate_B.x - char_B.getPos.x,
    screenB.y = translate_B.y;

}
