#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
	
	ofBackground(30);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-30);
    world_A.setIterations(1, 1);
    world_A.registerGrabbing();
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 30);
    world_B.setIterations(1, 1);
    world_B.registerGrabbing();
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
    control_A.setup(0);
    control_B.setup(1);
    //char
    char_A.setup(world_A,
                 control_A,
                 control_B,
                 ofPoint(0,0),
                 0);
    
    char_B.setup(world_B,
                 control_A,
                 control_B,
                 ofPoint(0,0),
                 1);
    
    //offset
    currentPos_A = char_A.getPos;
    currentPos_B = char_B.getPos;
    orgPos_A.set(0.0, 0.0);
    orgPos_B.set(0.0, 0.0);
    
    offSet_A = currentPos_A-orgPos_A;
    offSet_B = currentPos_B-orgPos_B;
    
    translate_A.set(384,200);
    translate_B.set(384,768-200);
    //rope
    rope_A.setup(ofxAccelerometer.getForce(),0);
    rope_B.setup(ofxAccelerometer.getForce(),1);
    
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    //sky
    sky.setup();
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
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

    //Character
    char_A.update();
    char_B.update();
   
    
    //offset
    currentPos_A = char_A.getPos;
    currentPos_B = char_B.getPos;
    if (!rope_A.bHooked) {
        offSet_B = currentPos_B-orgPos_B;
    }
    
    if (!rope_B.bHooked) {
        offSet_A = currentPos_A-orgPos_A;
    }
    
    
    
    //rope update
    rope_A.updatePosition(translate_A,translate_B,offSet_A,offSet_B);
    rope_B.updatePosition(translate_A,translate_B,offSet_A,offSet_B);
    rope_A.updateAccelerometer();
    rope_B.updateAccelerometer();
    rope_A.controlRope();
    rope_B.controlRope();
    // rope_A swiches
    if (rope_A.bRopeInUse) {
        
        char_A.bFixedMove = true;
        
        if (rope_A.bHooked) {
            char_B.bFixedMove = true;
            control_B.bHooked = true;
            char_B.bSwing = true;
            ofPoint pos;
            pos.x = currentPos_B.x - offSet_B.x;
            pos.y = char_B.start.getPosition().y - char_B.getPos.y;
            rope_A.endPos.set(pos.x, -pos.y);
        }
        
        if (control_B.bRelese) {
            char_B.bFixedMove = false;
            control_B.bHooked = false;
            char_B.bSwing = false;
            rope_A.bRopeInUse = false;
            rope_A.bHooked = false;
            char_A.bFixedMove = false;
            rope_A.endPos.set(0, 0);
        }
        
    }
    
   
    if (!rope_A.bRopeInUse&&!rope_B.bRopeInUse) {
        char_B.bFixedMove = false;
        char_B.bSwing = false;
    
        char_A.bFixedMove = false;
        char_A.bSwing = false;
        
        control_A.bHooked = false;
        control_B.bHooked = false;
       
        rope_A.bHooked = false;
        rope_B.bHooked = false;
    }
    
    
    
    //ropeB swiches
    if (rope_B.bRopeInUse) {
        char_B.bFixedMove = true;
    }
    
    if (rope_B.bHooked) {
        char_A.bFixedMove = true;
        control_A.bHooked = true;
        char_A.bSwing = true;
        ofPoint pos;
        pos.x = currentPos_A.x - offSet_A.x;
        pos.y = char_A.start.getPosition().y - char_A.getPos.y;
        rope_B.endPos.set(pos.x, -pos.y);
    }
    
    if (control_A.bRelese) {
        rope_B.bRopeInUse = false;
        rope_B.bHooked = false;
        char_A.bFixedMove = false;
        char_A.bSwing = false;
        rope_B.endPos.set(0, 0);
    }
    
    
    char_A.swing(translate_A, translate_B, offSet_A, offSet_B);
    char_B.swing(translate_A, translate_B, offSet_A, offSet_B);
    
    //no jump in sky
    if (numFootContacts_A<=0) {
        control_A.bFixed = true;
    }else{
        control_A.bFixed = false;
    }
    
    if (numFootContacts_B<=0) {
        control_B.bFixed = true;
    }else{
        control_B.bFixed = false;
    }
    
 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    
//    ofDrawBitmapStringHighlight("offSet_A: " + ofToString(offSet_A,2)+"\ntranslate_A: "+ofToString(translate_A)+"\nchar_A: "+ofToString(char_A.getPos), 50,50);
//    ofDrawBitmapStringHighlight("offSet_B: " + ofToString(offSet_B,2)+"\ntranslate_B: "+ofToString(translate_B)+"\nchar_B: "+ofToString(char_B.getPos), 530,950);
}
//-------------------------------------------------------------
void testApp::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(translate_A.x-offSet_A.x,translate_A.y);
        ground_A.draw();
//        ground_A.drawPolyLine();
//        char_A.drawBox2dObject();
//        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(translate_B.x-offSet_B.x,translate_B.y);
        ground_B.draw();
//        ground_B.drawPolyLine();
//        char_B.drawBox2dObject();
//        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
        
        ofPushMatrix();
        ofTranslate(translate_A.x-offSet_A.x,translate_A.y);
        char_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(translate_B.x-offSet_B.x,translate_B.y);
        char_B.draw();
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
    control_A.touchDown(touch.x, touch.y,touch.id);
    control_B.touchDown(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    control_A.touchMove(touch.x, touch.y,touch.id);
    control_B.touchMove(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    control_A.touchUp(touch.x, touch.y,touch.id);
    control_B.touchUp(touch.x, touch.y,touch.id);
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

