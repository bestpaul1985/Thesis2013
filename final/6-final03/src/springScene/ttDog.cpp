//
//  ttDog.cpp
//  final02
//
//  Created by PengCheng on 4/30/13.
//
//

#include "ttDog.h"

void ttDog::setup(ofxBox2d *world, ofxSpriteSheetRenderer *render, float x, float y,int num){
    dog.setPhysics(1.0f, 0.0f, 0.5f);
    dog.setup(world->getWorld(),x,y,30);
    dogNum = num;
    
    spriteRenderer = render;
    basicSprite_dog * newSprite = new basicSprite_dog();
    newSprite->pos.set(0,0);
    newSprite->animation = RUN;
    sprites.push_back(newSprite);
    
    frc.set(50, 0);
    flip = false;
    getPos = dog.getPosition();
    condition = D_RUN;
    killZone.setFromCenter(dog.getPosition(), 100+30, 50+66);
}


//------------------------------------------------------
void ttDog::update(){
    
    switch (condition) {
        case D_RUN:{
            run();
            spriteRenderer->clear();
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[0]->animation.loops = -1;
            sprites[0]->animation.frame_duration  = 130;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(dog.getVelocity().x), 1, 3);
            spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
            killZone.setFromCenter(dog.getPosition(), 100+30, 50+66);
        }
            break;
            
        case D_BITE:{
            dog.setVelocity(0, 0);
            spriteRenderer->clear();
            spriteRenderer->update(ofGetElapsedTimeMillis());
            if (sprites[0]->animation.loops == -1) {
                sprites[0]->animation.loops = 2;
               
            }
            
            if(sprites[0]->animation.loops == 0){
                condition = D_RUN;
            }
            spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
            killZone.setFromCenter(dog.getPosition(), 0, 0);
            
        }
        break;
            
    }
    
   getPos = dog.getPosition();
}
//------------------------------------------------------
void ttDog::draw(){
//    dog.draw();
//    ofRect(killZone);
    ofPushMatrix();
    if(dogNum==0){
        ofTranslate(dog.getPosition().x, dog.getPosition().y-15);
        ofScale(1, -1);
    }else{
        ofTranslate(dog.getPosition().x, dog.getPosition().y+15);
        ofScale(1, 1);
    }
    flip? ofScale(-1, 1):ofScale(1, 1);
    spriteRenderer->draw();
    ofPopMatrix();
   
}
//------------------------------------------------------
void ttDog::run(){
    
    if (dog.getPosition().x>500) {
        frc.x =-50;
        dog.setPosition(500, dog.getPosition().y);
        flip = true;
    }
    
    if (dog.getPosition().x<200) {
        frc.x =50;
        dog.setPosition(200, dog.getPosition().y);
        flip = false;
    }

    if (fabs(dog.getVelocity().x) <3) {
        dog.addForce(frc, 10);
    }
   
}