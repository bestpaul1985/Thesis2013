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
	ofEnableAlphaBlending();
    
    
    for (int i =0; i<2; i++) {
        basicSprite * newSprite = new basicSprite();
		newSprite->pos.set(300,400);
		newSprite->speed=0;
        if (i==0) {
            newSprite->animation = walkAnimation;
        }else{
            newSprite->animation = ropeAnimation;
        }
		sprites.push_back(newSprite);
    }
	
	
    cout<<spriteRenderer->getSpriteSheetWidth()<<endl;
    cout<<spriteRenderer->getTileSize()<<endl;

    left = false;
    right = false;
    rope = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
	spriteRenderer->clear();
    
//    if (left || right) {
//        spriteRenderer->update(ofGetElapsedTimeMillis());
//    }else{
//        spriteRenderer->update(0);
//    }
    
    spriteRenderer->update(ofGetElapsedTimeMillis());
    
    if (rope) {
        
        spriteRenderer->addCenteredTile(&sprites[1]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
        
    }else{
         
        spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
    }
    
    
	
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	spriteRenderer->draw();
    
    ofDrawBitmapStringHighlight("press 'a' or 'd' to move, hold 'f' to pull rope", 100, 100);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'a') {
        sprites[0]->pos.x-=5;
        left = true;
        
    }
    
    if (key == 'd') {
        sprites[0]->pos.x+=5;
        right = true;
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

