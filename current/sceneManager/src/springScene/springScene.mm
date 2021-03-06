#include "springScene.h"

//--------------------------------------------------------------
void springScene::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
    ofEnableAlphaBlending();
    
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-30);
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 30);
    //Map
    ground_A.setup(1, 0, world_A);
    ground_B.setup(1, 1, world_B);
    
    
	ofAddListener(world_A.contactStartEvents, this, &springScene::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &springScene::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &springScene::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &springScene::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    
    //contorl
    control_A.setup(0);
    control_B.setup(1);
    //char
    char_A.setup(world_A,control_A,control_B,ofPoint(50,0),0);
    char_B.setup(world_B,control_A,control_B,ofPoint(50,0),1);
    
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
    rope_A.setup(ofxAccelerometer.getForce(),screenA,screenB,char_A.getPos,char_B.getPos,control_A,control_B,0);
    rope_B.setup(ofxAccelerometer.getForce(),screenA,screenB,char_A.getPos,char_B.getPos,control_A,control_B,1);
}
//--------------------------------------------------------------
void springScene::contactStart_worldA(ofxBox2dContactArgs &e){
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
void springScene::contactEnd_worldA(ofxBox2dContactArgs &e){
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
void springScene::contactStart_worldB(ofxBox2dContactArgs &e){
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
void springScene::contactEnd_worldB(ofxBox2dContactArgs &e){
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
void springScene::update(){
    
    world_A.update();
    world_B.update();
    
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

    //Character
    char_A.update();
    char_B.update();
    //screen
    screen();
   
    //rope update
    rope_A.update();
    rope_B.update();
    
    //character ropeA
    
   
    
    if (rope_A.bRopeInUse) {
        char_A.bFixedMove = true;
        char_B.destroyRect();
        rope_A.bRopeInUse = false;
    }
    
    if(rope_A.bReady){
        control_B.bDrawButton = true;
    }
    
    if (control_B.bHookRope && rope_A.bReady) {
        char_B.copyRope(rope_A.rects, rope_A.joints, screenB);
        char_B.bSwing = true;
        char_B.bFixedMove = true;
        rope_A.bReady = false;
        rope_A.destroy();
    }else if(control_B.bHookRope && char_B.bSwing){
        char_B.controlRope();
    }else if(!control_B.bHookRope && char_B.bSwing){
        char_B.character.setVelocity(char_B.rects.back().getVelocity());
        char_B.destroyRope();
        char_B.bSwing = false;
        char_B.bFixedMove = false;
        control_B.bDrawButton = false;
    }
    //character ropeB
    if (rope_B.bRopeInUse) {
        char_B.bFixedMove = true;
        char_A.destroyRect();
        rope_B.bRopeInUse = false;
    }
    
    if(rope_B.bReady){
        control_A.bDrawButton = true;
    }
    
    if (control_A.bHookRope && rope_B.bReady) {
        char_A.copyRope(rope_B.rects, rope_B.joints, screenA);
        char_A.bSwing = true;
        char_A.bFixedMove = true;
        rope_B.bReady = false;
        rope_B.destroy();
    }else if(control_A.bHookRope && char_A.bSwing){
        char_A.controlRope();
    }else if(!control_A.bHookRope && char_A.bSwing){
        char_A.character.setVelocity(char_A.rects.back().getVelocity());
        char_A.destroyRope();
        char_A.bSwing = false;
        char_A.bFixedMove = false;
        control_A.bDrawButton = false;
    }
    
    if (!rope_A.bInitialize && !rope_B.bInitialize) {
        char_B.destroyRope();
        char_B.bSwing = false;
        char_B.bFixedMove = false;
       
        control_B.bDrawButton = false;
        
        char_A.destroyRope();
        char_A.bSwing = false;
        char_A.bFixedMove = false;
        
        control_A.bDrawButton = false;
    }
    
}

//--------------------------------------------------------------
void springScene::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
   
    drawScene(0);
    accIndictor.draw();
    control_A.draw();
    control_B.draw();
    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(ofPoint(translate_A.x,translate_A.y+char_A.getPos.y),2), 50,50);
    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(ofPoint(translate_B.x,translate_B.y+char_B.getPos.y),2), 750,700);
}
//-------------------------------------------------------------
void springScene::drawScene(int iDraw){

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
void springScene::exit(){

}

//--------------------------------------------------------------
void springScene::touchDown(ofTouchEventArgs & touch){
    control_A.touchDown(touch.x, touch.y,touch.id);
    control_B.touchDown(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void springScene::touchMoved(ofTouchEventArgs & touch){
    control_A.touchMove(touch.x, touch.y,touch.id);
    control_B.touchMove(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void springScene::touchUp(ofTouchEventArgs & touch){
    control_A.touchUp(touch.x, touch.y,touch.id);
    control_B.touchUp(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void springScene::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void springScene::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void springScene::lostFocus(){

}

//--------------------------------------------------------------
void springScene::gotFocus(){

}

//--------------------------------------------------------------
void springScene::gotMemoryWarning(){

}

//--------------------------------------------------------------
void springScene::deviceOrientationChanged(int newOrientation){

}
//--------------------------------------------------------------
void springScene::screen(){
    
    screenA.x = translate_A.x - char_A.getPos.x,
    screenA.y = translate_A.y;
    
    screenB.x = translate_B.x - char_B.getPos.x,
    screenB.y = translate_B.y;

}
