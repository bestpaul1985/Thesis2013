//
//  ttBirds.cpp
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#include "ttBirds.h"

void ttBirds::setup(ofxBox2d &World, ofxSpriteSheetRenderer *render,ttChar &Target, float x, float y,int num){
    bird.setPhysics(.3f, 0.0f, 0.5f);
    world = &World;
    bird.setup(world->getWorld(),x,y,10);
    birdNum = num;
    target = &Target;
    spriteRenderer = render;
    basicSprite_ttBirds * newSprite = new basicSprite_ttBirds();
    newSprite->pos.set(0,0);
    newSprite->animation = _bird_fly;
    sprites.push_back(newSprite);
    
    frc.set(50, 0);
    flip = false;
    getPos = bird.getPosition();
    condition = BIRD_FLY;
    killZone.setFromCenter(bird.getPosition(), 100+30, 50+66);
}


//------------------------------------------------------
void ttBirds::update(){
    
    frc.x = bird.getVelocity().x * -3;
    
    switch (condition) {
        case BIRD_FLY:{
            fly();
            bird.body->ApplyForce(bird.body->GetMass() * -world->getWorld()->GetGravity(), bird.body->GetWorldCenter());
            spriteRenderer->clear();
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[0]->animation.loops = -1;
            sprites[0]->animation.frame_duration  = 130;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(bird.getVelocity().x), 1, 3);
            spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
            killZone.setFromCenter(bird.getPosition(), 100+30, 50+66);
        }
            break;
            
        case BIRD_ATTACK:{
            bird.setVelocity(0, 0);
            spriteRenderer->clear();
            spriteRenderer->update(ofGetElapsedTimeMillis());
            if (sprites[0]->animation.loops == -1) {
                sprites[0]->animation.loops = 2;
            }
            
            if(sprites[0]->animation.loops == 0){
                condition = BIRD_FLY;
            }
            spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
            killZone.setFromCenter(bird.getPosition(), 0, 0);
            
        }
            break;
            
        case BIRD_DEAD:{
            
        }break;
    }
    
    getPos = bird.getPosition();
}
//------------------------------------------------------
void ttBirds::draw(){
    ofSetColor(220, 30, 255);
    bird.draw();
    ofRect(killZone);
    
    ofPushMatrix();
    if(birdNum==0){
        ofTranslate(bird.getPosition().x, bird.getPosition().y-15);
        ofScale(1, -1);
    }else{
        ofTranslate(bird.getPosition().x, bird.getPosition().y+15);
        ofScale(1, 1);
    }
    flip? ofScale(-1, 1):ofScale(1, 1);
    spriteRenderer->draw();
    ofPopMatrix();
    
    
    
}
//------------------------------------------------------
void ttBirds::fly(){

    
//    if (bird.getPosition().x>500) {
//        frc.x =-50;
//        bird.setPosition(500, bird.getPosition().y);
//        flip = true;
//    }
//    
//    if (bird.getPosition().x<200) {
//        frc.x =50;
//        bird.setPosition(200, bird.getPosition().y);
//        flip = false;
//    }
    
//    if (fabs(bird.getVelocity().x) <3) {
//        bird.addForce(frc, 1);
//    }
    
//    if (killZone.inside(target->character.getPosition().x, target->character.getPosition().y)) {
//        target->condition = C_DEAD;
//        condition = BIRD_ATTACK;
//    }
    
}