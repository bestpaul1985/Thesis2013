//
//  ttChar.cpp
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//
#include "ttChar.h"

//----------------------------------------------
void ttChar::setup(ofxBox2d &world, ofPoint SetPos, int CharNum){
    charNum = CharNum;
    character.setPhysics(4.0f, 0.1f, 0.1);
    character.setup(world.getWorld(), SetPos.x, SetPos.y, 15, 33);
    character.body->SetLinearDamping(b2dNum(0.5));
    character.body->SetFixedRotation(true);
    
    spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    
    if (charNum == 0) {
        spriteRenderer->loadTexture("sprites/grilSpritesAll.png", 2040, GL_NEAREST);
        for (int i =0; i<2; i++) {
            basicSprite * newSprite = new basicSprite();
            newSprite->pos.set(0,0);
            newSprite->speed=0;
            if (i==0) {
                newSprite->animation = walkAnimation_boy;
            }else{
                newSprite->animation = ropeAnimation_boy;
            }
            sprites.push_back(newSprite);
        }
    }
    
    if (charNum == 1) {
        spriteRenderer->loadTexture("sprites/boySpritesAll.png", 2040, GL_NEAREST);
        for (int i =0; i<2; i++) {
            basicSprite * newSprite = new basicSprite();
            newSprite->pos.set(0,0);
            newSprite->speed=0;
            if (i==0) {
                newSprite->animation = walkAnimation_girl;
            }else{
                newSprite->animation = ropeAnimation_girl;
            }
            sprites.push_back(newSprite);
        }
    }
    
    moveLeft = false;
    condition = C_STOP;
    getPos = SetPos;
}

//----------------------------------------------
void ttChar::update(){
    
    int spritesNum = 0;
    ofPoint frc;
    float time;
    
    spriteRenderer->clear();
    
    // change conditions
    switch (condition) {
        case C_STOP:{
            spriteRenderer->update(0);
            sprites[0]->animation.frame = 0;
            frc.x = character.getVelocity().x * -20;
            sprites[1]->animation.loops = 1;   
        }break;
                
        case C_LEFT:{
            moveLeft = true;
            if ( character.getVelocity().x > -5 ) frc.x = -50;
          
        }break;

        case C_RIGHT:{
            moveLeft = false;
            if ( character.getVelocity().x < 5 ) frc.x = 50;
        }break;
       
        case C_PUSH_ROPE:{
            frc.x = character.getVelocity().x * -30;
            spritesNum = 1;
        }break;
            
        case C_HOOK_ROPE:{
    
        }break;
    }
    
    //add force on char
    character.addForce(frc, 10);
    
    //update sprites
    if (condition == C_PUSH_ROPE) {
       time = ofGetElapsedTimeMillis(); 
    }
    else if (character.getVelocity().x<0.3 && character.getVelocity().x>-0.3) {
        time = 0;
    }
    else{
        time = ofGetElapsedTimeMillis();
    }
    
    spriteRenderer->update(time);
    sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
    spriteRenderer->addCenteredTile(&sprites[spritesNum]->animation, 0,0);
    
    getPos = character.getPosition();
}
//----------------------------------------------
void ttChar::draw(){
//    character.draw();
    
    ofPushMatrix();
    ofTranslate(character.getPosition().x, character.getPosition().y);
    if (charNum == 0) {
        moveLeft? ofScale(1, 1):ofScale(-1, 1);
    }
    
    if (charNum == 1) {
        moveLeft? ofScale(-1, 1):ofScale(1, 1);
    }
    
    spriteRenderer->draw();
    ofPopMatrix();
}