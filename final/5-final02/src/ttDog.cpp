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
    dog.setup(world.getWorld(),x,y,43,30);
    dog.body->SetFixedRotation(true);
    
    spriteRenderer = new ofxSpriteSheetRenderer(1, 1000, 0, 85);
    spriteRenderer->loadTexture("sprites/dogSprites2.png", 2040, GL_NEAREST);
    
    basicSprite_dog * newSprite = new basicSprite_dog();
    newSprite->pos.set(0,0);
    newSprite->speed=0;
    newSprite->animation = run;
    sprites.push_back(newSprite);
}


//------------------------------------------------------
void ttDog::update(){
    spriteRenderer->clear();
    spriteRenderer->update(ofGetElapsedTimeMillis());
    spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
}
//------------------------------------------------------
void ttDog::draw(){
    dog.draw();
    ofPushMatrix();
    ofTranslate(dog.getPosition().x, dog.getPosition().y);
    spriteRenderer->draw();
    ofPopMatrix();
    
}