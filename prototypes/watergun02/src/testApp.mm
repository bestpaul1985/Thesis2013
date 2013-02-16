#include "testApp.h"

//--------------------------------------------------------------
bool testApp::shouldRemoveBullet(Bullet &b) {
    
    if(b.bRemove) return true;
    
    
    bool bRemove = false;
    
    // get the rectangle of the OF world
    ofRectangle rec = ofGetCurrentViewport();
    
    // check if the bullet is inside the world
    if(rec.inside(b.pos) == false) {
        bRemove = true;
    }
    
    return bRemove;
}
//--------------------------------------------------------------
bool testApp::shouldRemoveEnemy(Enemy &b) {
    return b.bRemove;
}

//--------------------------------------------------------------
void testApp::setup(){	
	ofxAccelerometer.setup();
	ofBackground(30,30,30);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    //********gameEvent**********************
    bFire = false;
    enemyKilled = 0;
    maxBullets = 30;
    pos.set(50, ofGetHeight()/2);
    
    ofVec2f p(650, 800);
    holes.push_back(p);

    ofAddListener(GameEvent::events, this, &testApp::gameEvent);
    bulletsNum = 15;
    refillPos.set(20, 850);
    //********world**************************
    worldP1.init();
    worldP1.setGravity(0, 100);
    //  worldP1.createBounds();
    ofPoint one(0,ofGetHeight());
    ofPoint two(3000,ofGetHeight());
    worldP1.createGround(one, two);
    worldP1.setIterations(1, 1);
    worldP1.setFPS(60);
    worldP1.createBounds();
   
    worldP2.init();
    worldP2.setGravity(0, 100);
    worldP2.createGround(one, two);
    worldP2.setIterations(1, 1);
    worldP2.setFPS(60);
    worldP2.createBounds();
    
    
    //**********buttons****************
    P1L.setup(10, ofGetHeight()-120, 0, 0, 0);
    P1R.setup(20+115, ofGetHeight()-120, 1, 0, 0);
    P1J.setup(ofGetWidth()-190, ofGetHeight()-115, 0, 0, 0);
    P1F.setup(ofGetWidth()-105, ofGetHeight()-155, 1, 0, 0);
    bFixedButtonP1 = false;
    
    //***********map************************
    if (XML.loadFile("tutorialLevelP1.xml")) {
        int strokeNum = XML.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML.pushTag("STROKE",i);
            int ptNum = XML.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML.getValue("PT:X", 0, j);
                    int y = XML.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2);
                tempPolyline.create(worldP1.getWorld());
                polyLines1.push_back(tempPolyline);
               
            }
            XML.popTag();
        }
    }
    
    if (XML.loadFile("tutorialLevelP1.xml")) {
        int strokeNum = XML.getNumTags("STROKE");
        for (int i=0; i<strokeNum; i++) {
            XML.pushTag("STROKE",i);
            int ptNum = XML.getNumTags("PT");
            if (ptNum>0) {
                ofxBox2dPolygon tempPolyline;
                for (int j=0; j<ptNum; j++) {
                    int x = XML.getValue("PT:X", 0, j);
                    int y = XML.getValue("PT:Y", 0, j);
                    ofPoint tempP;
                    tempP.set(x-2220, y-1514);
                    tempPolyline.addVertex(tempP);
                }
                tempPolyline.setPhysics(0, 0, 0.2);
                tempPolyline.create(worldP2.getWorld());
                polyLines2.push_back(tempPolyline);
                
            }
            XML.popTag();
        }
    }
    
    //***************character**********************************
    character1.setPhysics(3, 0, 0.5);
    character1.setup(worldP1.getWorld(), 200, 500, 30,30);
    character1.body->SetFixedRotation(true);
    character1.setDamping(0.98f);`
}

//--------------------------------------------------------------
void testApp::gameEvent(GameEvent &e) {
    
    cout << "Game Event: "+e.message << endl;
    e.enemy->timeEnemyKilled = ofGetElapsedTimef();
    e.enemy->bSquashed = true;
    
    e.bullet->bRemove = true;
    
    enemyKilled ++;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (ofGetFrameNum()<10){
        
        //set it to mirror if it isn't already
        
        if (!ofxiPhoneExternalDisplay::isMirroring()){
            
            //code from the internet to get it to mirror on exteral screens
            
            ofxiPhoneExternalDisplay::mirrorOn();
            
            ofxiPhoneExternalDisplay::isMirroring();
            
        }
    }
    
    //***********world*******************************
    worldP1.update();
    worldP2.update();

    //*********** diffP1 ********************************
    diffP1 = character1.getPosition()-lastPosP1;
    
    //***********character1*******************************
    ofPoint frc1(0,0);
    ofPoint frc2(0,0);
    
    if (P1L.bPressed && fabs(diffP1.y)< 1){
        frc1.x = -100;
    }else if(P1L.bPressed && fabs(diffP1.y)> 1){
        frc1.x = -50;
    }
    
    if (P1R.bPressed && fabs(diffP1.y)< 1){
        frc1.x = 100;
    }else if(P1R.bPressed && fabs(diffP1.y)> 1){
        frc1.x = 50;
    }
    
    character1.addForce(frc1,10);
    
    
    //*********** get lastPos ***************
    lastPosP1 = character1.getPosition();
    
    //*********** gameEvent******************
    if((int)ofRandom(0, 60)==10 && enemy.size()< 3) {
        
        Enemy newEnemy;
        newEnemy.setPhysics(0.4, 0.53, 0.31);
        ofRectangle rect;
        rect.set(holes[0].x, holes[0].y, 15, 15);
        newEnemy.setup(worldP2.getWorld(), rect);
        ofPoint forc(-10,0);
        newEnemy.addForce(forc, 10);
        enemy.push_back(newEnemy);
    }
    
    for(int i=0; i<enemy.size(); i++) {
        
        enemy[i].update();
        float   size = enemy[i].getWidth();
        ofPoint pos  = enemy[i].getPosition();
        if(pos.x > ofGetWidth()-size)  enemy[i].pos.x = -size;
        if(pos.x < -size)              enemy[i].pos.x = ofGetWidth()-size;
        if(pos.y > ofGetHeight()+size) enemy[i].pos.y = -size;
        if(pos.y < -size)              enemy[i].pos.y = ofGetHeight()-size;
    }
    
    ofRemove(enemy, shouldRemoveEnemy);
    
    for(int i=0; i<bullets.size(); i++) {
        bullets[i].update();
    }
    
    ofRemove(bullets, shouldRemoveBullet);
    
    for(int i=0; i<bullets.size(); i++) {
        for(int j=0; j<enemy.size(); j++) {
            
            ofVec2f a       = bullets[i].pos;
            ofVec2f b       = enemy[j].getPosition();
            float   minSize = enemy[j].getWidth() + bullets[i].size;
           
            if(a.distance(b) < minSize && enemy[j].bSquashed == false) {
                
                static GameEvent newEvent;
                newEvent.message = "BUG HIT";
                newEvent.enemy    = &enemy[j];
                newEvent.bullet  = &bullets[i];
                
                ofNotifyEvent(GameEvent::events, newEvent);
            }
            
        }
 
    }
    
    
    ofVec2f a = character1.getPosition();
    ofVec2f b = refillPos;
    
    if (a.distance(b)<100) {
    
        if ((int)ofRandom(0,10)==1 && bulletsNum<30) {
            bulletsNum += 1;
            
        }
        
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(242, 208, 59);
    for (int i=0; i<polyLines1.size(); i++) {
        polyLines1[i].draw();
    }
 
    
    ofSetColor(71, 217, 191);
	character1.draw();
    
    ofPushMatrix();
    ofTranslate(character1.getPosition().x+10, character1.getPosition().y+character1.getHeight());
    ofRotateZ(180);
    ofSetColor(31, 117, 151);
    float height = ofMap(bulletsNum, 0, 30, 0, character1.getHeight()*2);
    ofRect(0, 0, 20, height);
    ofPopMatrix();
    //*********buttons******************************************
    
    if (bFixedButtonP1) {
        P1L.bFixed = true;
        P1R.bFixed = true;
        P1J.bFixed = true;
        P1F.bFixed = true;
    }else{
        P1L.bFixed = false;
        P1R.bFixed = false;
        P1J.bFixed = false;
        P1F.bFixed = false;
    }
    P1L.draw();
    P1R.draw();
    P1J.draw();
    P1F.draw();
    
    
    //*********gameEvents***************************************
    
    ofSetColor(245, 128, 146);
    ofRect(refillPos,50,10);
    
    for(int i=0; i<holes.size(); i++) {
        ofSetColor(0,48,86);
        ofCircle(holes[i], 40);
    }
    
    for(int i=0; i<enemy.size(); i++) {
        enemy[i].draw();
    }
    
    for(int i=0; i<bullets.size(); i++) {
        bullets[i].draw();
    }
    

    
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    if (bFixedButtonP1 == false) {
        P1L.touchDown(touch.x, touch.y, touch.id);
        P1R.touchDown(touch.x, touch.y, touch.id);
        P1J.touchDown(touch.x, touch.y, touch.id);
        P1F.touchDown(touch.x, touch.y, touch.id);
    }
    
    if (bFixedButtonP2 == false) {
        P2L.touchDown(touch.x, touch.y, touch.id);
        P2R.touchDown(touch.x, touch.y, touch.id);
        P2J.touchDown(touch.x, touch.y, touch.id);
        P2F.touchDown(touch.x, touch.y, touch.id);
    }
    
    
    
    if (P1J.bPressed && fabs(diffP1.y)< 1){

        
        character1.setVelocity(0, -40);
        
    }
    
    if (P1F.bPressed && bulletsNum > 0){
        
        if(bullets.size() < maxBullets) {
            bFire = true;
            
            Bullet b;
            ofPoint vec(10,0);
            ofVec2f bulletPos = character1.getPosition() + vec;
            
            b.pos     = bulletPos;
            b.vel     = vec * ofRandom(2, 3);
            b.bRemove = false;
            
            // add the bullets to the array
            bullets.push_back(b);
            
            bulletsNum -=1;
            
            cout<<bulletsNum<<endl;
        }
    }

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    if (bFixedButtonP1 == false) {
        P1L.touchMoved(touch.x, touch.y, touch.id);
        P1R.touchMoved(touch.x, touch.y, touch.id);
        P1J.touchMoved(touch.x, touch.y, touch.id);
        P1F.touchMoved(touch.x, touch.y, touch.id);
    }
    if (bFixedButtonP2 == false) {
        P2L.touchMoved(touch.x, touch.y, touch.id);
        P2R.touchMoved(touch.x, touch.y, touch.id);
        P2J.touchMoved(touch.x, touch.y, touch.id);
        P2F.touchMoved(touch.x, touch.y, touch.id);
    }

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    ofRectangle rect1(0,ofGetHeight()/2,ofGetWidth()/2, ofGetHeight());
    ofRectangle rect2(ofGetWidth()/2, ofGetHeight()/2,ofGetWidth(), ofGetHeight());
    ofRectangle rect3(0,0,ofGetWidth()/2, ofGetHeight()/2);
    ofRectangle rect4(ofGetWidth()/2, 0,ofGetWidth(), ofGetHeight()/2);
    if(rect1.inside(touch.x, touch.y))touch.id = 0;
    if(rect2.inside(touch.x, touch.y))touch.id = 1;
    if(rect3.inside(touch.x, touch.y))touch.id = 2;
    if(rect4.inside(touch.x, touch.y))touch.id = 3;
    if (bFixedButtonP1 == false) {
        P1L.touchUp(touch.x, touch.y, touch.id);
        P1R.touchUp(touch.x, touch.y, touch.id);
        P1J.touchUp(touch.x, touch.y, touch.id);
        P1F.touchUp(touch.x, touch.y, touch.id);
    }
    
    if (bFixedButtonP2 == false) {
        P2L.touchUp(touch.x, touch.y, touch.id);
        P2R.touchUp(touch.x, touch.y, touch.id);
        P2J.touchUp(touch.x, touch.y, touch.id);
        P2F.touchUp(touch.x, touch.y, touch.id);
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

