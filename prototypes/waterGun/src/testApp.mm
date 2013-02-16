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
    bFire = false;
    enemyKilled = 0;
    maxBullets = 30;
    pos.set(50, ofGetHeight()/2);
    int nHoldes = 3;
    for(int i=0; i<nHoldes; i++) {
        ofVec2f p(ofRandom(ofGetWidth()/2+150, ofGetWidth())-30, ofGetHeight()/4 *(1+i));
        holes.push_back(p);
    }
    
    ofAddListener(GameEvent::events, this, &testApp::gameEvent);
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
    
    if((int)ofRandom(0, 60)==10) {
        
        int randomHole = ofRandom(holes.size());
        
        Enemy newEnemy;
        newEnemy.pos = holes[randomHole];
        newEnemy.vel.set(ofRandom(-1, 0), ofRandom(-0.9, 0.9));
        enemy.push_back(newEnemy);
    }
    
    for(int i=0; i<enemy.size(); i++) {
        
        enemy[i].update();
        float   size = enemy[i].size;
        ofVec2f pos  = enemy[i].pos;
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
            ofVec2f b       = enemy[j].pos;
            float   minSize = enemy[j].size;
            
            if(a.distance(b) < minSize) {
                
                static GameEvent newEvent;
                newEvent.message = "BUG HIT";
                newEvent.enemy    = &enemy[j];
                newEvent.bullet  = &bullets[i];
                
                ofNotifyEvent(GameEvent::events, newEvent);
            }
            
        }
    }

    cout<< holes[0]<<endl;
}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i=0; i<holes.size(); i++) {
        ofSetColor(220,0,30);
        ofCircle(holes[i], 25);
        ofSetColor(220,0,200);
        ofCircle(holes[i], 20);
    }
    
    for(int i=0; i<enemy.size(); i++) {
        enemy[i].draw();
    }
    
    for(int i=0; i<bullets.size(); i++) {
        bullets[i].draw();
    }
    
    ofSetColor(10);
    ofDrawBitmapString("Bullets "+ofToString(bullets.size())+"\nEnemy Killed: "+ofToString(enemyKilled), 20, 20);
    
    ofSetColor(0, 220, 30);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(pos.x, pos.y, 50, 50);

}

//--------------------------------------------------------------
void testApp::exit(){
    
       
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

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

