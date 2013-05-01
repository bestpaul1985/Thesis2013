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
    dog.setup(world.getWorld(),x,y,58.5,39);	
    dog.body->SetFixedRotation(true);
    
    renderer = new ofxSpriteSheetRenderer(1, 10000, 0, 330);
    renderer->loadTexture("sprites/dog_new.png", 1980, GL_NEAREST);
    DogSprite * newSprite = new DogSprite();
    newSprite->pos.set(dog.getPosition());
    newSprite->animation = RUN;
    sprites[0] = newSprite;
    
//    cout<< renderer->getSpriteSheetWidth() << endl;
//    cout<< renderer->getTileSize() <<endl;
}


//------------------------------------------------------
void ttDog::update(){
    renderer->clear();
    renderer->update(ofGetElapsedTimeMillis());
    renderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
}
//------------------------------------------------------
void ttDog::draw(){
    dog.draw();
    renderer->draw();
}