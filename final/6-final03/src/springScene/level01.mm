#include "level01.h"

//--------------------------------------------------------------
void level01::setup(){	
    // initialize the accelerometer
    SETUP = false;
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.9f);
    ofEnableAlphaBlending();
    ofSetCircleResolution(8);
    ofSetLineWidth(2.5);
    ofSetFrameRate(60);
    ofEnableSmoothing();
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
    
    //Listener
	ofAddListener(world_A.contactStartEvents, this, &level01::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &level01::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &level01::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &level01::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;
    
    //contorl
    control.setup();
    
    //char
    char_A.setup(world_A, ofPoint(0,0), 0);
    char_B.setup(world_B, ofPoint(0,0), 1);
    //camera
    translate_A.set(384,250);
    translate_B.set(384,768-250);
    camera_A = char_A.getPos;
    camera_B = char_B.getPos;
    //thorn
    thorns_A.setup(world_A, 0);
    thorns_B.setup(world_B, 1);
    
    //sky
    sky.setup();
    
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    rope_A.setup(world_B, char_A, char_B, rope_start_B, hook_start_A, hook_end_A, ofxAccelerometer.getForce(), 0);
    rope_B.setup(world_A, char_B, char_A, rope_start_A, hook_start_B, hook_end_B, ofxAccelerometer.getForce(), 1);
    
    //booleans
    bInSky_A = false;
    bInSky_B = false;
    bStatistics = false;
    
    //renderers
    dog_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 120);
    dog_Render ->loadTexture("sprites/all_dog.png", 2040, GL_NEAREST);
    rabit_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 30);
    rabit_Render ->loadTexture("sprites/rabit.png", 2040, GL_NEAREST);
    
    //dog
    dog_A.setup(world_A,dog_Render, 200, 100, 0);
    dog_B.setup(world_B,dog_Render, 200, -100, 1);
    //rabit
    rabit_A.setup(world_A,rabit_Render, -200, 100, 0);
    rabit_B.setup(world_B,rabit_Render, -200, -100, 1);
    //emoji
    emoji_A.setup(char_A.character.getPosition(),char_A,0);
    emoji_B.setup(char_B.character.getPosition(),char_B,1);
    image[0].loadImage("sprites/emoji_love.png");
    image[1].loadImage("sprites/emoji_laughing.png");
    image[2].loadImage("sprites/emoji_happy.png");
    image[3].loadImage("sprites/emoji_supprise.png");
    image[4].loadImage("sprites/emoji_angry.png");
    
    emoji_A.image[0] = &image[0];
    emoji_A.image[1] = &image[1];
    emoji_A.image[2] = &image[2];
    emoji_A.image[3] = &image[3];
    emoji_A.image[4] = &image[4];
    
    emoji_B.image[0] = &image[0];
    emoji_B.image[1] = &image[1];
    emoji_B.image[2] = &image[2];
    emoji_B.image[3] = &image[3];
    emoji_B.image[4] = &image[4];
    
    
    
    //score
    font.loadFont("font/NewMedia Fett.ttf", 20);
    
    //meun
    leve_menu.set(ofGetWidth(),ofGetHeight()/2);
    meunRadius = 70;
    SETUP = true;
}
//--------------------------------------------------------------
void level01::contactStart_worldA(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.condition = C_DEAD;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.condition = C_DEAD;
            }
        }
        
    }
    
}
//--------------------------------------------------------------
void level01::contactEnd_worldA(ofxBox2dContactArgs &e){
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
void level01::contactStart_worldB(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        //a == polygone, b == circle
        ttSetData * aData = (ttSetData*)e.a->GetUserData();
        ttSetData * bData = (ttSetData*)e.b->GetUserData();
        
        if (aData && aData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
                char_B.condition = C_DEAD;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
                char_B.condition = C_DEAD;
            }
        }
    }
    
}
//--------------------------------------------------------------
void level01::contactEnd_worldB(ofxBox2dContactArgs &e){
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
void level01::update(){
    world_A.update();
    world_B.update();
    
    //no jump in sky
    if (numFootContacts_A<=0) {
        bInSky_A = true;
    }else{
        bInSky_A = false;
    }
    
    if (numFootContacts_B<=0) {
        bInSky_B = true;
    }else{
        bInSky_B = false;
    }
    
    
    //screen update-------------------------------
    position();
    //control char_A-------------------------------
    if (ofxAccelerometer.getForce().x<-0.3 && rope_A.condition == R_NO_USE && rope_B.condition != R_SWING&& !bInSky_A) {
        char_A.condition = C_PUSH_ROPE;
        rope_A.hook_pct  = 0;
        rope_A.condition = R_PUSH;
    }//charA pushRope
    
    if (char_A.condition != C_DEAD) {
        if (!control.bTouch[0]&&!control.bTouch[1]) {//charA noPress
            
            if (rope_A.condition==R_NO_USE&& !bInSky_A) {
                char_A.condition = C_STOP;
            }
            
            if (rope_B.condition == R_SWING) {
                rope_B.condition = R_DESTROY;
            }
            
            if (rope_B.condition == R_DESTROY) {
                char_B.condition = C_STOP;
            }
        }
        
        
        if (control.bTouch[0]&&!control.bTouch[1]) {//charA left
            if (rope_A.condition == R_NO_USE) {
                char_A.condition = C_LEFT;
            }
            if (rope_B.condition == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
        if(control.bTouch[1]&&!control.bTouch[0]){//charA right
            if (rope_A.condition  == R_NO_USE) {
                char_A.condition = C_RIGHT;
            }
            if (rope_B.condition  == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
        if(control.bTouch[0]&&control.bTouch[1]){//charA doublePress
            if (rope_B.condition  == R_PUSH) {
                ofPoint dis =  hook_end_B - char_pos_A;
                if ( fabs(dis.x)< 50 && dis.y<=60) {
                    char_A.condition = C_HOOK_ROPE;
                    char_B.condition = C_SWING_ROPE;
                    rope_B.condition  = R_SWING;
                }
            }
        }
    }
    
    //control char_B-------------------------------
    if (ofxAccelerometer.getForce().x>0.3 && rope_B.condition  == R_NO_USE && rope_A.condition != R_SWING && !bInSky_B) {
        char_B.condition = C_PUSH_ROPE;
        rope_B.hook_pct = 0;
        rope_B.condition  = R_PUSH;
        
    }//charB pushRope
    
    if (char_B.condition != C_DEAD) {
        if (!control.bTouch[2]&&!control.bTouch[3]) {//charB noPress
            if (rope_B.condition==R_NO_USE && !bInSky_B) {
                char_B.condition = C_STOP;
            }
            
            
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
            
            if (rope_A.condition == R_DESTROY) {
                char_A.condition = C_STOP;
            }
        }
        
        if (control.bTouch[2]&&!control.bTouch[3]) {//charB left
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_LEFT;
            }
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        if(control.bTouch[3]&&!control.bTouch[2]){//charB right
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_RIGHT;
            }
            
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        if(control.bTouch[2]&&control.bTouch[3]){//charB double press
            if (rope_A.condition == R_PUSH) {
                ofPoint dis =  hook_end_A - char_pos_B;
                if ( fabs(dis.x)< 50 && dis.y>=-60) {
                    char_B.condition = C_HOOK_ROPE;
                    char_A.condition = C_SWING_ROPE;
                    rope_A.condition = R_SWING;
                }
            }
        }
    }
    //rope--------------------------------------
    rope_A.update();
    rope_B.update();
    
    //Character-------------------------------
    char_A.update();
    char_B.update();
    
    //dog-------------------------------
    dog_A.update();
    dog_B.update();
    if (dog_B.killZone.inside(char_B.character.getPosition().x, char_B.character.getPosition().y)) {
        char_B.condition = C_DEAD;
        dog_B.condition = D_BITE;
        rope_A.condition = R_DESTROY;
    }
    //rabit-------------------------------
    rabit_A.update();
    rabit_B.update();
    //emoji-------------------------------
    emoji_A.update(char_A.character.getPosition(), char_A.moveLeft);
    emoji_B.update(char_B.character.getPosition(), char_B.moveLeft);
    emoji_A.control();
    emoji_B.control();}

//--------------------------------------------------------------
void level01::draw(){
    ofColor dark(80);
    ofBackgroundGradient(dark, ofColor::black);
    
    drawScene(0);
    accIndictor.draw();
    control.draw();
    
    //meun
    bStatistics? ofSetColor(204,204,204,150):ofSetColor(204,204,204,60);
    ofCircle(leve_menu, meunRadius);
    
    if (bStatistics) {
        ofSetColor(30, 30, 30);
        font.drawString("SCORE_A\n"+ofToString(emoji_A.score), ofGetWidth()/2, ofGetHeight()/2-300);
        font.drawString("SCORE_B\n"+ofToString(emoji_B.score), ofGetWidth()/2, ofGetHeight()/2+300);
        emoji_A.diagram(800,400);
        emoji_B.diagram(300,400);
    }
    
    //    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(char_A.getPos+screen_A,2), 50,50);
    //    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(char_B.getPos+screen_B,2), 750,700);
}
//-------------------------------------------------------------
void level01::drawScene(int iDraw){

    if (iDraw == 0) {
        sky.drawBg();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        ground_A.draw();
        //        ground_A.drawPolyLine();
        //        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        ground_B.draw();
        //        ground_B.drawPolyLine();
        //        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
        
        ofPushMatrix();
        ofTranslate(screen_A);
        dog_A.draw();
        rabit_A.draw();
        char_A.draw();
        emoji_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        dog_B.draw();
        rabit_B.draw();
        char_B.draw();
        emoji_B.draw();
        ofPopMatrix();
    }
    //draw swing rope A
    rope_A.draw_swing(screen_B);
    rope_A.draw_push();
    rope_B.draw_swing(screen_A);
    rope_B.draw_push();
}
//--------------------------------------------------------------
void level01::exit(){

}

//--------------------------------------------------------------
void level01::touchDown(ofTouchEventArgs & touch){
    control.touchDown(touch.x, touch.y,touch.id);
    ofPoint pos(touch.x, touch.y);
    if (leve_menu.distance(pos)< meunRadius) {
        bStatistics = !bStatistics;
    }
}

//--------------------------------------------------------------
void level01::touchMoved(ofTouchEventArgs & touch){
    control.touchMove(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void level01::touchUp(ofTouchEventArgs & touch){
    control.touchUp(touch.x, touch.y,touch.id);
}

//--------------------------------------------------------------
void level01::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void level01::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void level01::lostFocus(){

}

//--------------------------------------------------------------
void level01::gotFocus(){

}

//--------------------------------------------------------------
void level01::gotMemoryWarning(){

}

//--------------------------------------------------------------
void level01::deviceOrientationChanged(int newOrientation){

}
//--------------------------------------------------------------
void level01::position(){
    
    bool A[10],B[10];
    float catchUpSpeed = 0.05f;
    ofPoint catch_A, catch_B;
    
    char_A.getPos.x<0? A[0] = true: A[0] =false;
    char_B.getPos.x<0? B[0] = true: B[0] =false;
    //camera setup
    if (A[0]) {
        catch_A.x = 0;
        catch_A.y = char_A.getPos.y;
    }else{
        catch_A.x = char_A.getPos.x;
        catch_A.y = char_A.getPos.y;
    }
    
    if (B[0]) {
        catch_B.x = 0;
        catch_B.y = char_B.getPos.y;
    }else{
        catch_B.x = char_B.getPos.x;
        catch_B.y = char_B.getPos.y;
    }
    
    
    if (rope_B.condition != R_SWING) {
        camera_A.x = catchUpSpeed * catch_A.x + (1-catchUpSpeed) * camera_A.x;
        camera_A.y = catchUpSpeed * catch_A.y + (1-catchUpSpeed) * camera_A.y;
    }
    
    if (rope_A.condition != R_SWING) {
        camera_B.x = catchUpSpeed * catch_B.x + (1-catchUpSpeed) * camera_B.x;
        camera_B.y = catchUpSpeed * catch_B.y + (1-catchUpSpeed) * camera_B.y;
    }
    
    screen_A.x = translate_A.x - camera_A.x,
    screen_A.y = translate_A.y;
    
    screen_B.x = translate_B.x - camera_B.x,
    screen_B.y = translate_B.y;
    //char postion
    char_pos_A = char_A.getPos + screen_A;
    char_pos_B = char_B.getPos + screen_B;
    //hook postion
    
    ofPoint offset_A(15,8);
    ofPoint offset_B(-4,22);
    if (char_A.moveLeft) hook_start_A.x = char_pos_A.x - offset_A.x;
    else hook_start_A.x = char_pos_A.x + offset_A.x;
    hook_start_A.y = char_pos_A.y + offset_A.y;
    
    if (char_B.moveLeft) hook_start_B.x = char_pos_B.x - offset_B.x;
    else hook_start_B.x = char_pos_B.x + offset_B.x;
    hook_start_B.y = char_pos_B.y - offset_B.y;
    //rope postion
    rope_start_A = hook_start_B - screen_A;
    //    rope_end_A = hook_end_B - screen_A;
    
    rope_start_B = hook_start_A - screen_B;
    //    rope_end_B = hook_end_A - screen_B;
    
}