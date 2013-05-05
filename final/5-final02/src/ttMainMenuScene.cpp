//
//  ttMainMenuScene.cpp
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#include "ttMainMenuScene.h"
//-----------------------------------------------
void ttMainMenuScene::setup(int &CurrentScene){
    currentScene = &CurrentScene;
    bg.loadImage("sprites/mainMenu.png");
}

//-----------------------------------------------
void ttMainMenuScene::update(){
    
}
//-----------------------------------------------
void ttMainMenuScene::draw(){
	bg.draw(0, 0);
}


//-----------------------------------------------
void ttMainMenuScene::touchDown(ofTouchEventArgs & touch){
    *currentScene=1;
}
//-----------------------------------------------
void ttMainMenuScene::touchMoved(ofTouchEventArgs & touch){

}
//-----------------------------------------------
void ttMainMenuScene::touchUp(ofTouchEventArgs & touch){

}