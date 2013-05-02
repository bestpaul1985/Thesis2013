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
    character.body->SetFixedRotation(true);
    b2PolygonShape shape;
    
    b2Vec2 v2;
    charNum==0? v2.Set(b2dNum(0), b2dNum(-30)):v2.Set(b2dNum(0), b2dNum(30));
    shape.SetAsBox(b2dNum(10), b2dNum(10), v2 , b2dNum(0));
	b2FixtureDef fixture;
    fixture.isSensor = true;
    fixture.shape = &shape;
    b2Fixture* footSensorFixture = character.body->CreateFixture(&fixture);
    footSensorFixture->SetUserData(new ttSetData());
    ttSetData * sd = (ttSetData*)footSensorFixture->GetUserData();
    sd->name	= "footSenser";
    
    
 
    if (charNum == 0) {
        spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
        spriteRenderer2 = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
        spriteRenderer->loadTexture("sprites/grilSpritesAll.png", 2040, GL_NEAREST);
        spriteRenderer2->loadTexture("sprites/girl_push.png", 2040, GL_NEAREST);
       
        Sprite * newSprite = new Sprite();
        newSprite->pos.set(0,0);
        newSprite->animation = GIRL_RUN;
        sprites[0]=newSprite;
        
        Sprite * newSprite2 = new Sprite();
        newSprite2->pos.set(0,340);
        newSprite2->animation = GIRL_PUSH_ROPE;
        sprites[1]=newSprite2;
        
        Sprite * newSprite3 = new Sprite();
        newSprite3->pos.set(0,0);
        newSprite3->animation = GIRL_HOOK_ROPE;
        sprites[2]=newSprite3;
    }
    
    if (charNum == 1) {
        spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
        spriteRenderer2 = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
        spriteRenderer->loadTexture("sprites/boySpritesAll.png", 2040, GL_NEAREST);
        spriteRenderer2->loadTexture("sprites/boy_push.png", 2040, GL_NEAREST);
        
        Sprite * newSprite = new Sprite();
        newSprite->pos.set(0,0);
        newSprite->animation = BOY_RUN;
        sprites[0]=newSprite;
        
        Sprite * newSprite2 = new Sprite();
        newSprite2->pos.set(0,-170);
        newSprite2->animation = BOY_PUSH_ROPE;
        sprites[1] =newSprite2;
        
        Sprite * newSprite3 = new Sprite();
        newSprite3->pos.set(0,0);
        newSprite3->animation = BOY_HOOK_ROPE;
        sprites[2]=newSprite3;
    }
    
    moveLeft = false;
    condition = C_STOP;
    getPos = SetPos;
    angle = 0;
}

//----------------------------------------------
void ttChar::update(){
    
    ofPoint frc(0,0);
    spriteRenderer->clear();
    spriteRenderer2->clear();
    // change conditions
    switch (condition) {
        case C_STOP:{
            sprites[1]->animation.loops = 1;
            frc.x = character.getVelocity().x * -20;
//            sprites[1]->animation.loops = 1;
            if (character.getVelocity().length()<0.5) {
                spriteRenderer->update(ofGetElapsedTimeMillis());
                sprites[0]->animation.frame = 0;
                sprites[0]->animation.total_frames = 1;
                spriteRenderer->addCenteredTile(&sprites[0]->animation, 0,0);
            }else{
                spriteRenderer->update(ofGetElapsedTimeMillis());
                sprites[0]->animation.total_frames = 19;
                sprites[0]->animation.frame_duration = 75;
                sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
                spriteRenderer->addCenteredTile(&sprites[0]->animation, 0,0);
            }
        }break;
                
        case C_LEFT:{
            moveLeft = true;
            if ( character.getVelocity().x > -5 ) frc.x = -50;
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[0]->animation.total_frames = 19;
            sprites[0]->animation.frame_duration = 75;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
            spriteRenderer->addCenteredTile(&sprites[0]->animation, 0,0);
        }break;

        case C_RIGHT:{
            moveLeft = false;
            if ( character.getVelocity().x < 5 ) frc.x = 50;
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[0]->animation.total_frames = 19;
            sprites[0]->animation.frame_duration = 75;
            sprites[0]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 5);
            spriteRenderer->addCenteredTile(&sprites[0]->animation, 0,0);
        }break;
       
        case C_PUSH_ROPE:{
            frc.x = character.getVelocity().x * -30;
            if ( character.getVelocity().length()<0.1){
                spriteRenderer2->update(ofGetElapsedTimeMillis());
                sprites[1]->animation.index = 0;
                sprites[1]->animation.total_frames = 8;
                sprites[1]->animation.frame_duration = 35;
                spriteRenderer2->addCenteredTile(&sprites[1]->animation,sprites[1]->pos.x,sprites[1]->pos.y);
            }

        }break;
            
        case C_HOOK_ROPE:{
            
            spriteRenderer->update(ofGetElapsedTimeMillis());
            sprites[2]->animation.frame_duration = 120;
            sprites[2]->animation.frame_duration /= ofClamp(fabs(character.getVelocity().x), 1, 3);
            sprites[2]->pos.set(-12, 0);
            spriteRenderer->addCenteredTile(&sprites[2]->animation, sprites[2]->pos.x,sprites[2]->pos.y);
            
        }break;
            
        case C_SWING_ROPE:{
            
            sprites[1]->animation.frame = 8;
            sprites[1]->animation.total_frames = 1;
            spriteRenderer2->addCenteredTile(&sprites[1]->animation,sprites[1]->pos.x,sprites[1]->pos.y);

        }break;
            
        case C_DEAD:{
            dead();
        }break;
    }
    
    //add force on char
    character.addForce(frc, 10);
    
    //update postion
    if (condition !=C_HOOK_ROPE) {
        getPos = character.getPosition();
    }
    
}
//----------------------------------------------
void ttChar::draw(){
    ofSetColor(255, 100);
//    character.draw();
    
    ofPushMatrix();
    ofTranslate(character.getPosition().x, character.getPosition().y);
    ofRotateZ(-angle*RAD_TO_DEG);
    if (charNum == 0) {
        moveLeft? ofScale(1, 1):ofScale(-1, 1);
    }
    
    if (charNum == 1) {
        moveLeft? ofScale(-1, 1):ofScale(1, 1);
    }
    
    spriteRenderer->draw();
    spriteRenderer2->draw();
    ofPopMatrix();
    
   
}
//-----------------------------------------------
void ttChar::dead(){
    
    
    if (charNum == 0) {
    
        if (character.getPosition().x<2593) {
            character.setPosition(0, 0);
        }else if(character.getPosition().x>2593 && character.getPosition().x<4384){
            character.setPosition(2691, 41);
        }else if(character.getPosition().x>4384){
            character.setPosition(4693, -185);
        }else{
            character.setPosition(0, 0);
        }
        
    }
    
    if (charNum == 1) {
    
        if (character.getPosition().x<2718) {
            character.setPosition(0, 0);
        }else if(character.getPosition().x>2718&&character.getPosition().x<4533){
            character.setPosition(2809, 75);
        }else if(character.getPosition().x>4533){
            character.setPosition(4860, 196);
        }else{
            character.setPosition(0, 0);
        }
        
    }
    
    condition = C_STOP;
}
