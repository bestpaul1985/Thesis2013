//
//  ttDog.cpp
//  final02
//
//  Created by PengCheng on 4/30/13.
//
//

#include "ttDog.h"

void ttDog::setup(ofxBox2d &world, float x, float y){
    dog.setPhysics(1.0f, 0.0f, 0.5f);
    dog.setup(world.getWorld(),x,y,30);
    
    
    spriteRenderer = new ofxSpriteSheetRenderer(1, 1000, 0, 120);
    spriteRenderer->loadTexture("sprites/dogSprites.png", 2040, GL_NEAREST);
    
    basicSprite_dog * newSprite = new basicSprite_dog();
    newSprite->pos.set(0,0);
    newSprite->speed=0;
    newSprite->animation = RUN;
    sprites.push_back(newSprite);
    frc.set(50, 0);
    flip = false;
}


//------------------------------------------------------
void ttDog::update(){
    run();
    spriteRenderer->clear();
    spriteRenderer->update(ofGetElapsedTimeMillis());
    sprites[0]->animation.frame_duration  = 130;
    sprites[0]->animation.frame_duration /= ofClamp(fabs(dog.getVelocity().x), 1, 3);
    cout<<sprites[0]->animation.frame_duration<<endl;
    spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
}
//------------------------------------------------------
void ttDog::draw(){
    dog.draw();
    ofPushMatrix();
    ofTranslate(dog.getPosition().x, dog.getPosition().y+15);
    flip? ofScale(-1, 1):ofScale(1, 1);
    spriteRenderer->draw();
    ofPopMatrix();
    
}
void ttDog::run(){
    
    if (dog.getPosition().x>300) {
        frc.x =-50;
        dog.setPosition(300, dog.getPosition().y);
        flip = true;
    }
    
    if (dog.getPosition().x<0) {
        frc.x =50;
        dog.setPosition(0, dog.getPosition().y);
        flip = false;
    }

    if (fabs(dog.getVelocity().x) <3) {
        dog.addForce(frc, 10);
    }
   
}