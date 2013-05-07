#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.9f);
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    ofEnableAlphaBlending();
    ofSetCircleResolution(6);
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
    ground_A.setup(0, 0, world_A);
    ground_B.setup(0, 1, world_B);
    //Listener
	ofAddListener(world_A.contactStartEvents, this, &testApp::contactStart_worldA);
	ofAddListener(world_A.contactEndEvents, this, &testApp::contactEnd_worldA);
    ofAddListener(world_B.contactStartEvents,this, &testApp::contactStart_worldB);
    ofAddListener(world_B.contactEndEvents,this, &testApp::contactEnd_worldB);
    numFootContacts_A = 0;
    numFootContacts_B = 0;

    //contorl
    control.setup();
    
    //char
    char_Render[0] = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    char_Render[1] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[2] = new ofxSpriteSheetRenderer(1, 10000, 0, 39);
    char_Render[3] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[4] = new  ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_Render[0]->loadTexture("sprites/all_girl.png", 2040, GL_NEAREST);
    char_Render[1]->loadTexture("sprites/push_girl.png", 1000, GL_NEAREST);
    char_Render[2] ->loadTexture("sprites/run_boy.png", 1000, GL_NEAREST);
    char_Render[3] ->loadTexture("sprites/push_boy.png", 1000, GL_NEAREST);
    char_Render[4] ->loadTexture("sprites/pull_boy.png", 1000, GL_NEAREST);
    char_A.setup(world_A, ofPoint(0,-200), 0,char_Render[0],char_Render[1],char_Render[1]);
    char_B.setup(world_B, ofPoint(0,200), 1,char_Render[2],char_Render[3],char_Render[4]);
    //camera
    translate_A.set(384,768/2);
    translate_B.set(384,768/2);
    camera_A = char_A.getPos;
    camera_B = char_B.getPos;
    //thorn
    thorns_A.setup(world_A, 0,0);
    thorns_B.setup(world_B, 0,1);
    
    //sky
    skyBg.loadImage("sprites/bg/sky/background.png");
    sky.setup(skyBg);
    //indictor
    accIndictor.setup(ofxAccelerometer.getForce());
    
    //rope
    rope_A.setup(world_B, char_A, char_B, rope_start_B, hook_start_A, hook_end_A, ofxAccelerometer.getForce(), 0);
    rope_B.setup(world_A, char_B, char_A, rope_start_A, hook_start_B, hook_end_B, ofxAccelerometer.getForce(), 1);

    //booleans
    bInSky_A = false;
    bInSky_B = false;
    levelOver_A = false;
    levelOver_B = false;
    levelRester = true;
    bStatistics = false;
    //renderers
    dog_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 120);
    dog_Render ->loadTexture("sprites/all_dog.png", 2040, GL_NEAREST);
    rabit_Render = new ofxSpriteSheetRenderer(1, 1000, 0, 30);
    rabit_Render ->loadTexture("sprites/rabit.png", 2040, GL_NEAREST);
    bird_Render =new ofxSpriteSheetRenderer(1,1000,0,100);
    bird_Render ->loadTexture("sprites/all_bird.png", 2040, GL_NEAREST);

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
    logo.loadImage("menu/firstmenuLogo72.png");
    mainMenuText.loadImage("menu/firstmenuText72.png");
    main_menu.setup(skyBg, logo,mainMenuText, ofxAccelerometer.getForce());
    game_menu.setup();
    
    //gameEnd;
    gameEnd_bg.loadImage("menu/emojigraph72.png");
    gameEnd_font.loadFont("font/NewMedia Fett.ttf", 12);
    
    //minigame
    catchGame.setup(ofxAccelerometer.getForce(), control);
    timer = 0;
    //elements
    D4.loadImage("visualcue/d4.png");
    D6.loadImage("visualcue/d6.png");
    D8.loadImage("visualcue/d8.png");
    D12.loadImage("visualcue/d12.png");
    D20.loadImage("visualcue/d20.png");
    
    condition = LEVEL_0;
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
                char_A.condition = C_DEAD;
            }
            
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = true;
            }
        }
        else if (bData && bData->name == "footSenser"){
            numFootContacts_A++;
            if (bData&&bData->name == "thorn") {
                char_A.condition = C_DEAD;
            }
            
            if (bData&&bData->name == "door" && condition != MAIN_MEUN) {
                levelOver_A = true;
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
            if (bData&&bData->name == "door" && condition != MAIN_MEUN && !bInSky_A) {
                levelOver_A = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_A--;
            if (bData&&bData->name == "door" && condition != MAIN_MEUN && !bInSky_A) {
                levelOver_A = false;
            }
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
                char_B.condition = C_DEAD;
            }
            if (bData&&bData->name == "door" && condition != MAIN_MEUN && !bInSky_B) {
                levelOver_B = true;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B++;
            if (bData&&bData->name == "thorn") {
               char_B.condition = C_DEAD;
            }
            if (bData&&bData->name == "door" && condition != MAIN_MEUN&& !bInSky_B) {
                levelOver_B = true;
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
            if (bData&&bData->name == "door" && condition != MAIN_MEUN && !bInSky_B) {
                levelOver_B = false;
            }
        }else if (bData && bData->name == "footSenser"){
            numFootContacts_B--;
            if (bData&&bData->name == "door" && condition != MAIN_MEUN && !bInSky_B) {
                levelOver_B = false;
            }
        } 
    }
}
//--------------------------------------------------------------
void testApp::update(){
    
    switch (condition) {
        case MAIN_MEUN:{
            char_A.character.setPosition(0, 0);
            char_B.character.setPosition(0, 0);
            camera_A.set(0, 0);
            camera_B.set(0, 0);
            
            if (control.bAllTouch) {
                timer ++;
                if (timer>50) {
                    timer = 0;
                    condition = LEVEL_0;
                    levelRester = true;
                }
            }
        }break;
            
        case LEVEL_0:{
            LEVEL_UPDATE_0();
        }break;
           
        case LEVEL_1:{
            LEVEL_UPDATE_1();
        }break;
            
        case LEVEL_2:{
            LEVEL_UPDATE_2();
        }break;
            
        case LEVEL_3:{
            LEVEL_UPDATE_3();
        }break;
            
        case LEVEL_4:{
            LEVEL_UPDATE_4();
        }break;
            
        case LEVEL_5:{
            LEVEL_UPDATE_5();
        }break;
            
        case LEVEL_6:{
            LEVEL_UPDATE_6();
        }break;
    }
    
}
//--------------------------------------------------------------
void testApp::gamePlay(int level){
    
    for (int i=0; i<birds_A.size(); i++) {
        birds_A[0].update();
    }
    
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
    position(level);
    //control char_A-------------------------------
    if (ofxAccelerometer.getForce().x<-0.3 && rope_A.condition == R_NO_USE && rope_B.condition != R_SWING&& !bInSky_A&&char_A.condition != C_MINIGAME) {
        char_A.condition = C_PUSH_ROPE;
        rope_A.hook_pct  = 0;
        rope_A.condition = R_PUSH;
    }//charA pushRope
    if (char_A.condition == C_DEAD) {
        rope_B.condition = R_DESTROY;
    }
    
    if (char_A.condition != C_DEAD&&char_A.condition != C_MINIGAME) {
       
        
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
        
        else if (control.bTouch[0]&&!control.bTouch[1]) {//charA left
            if (rope_A.condition == R_NO_USE) {
                char_A.condition = C_LEFT;
            }
            if (rope_B.condition == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
       else if(control.bTouch[1]&&!control.bTouch[0]){//charA right
            if (rope_A.condition  == R_NO_USE) {
                char_A.condition = C_RIGHT;
            }
            if (rope_B.condition  == R_SWING) {
                rope_B.condition  = R_DESTROY;
            }
        }
        
      
        
       else if (!control.bTouch[0]&&!control.bTouch[1]) {//charA noPress
            
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
    }
    
    //control char_B-------------------------------
    if (ofxAccelerometer.getForce().x>0.3 && rope_B.condition  == R_NO_USE && rope_A.condition != R_SWING && !bInSky_B&&char_B.condition != C_MINIGAME) {
        char_B.condition = C_PUSH_ROPE;
        rope_B.hook_pct = 0;
        rope_B.condition  = R_PUSH;
        
    }//charB pushRope
    
    if (char_B.condition == C_DEAD) {
        rope_A.condition = R_DESTROY;
    }
    
    if (char_B.condition != C_DEAD&&char_B.condition != C_MINIGAME) {
                
        if (control.bTouch[2]&&!control.bTouch[3]) {//charB left
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_LEFT;
            }
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        else if(control.bTouch[3]&&!control.bTouch[2]){//charB right
            if (rope_B.condition == R_NO_USE) {
                char_B.condition = C_RIGHT;
            }
            
            if (rope_A.condition == R_SWING) {
                rope_A.condition = R_DESTROY;
            }
        }
        
        else if(control.bTouch[2]&&control.bTouch[3]){//charB double press
            if (rope_A.condition == R_PUSH) {
                ofPoint dis =  hook_end_A - char_pos_B;
                if ( fabs(dis.x)< 50 && dis.y>=-60) {
                    char_B.condition = C_HOOK_ROPE;
                    char_A.condition = C_SWING_ROPE;
                    rope_A.condition = R_SWING;
                }
            }
        }
        else if (!control.bTouch[2]&&!control.bTouch[3]) {//charB noPress
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

    }
    //rope--------------------------------------
    rope_A.update();
    rope_B.update();
    
    //Character-------------------------------
    char_A.update();
    char_B.update();
    
    //emoji-------------------------------
    emoji_A.update(char_A.character.getPosition(), char_A.moveLeft);
    emoji_B.update(char_B.character.getPosition(), char_B.moveLeft);
    emoji_A.control();
    emoji_B.control();
    //dog-------------------------------


        //rabit-------------------------------
//        rabit_A.update();
//        rabit_B.update();
//    
    
}
//--------------------------------------------------------------
void testApp::gameEnd(int level){
    float orgRadius = 180;
    int max;
    int number[5];
    float angle[5];
    float radius[5];
    ofPoint pts[5];
    ofPoint orgPos(ofGetWidth()/2, ofGetHeight()/2);
    ofPoint icon_pts[5];
    ofPolyline path;
    float offSet = 30;
    number[0] = emoji_A.num_love+emoji_B.num_love;
    number[1] = emoji_A.num_happy+ emoji_B.num_happy;
    number[2] = emoji_A.num_laughing+ emoji_B.num_laughing;
    number[3] = emoji_A.num_angry + emoji_B.num_angry;
    number[4] = emoji_A.num_surprise+ emoji_B.num_surprise;
    
    //    number[0] = 10;
    //    number[1] = 20;
    //    number[2] = 30;
    //    number[3] = 40;
    //    number[4] = 50;
    //
    angle[0] = 90;
    angle[1] = 150;
    angle[2] = 210;
    angle[3] = 330;
    angle[4] = 30;
    
    for (int i=1; i<5; i++) {
        max = MAX(number[i], number[i-1]);
    }
    
    radius[0] = ofMap(number[0], 0, max, 50, orgRadius, true);
    radius[1] = ofMap(number[1], 0, max, 50, orgRadius, true);
    radius[2] = ofMap(number[2], 0, max, 50, orgRadius, true);
    radius[3] = ofMap(number[3], 0, max, 50, orgRadius, true);
    radius[4] = ofMap(number[4], 0, max, 50, orgRadius, true);
    
    ofSetColor(255);
    skyBg.draw(0, 0);
    
    for (int i=0; i<5; i++) {
        pts[i].x =  radius[i]*cos(angle[i]*DEG_TO_RAD);
        pts[i].y = radius[i]*-sin(angle[i]*DEG_TO_RAD);
        icon_pts[i].x = (orgRadius+offSet)*cos(angle[i]*DEG_TO_RAD);
        icon_pts[i].y = (orgRadius+offSet)*-sin(angle[i]*DEG_TO_RAD);
        path.addVertex(pts[i]);
    }
    path.close();
    
    
    // draw the mesh
    ofMesh mesh;
    ofMesh meshBG;
    meshBG.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    vector < ofPoint > meshPts = path.getVertices();
    for (int i = 0; i < meshPts.size(); i++){
        meshBG.addVertex(meshPts[i]);
    }
    
    
    ofPushMatrix();
    ofTranslate(orgPos);
    ofSetColor(144,143,142,125);
    ofFill();
    meshBG.draw();
    //    for (int i=0; i<5; i++) {
    //        ofSetColor(255, 30, 100);
    //        ofLine(0,0, pts[i].x, pts[i].y);
    //    }
    //    ofSetColor(0,125);
    //    ofSetLineWidth(1);
    //    path.draw();
    ofPopMatrix();
    
    ;
    for (int i=0; i<5; i++) {
        ofPushMatrix();
        ofRectangle rect;
        rect = gameEnd_font.getStringBoundingBox(ofToString(number[i]), 0, 0);
        ofTranslate(orgPos.x+icon_pts[i].x,orgPos.y+icon_pts[i].y);
        
        if (i==0) {
            ofRotateZ(0);
        }
        if (i==1) {
            ofRotateZ(-60);
        }
        if (i==2) {
            ofRotateZ(-120);
        }
        if (i==3) {
            ofRotateZ(-240);
        }
        if (i == 4) {
            ofRotateZ(-300);
        }
        
        ofSetColor(30);
        gameEnd_font.drawString(ofToString(number[i]),-rect.getWidth()/2,-rect.getHeight()/2);
        ofPopMatrix();
    }
    
    
    ofSetColor(255);
    gameEnd_bg.draw(0,0);
    
    number[0] = 0;
    number[1] = 0;
    number[2] = 0;
    number[3] = 0;
    number[4] = 0;
    
}
//--------------------------------------------------------------
void testApp::draw(){
    ofPoint pt[2];
    float radius = 40;
    switch (condition) {
        case MAIN_MEUN:{
            main_menu.draw();
            control.draw();
        } break;
        case LEVEL_0:{
            LEVEL_DRAW_0();
        }break;
        case LEVEL_1:{
            LEVEL_DRAW_1();
        }break;
        case LEVEL_2:{
            LEVEL_DRAW_2();
        }break;
        case LEVEL_3:{
            LEVEL_DRAW_3();
        }break;
        case LEVEL_4:{
            LEVEL_DRAW_4();
        }break;
        case LEVEL_5:{
            LEVEL_DRAW_5();
        }break;
        case LEVEL_6:{
           LEVEL_DRAW_6();
        }break;
    }
    
    ofDrawBitmapStringHighlight("world: " + ofToString(char_A.getPos,2)+"\nScreen: "+ofToString(char_A.getPos+screen_A,2), 50,50);
    ofDrawBitmapStringHighlight("world: " + ofToString(char_B.getPos,2)+"\nScreen: "+ofToString(char_B.getPos+screen_B,2), 750,700);

}
//-------------------------------------------------------------
void testApp::drawScene(int level){
    
    sky.drawBg();
    
        ofPushMatrix();
        ofTranslate(screen_A);
        ground_A.draw();
        ground_A.drawPolyLine();
        thorns_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        ground_B.draw();
        ground_B.drawPolyLine();
        thorns_B.draw();
        ofPopMatrix();
        
        sky.drawCloud();
    
        for (int i=0; i<birds_A.size(); i++) {
            birds_A[i].draw();
        }
    
       //char draw
        ofPushMatrix();
        ofTranslate(screen_A);
        char_A.draw();
        emoji_A.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(screen_B);
        char_B.draw();
        emoji_B.draw();
        ofPopMatrix();
        // cub
//    ofPushMatrix();
    
//    for (int i=0; i<d4.size(); i++) {d4[i].draw();}
//    for (int i=0; i<d6.size(); i++) {d6[i].draw();}
//    for (int i=0; i<d8.size(); i++) {d8[i].draw();}
//    for (int i=0; i<d12.size(); i++) {d12[i].draw();}
//    for (int i=0; i<d20.size(); i++) {d20[i].draw();}
//    ofPopMatrix();
    
        //draw swing rope A
        rope_A.draw_swing(screen_B);
        rope_A.draw_push();
        rope_B.draw_swing(screen_A);
        rope_B.draw_push();
    
    
            
}
//--------------------------------------------------------------
void testApp::exit(){

}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
   
    if (condition !=MAIN_MEUN) game_menu.touchDown(touch.x, touch.y,touch.id);
    control.touchDown(touch.x, touch.y,touch.id);
    ofPoint pos(touch.x, touch.y);
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
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}
//--------------------------------------------------------------
void testApp::position(int level){

    bool A[10],B[10];
    float catchUpSpeed = 0.05f;
    ofPoint catch_A, catch_B;
   
//    if (level == 0) {
        char_A.getPos.x<0? A[0] = true: A[0] =false;
        char_B.getPos.x<0? B[0] = true: B[0] =false;
   
        char_A.getPos.x>1690? A[1] = true: A[1] =false;
        char_B.getPos.x>1690? B[1] = true: B[1] =false;
        
        //camera setup
        if (A[0]) {
            catch_A.x = 0;
            catch_A.y = char_A.getPos.y;
        }else if(A[1]){
            catch_A.x = 1690;
            catch_A.y = -180;
        }else{
            catch_A.x = char_A.getPos.x;
            catch_A.y = char_A.getPos.y;
        }
        
        if (B[0]) {
            catch_B.x = 0;
            catch_B.y = char_B.getPos.y;
        }else if(B[1]){
            catch_B.x = 1690;
            catch_B.y = 180;
        }else{
            catch_B.x = char_B.getPos.x;
            catch_B.y = char_B.getPos.y;
        }

//    }
    
    
    if (rope_B.condition != R_SWING && char_A.condition != C_MINIGAME) {
        camera_A.x = catchUpSpeed * catch_A.x + (1-catchUpSpeed) * camera_A.x;
        camera_A.y = catchUpSpeed * catch_A.y + (1-catchUpSpeed) * camera_A.y;
    }
       
    if (rope_A.condition != R_SWING ) {
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
//  rope_end_A = hook_end_B - screen_A;
   
    rope_start_B = hook_start_A - screen_B;
//  rope_end_B = hook_end_A - screen_B;

}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_0(){
    if (levelRester) {
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(0, 0, world_A);
        ground_B.setup(0, 1, world_B);
        
        cue.clear();
        
        ttVisualcue temp;
        temp.setup(D20,422,-16,screen_A,0);
        temp.bFix = true;
        cue.push_back(temp);
        
        temp.setup(D20,1004,-16,screen_B,1);
        temp.bFix = false;
        cue.push_back(temp);
        
        temp.setup(D20,1608,-16,screen_A,0);
        temp.bFix = false;
        cue.push_back(temp);
        
        
        levelRester = false;
    }
    else{
        if (!game_menu.show) {
            gamePlay(0);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                
                char_A.character.setPosition(100, 0);
                char_B.character.setPosition(-100, 0);
                char_A.condition = C_STOP;
                char_B.condition = C_STOP;
                rope_A.condition = R_NO_USE;
                rope_B.condition = R_NO_USE;
                
                condition = LEVEL_1;
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_0(){
    ofPoint pt[2];
    float radius = 40;
    
    drawScene(0);
    
    ofSetColor(255, 255, 255);

    for (int i=0; i<3; i++) {
        cue[i].draw();
    }

    ofPushMatrix();
    ofTranslate(screen_A);
    cue[1].draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(screen_B);
    cue[2].draw();
    ofPopMatrix();
    
    game_menu.draw();
    
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    
    if (bStatistics) {gameEnd(0);}
    
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_1(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(1, 0, world_A);
        ground_B.setup(1, 1, world_B);
        ttBirds bird;
        bird.setup(world_A, bird_Render, char_A, 0, 300, 0);
        birds_A.push_back(bird);
        levelRester = false;
    }else{
        if (!game_menu.show) {
            gamePlay(1);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                
                bStatistics = false;
                condition = LEVEL_2;
            }
        }
    }

}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_2(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(2, 0, world_A);
        ground_B.setup(2, 1, world_B);
        levelRester = false;
    }else{
        
        
        if (!game_menu.show) {
            gamePlay(2);
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                condition = LEVEL_3;
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_3(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(3, 0, world_A);
        ground_B.setup(3, 1, world_B);
        ttBirds bird;
        bird.setup(world_A, bird_Render, char_A, 0, 300, 0);
        birds_A.push_back(bird);
        levelRester = false;
    }else{
        if (!game_menu.show) {
            gamePlay(3);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                condition = LEVEL_4;
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_4(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(4, 0, world_A);
        ground_B.setup(4, 1, world_B);
        ttBirds bird;
        bird.setup(world_A, bird_Render, char_A, 0, 300, 0);
        birds_A.push_back(bird);
        levelRester = false;
    }else{
        if (!game_menu.show) {
            gamePlay(4);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                condition = LEVEL_5;
            }
        }
    }

}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_5(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(5, 0, world_A);
        ground_B.setup(5, 1, world_B);
        ttBirds bird;
        bird.setup(world_A, bird_Render, char_A, 0, 300, 0);
        birds_A.push_back(bird);
        levelRester = false;
    }else{
        if (!game_menu.show) {
            gamePlay(5);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                condition = LEVEL_6;
            }
        }
    }

}
//--------------------------------------------------------------
void testApp::LEVEL_UPDATE_6(){
    if (levelRester) {
        char_A.character.setPosition(0, 0);
        char_B.character.setPosition(0, 0);
        char_A.condition = C_STOP;
        char_B.condition = C_STOP;
        rope_A.condition = R_NO_USE;
        rope_B.condition = R_NO_USE;
        
        ground_A.destroy();
        ground_B.destroy();
        ground_A.setup(6, 0, world_A);
        ground_B.setup(6, 1, world_B);
        ttBirds bird;
        bird.setup(world_A, bird_Render, char_A, 0, 300, 0);
        birds_A.push_back(bird);
        levelRester = false;
    }else{
        if (!game_menu.show) {
            gamePlay(6);
            
        }
        if (game_menu.goMain) {
            game_menu.goMain = false;
            condition = MAIN_MEUN;
        }
        
        if (levelOver_A && levelOver_B) {
            char_A.condition = C_MINIGAME;
            char_B.condition = C_MINIGAME;
            rope_A.condition = R_MINIGAME;
            rope_B.condition = R_MINIGAME;
            catchGame.update();
        }
        
        if (catchGame.bFinish) {
            bStatistics = true;
            catchGame.bFinish = false;
            catchGame.indicator = 0;
            levelOver_A = false;
            levelOver_B = false;
        }
        
        if (bStatistics && control.bAllTouch) {
            timer ++;
            if (timer > 70) {
                timer = 0;
                bStatistics = false;
                condition = MAIN_MEUN;
            }
        }
    }

}

//--------------------------------------------------------------
void testApp::LEVEL_DRAW_1(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(1);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(1);
    }
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_2(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(2);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(2);
    }
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_3(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(3);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(3);
    }
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_4(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(4);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(4);
    }
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_5(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(5);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(5);
    }
    control.draw();
}
//--------------------------------------------------------------
void testApp::LEVEL_DRAW_6(){
    ofPoint pt[2];
    float radius = 40;
    drawScene(6);
    game_menu.draw();
    if (levelOver_A && levelOver_B) {
        catchGame.draw();
        pt[0].x = catchGame.cursorIn.x + radius*cos(0*DEG_TO_RAD);
        pt[0].y = catchGame.cursorIn.y + radius*-sin(0*DEG_TO_RAD);
        pt[1].x = catchGame.cursorIn.x + radius*cos(180*DEG_TO_RAD);
        pt[1].y = catchGame.cursorIn.y + radius*-sin(180*DEG_TO_RAD);
        rope_A.draw_minigame(pt[0]);
        rope_B.draw_minigame(pt[1]);
    }
    if (bStatistics) {
        gameEnd(6);
    }
    control.draw();
}
