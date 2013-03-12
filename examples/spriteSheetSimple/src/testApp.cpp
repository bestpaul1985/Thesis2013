#include "testApp.h"

bool sortVertically(  basicSprite * a, basicSprite * b ) { 
	return a->pos.y > b->pos.y; 
}   

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(0);
	spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 32);
	spriteRenderer->loadTexture("spriteSheetExample.png", 256, GL_NEAREST);
	ofEnableAlphaBlending();
    
    for(int i=0;i<1;i++){
		basicSprite * newSprite = new basicSprite();
		newSprite->pos.set(ofRandom(0,ofGetWidth()),-16);
		newSprite->speed=ofRandom(1,5);
		newSprite->animation = walkAnimation;
		newSprite->animation.frame_duration /= newSprite->speed;
		newSprite->animation.index = (int)ofRandom(0,4)*8;
		sprites.push_back(newSprite);
	}
    
}

//--------------------------------------------------------------
void testApp::update(){
	spriteRenderer->clear();
	spriteRenderer->update(ofGetElapsedTimeMillis());	
	sort( sprites.begin(), sprites.end(), sortVertically );
	
	if(sprites.size()>0){
		for(int i=sprites.size()-1;i>=0;i--){
            sprites[i]->pos.x = 0;
            sprites[i]->pos.y = 0;
//			sprites[i]->pos.y+=sprites[i]->speed;
//            sprites[i]->pos.x+=ofRandom(-2,2);
			if(sprites[i]->pos.y > ofGetHeight()+16){
				delete sprites[i];
				sprites.erase(sprites.begin()+i);
			}
			else
				spriteRenderer->addCenteredTile(&sprites[i]->animation, sprites[i]->pos.x, sprites[i]->pos.y);
		}
	}
	

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackgroundGradient(ofColor::azure, ofColor::aquamarine);

    ofTranslate(mouseX, mouseY);
    float scl = ofMap(mouseY, 0, ofGetHeight(), 0.2, 6);
    ofScale(scl, scl);
	spriteRenderer->draw();
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    }
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}

