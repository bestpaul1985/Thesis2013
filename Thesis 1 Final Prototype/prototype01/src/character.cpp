//
//  character.cpp
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#include "character.h"

void character::setup(ofxBox2d world, float x, float y, float width, float height){
   
    offSetX = width/2;
    offSetY = height/2;
    density = 10;
    bounce = 0;
    friction = 0.5;
    box2d.setPhysics(density, bounce, friction);
    box2d.setup(world.getWorld(), x, y, width,height);
}

void character::update(bool L, bool R,float speed, float scale, float dump){
   
    ofPoint frc(0, 0);
    
    if (L) {
        frc.x = -speed;
    }
    
    if (R) {
        frc.x = speed;
    }
    
    box2d.addForce(frc, scale);
    box2d.setDamping(dump);
}

void character::draw(){
    ofSetColor(255, 255, 255);    
    img->draw(box2d.getPosition().x - offSetX, box2d.getPosition().y - offSetY, box2d.getWidth(),box2d.getHeight());
}

