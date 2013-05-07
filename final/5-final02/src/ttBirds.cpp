//
//  ttBirds.cpp
//  final02
//
//  Created by PengCheng on 5/6/13.
//
//

#include "ttBirds.h"

void ttBirds::setup(ofxBox2d &World, ofxSpriteSheetRenderer *render,ttChar &Target, float x, float y,int num){
    
    world = &World;
    bird.setPhysics(1.0f, 0.5f, 0.5f);
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
    killZone.setFromCenter(bird.getPosition(), 50, 50);
    radius = 100;
}


//------------------------------------------------------
void ttBirds::update(){
    
   
    
    switch (condition) {
        case BIRD_FLY:{
            
            
            bird.body->ApplyForce(bird.body->GetMass() * -world->getWorld()->GetGravity(), bird.body->GetWorldCenter());
            fly();

            spriteRenderer->clear();
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[0]->animation.loops = -1;
            sprites[0]->animation.frame_duration  = 75;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(bird.getVelocity().x), 1, 3);
            spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
            killZone.setFromCenter(bird.getPosition(),50, 50);
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
    
    ofSetColor(220, 30, 100,100);
    ofCircle(bird.getPosition(), radius);
    ofSetColor(220, 30, 255);
    bird.draw();
    
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
    cout<<bird.getPosition()<<endl;
}
//------------------------------------------------------
void ttBirds::fly(){
    if (bird.getPosition().x>2000) {
        frc.x =-50;
        bird.setPosition(2000, bird.getPosition().y);
        flip = true;
    }
    
    if (bird.getPosition().x<-200) {
        frc.x =50;
        bird.setPosition(-200, bird.getPosition().y);
        flip = false;
    }
    
    if (fabs(bird.getVelocity().x) <3) {
        bird.addForce(frc, 3);
    }
    
}
