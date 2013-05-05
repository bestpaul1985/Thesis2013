#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
    scenes[0] = new openingScene();
    scenes[1] = new springScene();
	scenes[2] = new springScene();
    
    //emoji image
    image[0].loadImage("sprites/emoji_love.png");
    image[1].loadImage("sprites/emoji_laughing.png");
    image[2].loadImage("sprites/emoji_happy.png");
    image[3].loadImage("sprites/emoji_supprise.png");
    image[4].loadImage("sprites/emoji_angry.png");

    //char_render
    char_render[0] = new ofxSpriteSheetRenderer(1, 10000, 0, 85);
    char_render[1] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_render[2] = new ofxSpriteSheetRenderer(1, 10000, 0, 39);
    char_render[3] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_render[4] = new ofxSpriteSheetRenderer(1, 10000, 0, 84);
    char_render[0]->loadTexture("sprites/all_girl.png", 2040, GL_NEAREST);
    char_render[1]->loadTexture("sprites/push_girl.png", 1000, GL_NEAREST);
    char_render[2]->loadTexture("sprites/run_boy.png", 1000, GL_NEAREST);
    char_render[3]->loadTexture("sprites/push_boy.png", 1000, GL_NEAREST);
    char_render[4]->loadTexture("sprites/pull_boy.png", 1000, GL_NEAREST);
	
    
    //dog render
    dog_render = new ofxSpriteSheetRenderer(1, 1000, 0, 120);
    dog_render ->loadTexture("sprites/all_dog.png", 2040, GL_NEAREST);
    
    //rabit render
    rabit_render = new ofxSpriteSheetRenderer(1, 1000, 0, 30);
    rabit_render ->loadTexture("sprites/rabit.png", 2040, GL_NEAREST);
    
    //sky
    skyBg.loadImage("sprites/bg/sky/background.png");
    cloud01.loadImage("sprites/bg/sky/cloud01.png");
    cloud02.loadImage("sprites/bg/sky/cloud02.png");
    cloud03.loadImage("sprites/bg/sky/cloud03.png");
    
    //box2d
    // setup world A
    world_A.init();
    world_A.setFPS(60);
    world_A.setGravity(0,-10);
    // setup world B
    world_B.init();
    world_B.setFPS(60);
    world_B.setGravity(0, 10);
    
    //levelLoder
    levelLoader();
    //setup
    scenes[0]->setup();
    scenes[1]->setup();
    scenes[2]->setup();
    currentScene = 0;
}
//--------------------------------------------------------------
void testApp::update(){
    
	scenes[currentScene]->update();
}
//--------------------------------------------------------------
void testApp::draw(){
	scenes[currentScene]->draw();
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    currentScene++;
    currentScene %= 3;

//	((circleScene*)scenes[1])->sayHello();
    scenes[currentScene]->touchDown(touch);
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    scenes[currentScene]->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    scenes[currentScene]->touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    scenes[currentScene]->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    scenes[currentScene]->touchCancelled(touch);
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    scenes[currentScene]->lostFocus();
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    scenes[currentScene]->gotFocus();
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    scenes[currentScene]->gotMemoryWarning();
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    scenes[currentScene]->deviceOrientationChanged(newOrientation);
}
//--------------------------------------------------------------
void testApp::levelLoader(){

    scenes[1]->dog_Render = dog_render;
    scenes[1]->rabit_Render = rabit_render;
    scenes[1]->char_Render[0] = char_render[0];
	scenes[1]->char_Render[1] = char_render[1];
    scenes[1]->char_Render[2] = char_render[2];
    scenes[1]->char_Render[3] = char_render[3];
    scenes[1]->char_Render[4] = char_render[4];
    scenes[1]->skyBg = &skyBg;
    scenes[1]->cloud01 = &cloud01;
    scenes[1]->cloud02 = &cloud02;
    scenes[1]->cloud03 = &cloud03;
    for (int i = 0; i<5; i++) {
        scenes[1]->image[i] = &image[i];
    }
    scenes[1]->world_A = &world_A;
    scenes[1]->world_B = &world_B;
    
    scenes[2]->dog_Render = dog_render;
    scenes[2]->rabit_Render = rabit_render;
    scenes[2]->char_Render[0] = char_render[0];
	scenes[2]->char_Render[1] = char_render[1];
    scenes[2]->char_Render[2] = char_render[2];
    scenes[2]->char_Render[3] = char_render[3];
    scenes[2]->char_Render[4] = char_render[4];
    scenes[2]->skyBg = &skyBg;
    scenes[2]->cloud01 = &cloud01;
    scenes[2]->cloud02 = &cloud02;
    scenes[2]->cloud03 = &cloud03;
    for (int i = 0; i<5; i++) {
        scenes[1]->image[i] = &image[i];
    }
    scenes[2]->world_A = &world_A;
    scenes[2]->world_B = &world_B;
}






