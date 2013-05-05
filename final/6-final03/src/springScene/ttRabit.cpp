//
//  ttRabit.cpp
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#include "ttRabit.h"

//-------------------------------------------------
void ttRabit::setup(ofxBox2d *world,ofxSpriteSheetRenderer *render,float x, float y, int num){
    rabit.setPhysics(1.0f, 0.0f, 0.5f);
    rabit.setup(world->getWorld(),x,y,10);
    rabitNum = num;
    
    rabitRender = render;
    basicSprite_rabit * newSprite = new basicSprite_rabit();
    newSprite->pos.set(0,0);
    newSprite->animation = animation_run;
    rabitSprites.push_back(newSprite);
    
    
    rabitRender = render;
    basicSprite_rabit * newSprite1 = new basicSprite_rabit();
    newSprite1->pos.set(0,0);
    newSprite1->animation = animation_stand;
    rabitSprites.push_back(newSprite1);
    
    rabitRender = render;
    basicSprite_rabit * newSprite2 = new basicSprite_rabit();
    newSprite2->pos.set(0,0);
    newSprite2->animation = animation_stop;
    rabitSprites.push_back(newSprite2);
    
    frc.set(50, 0);
    flip = false;
    getPos = rabit.getPosition();
    condition = RB_RUN;
}
//-------------------------------------------------
void ttRabit::update(){
    switch (condition) {
        case RB_RUN:{
            run();
            rabitRender->clear();
            rabitRender->update(ofGetElapsedTimeMillis());
            rabitSprites[0]->animation.frame_duration  = 75;
            rabitSprites[0]->animation.frame_duration /= ofClamp(fabs(rabit.getVelocity().x), 1, 3);
            rabitRender->addCenteredTile(&rabitSprites[0]->animation,0,0);
        }break;

        case RB_STAND:{
            rabitRender->clear();
            rabitRender->update(ofGetElapsedTimeMillis());
            rabitSprites[1]->animation.frame_duration  = 75;
            rabitSprites[1]->animation.frame_duration /= ofClamp(fabs(rabit.getVelocity().x), 1, 3);
            rabitRender->addCenteredTile(&rabitSprites[1]->animation,0,0);
        }break;
            
        case RB_STOP:{
            rabitRender->clear();
            rabitRender->update(ofGetElapsedTimeMillis());
            rabitSprites[2]->animation.frame_duration  = 75;
            rabitSprites[2]->animation.frame_duration /= ofClamp(fabs(rabit.getVelocity().x), 1, 3);
            rabitRender->addCenteredTile(&rabitSprites[2]->animation,0,0);
        }break;
    }

    getPos = rabit.getPosition();
}
//-------------------------------------------------
void ttRabit::draw(){
//    rabit.draw();
    ofPushMatrix();
   
    if(rabitNum==0){
        ofTranslate(rabit.getPosition().x, rabit.getPosition().y+20);
        ofScale(1, -1);
    }else{
        ofTranslate(rabit.getPosition().x, rabit.getPosition().y-20);
        ofScale(1, 1);
    }
    flip? ofScale(-1, 1):ofScale(1, 1);
    rabitRender->draw();
    ofPopMatrix();
}
//-------------------------------------------------
void ttRabit::run(){
    if (rabit.getPosition().x>-50) {
        frc.x =-50;
        rabit.setPosition(-50, rabit.getPosition().y);
        flip = true;
    }
    
    if (rabit.getPosition().x<-300) {
        frc.x =50;
        rabit.setPosition(-300, rabit.getPosition().y);
        flip = false;
    }
    
    if (fabs(rabit.getVelocity().x) <2) {
        rabit.addForce(frc, 0.5);
    }
}









