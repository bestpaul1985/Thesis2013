// press "a" or "d" to move, hold 'f' to pull rope


#include "testApp.h"

bool sortVertically(  basicSprite * a, basicSprite * b ) { 
	return a->pos.y > b->pos.y; 
}   

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    spriteRenderer->loadTexture("boySpritesAll.png", 2040, GL_NEAREST);
    
    spriteRenderer2 =  new ofxSpriteSheetRenderer(1, 10000, 0, 150);
    spriteRenderer2->loadTexture("dog7.png", 1950, GL_NEAREST);
    
	ofEnableAlphaBlending();
    
    
   
    basicSprite * newSprite = new basicSprite();
    newSprite->pos.set(300,400);
    newSprite->animation = BOY;
    sprites[0] =newSprite;

    basicSprite * newSprite2 = new basicSprite();
    newSprite2->pos.set(400,400);
    newSprite2->animation = GIRL;
    sprites[1] =newSprite2;
	
    cout<<spriteRenderer->getSpriteSheetWidth()<<endl;
    cout<<spriteRenderer->getTileSize()<<endl;

    left = false;
    right = false;
    rope = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
	spriteRenderer->clear();
    spriteRenderer2->clear();
//    if (left || right) {
//        spriteRenderer->update(ofGetElapsedTimeMillis());
//    }else{
//        spriteRenderer->update(0);
//    }
    
    spriteRenderer->update(ofGetElapsedTimeMillis());
    spriteRenderer2->update(ofGetElapsedTimeMillis());
    spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
    
     spriteRenderer2->addCenteredTile(&sprites[1]->animation, sprites[1]->pos.x, sprites[1]->pos.y);
    //   bool addCenteredTile     (animation_t* sprite,         float x, float y, int layer = -1,                        flipDirection f = F_NONE, float scale = 1.0,          int r=255, int g=255, int b=255, int alpha=255);
    
	
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofPushMatrix();
    ofTranslate(0, 0);
	spriteRenderer->draw();
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(100, 0);
	spriteRenderer2->draw();
    ofPopMatrix();
    ofDrawBitmapStringHighlight("press 'a' or 'd' to move, hold 'f' to pull rope    "+ofToString( sprites[1]->animation.frame), 100, 100);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'a') {
       
        sprites[1]->animation.frame +=1;
    }
    
    if (key == 'd') {
        sprites[1]->animation.frame -=1;
    }
    
    if (key=='f') {
        rope = true;
    }

}
void testApp::keyReleased(int key){
    if (key == 'a') {
        left = false;

    }
    
    if (key == 'd') {
       
        right = false;
    }

    if (key=='f') {
        rope = false;
        sprites[1]->animation.loops = 1;
    }
}
void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}

