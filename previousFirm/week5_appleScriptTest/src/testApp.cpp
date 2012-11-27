#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key =='z' || key =='Z') {
        cout << "key Z pressed" << endl;
        
        
        system("osascript /Users/firmread/Desktop/testL.scpt");
//        system("osascript /Users/firmread/Desktop/testL2.scpt");
        
                //test syntax 6
//        string scriptPath = "osascript " + ofToString(ofToDataPath("testL.scpt"));
//        system(scriptPath);

                //test syntax 5
//        system("osascript " + ofToString(ofToDataPath("testL.scpt")) );
        
                //test syntax 4 <<
                //*** WORKS with full path
//        system("osascript /Users/firmread/Desktop/testL.scpt");
//        system("osascript /Users/firmread/Desktop/testL2.scpt");
        
                //test syntax 3
//        system("osascript -e 'tell application \"TextEdit\" activate end tell'");
//        system("osascript -e 'tell application \"System Events\" to keystroke \"l\" end tell'");
//        system("osascript -e 'tell application \"emptyExampleDebug\" activate end tell'");
        
                //test syntax 2
//        system("osascript -e 'tell application \"TextEdit\" activate tell application \"System Events\" to keystroke \"l\" end tell tell application \"emptyExampleDebug\" activate end tell'");
        
                //test syntax 1
//        system("osascript -e 'tell application \"TextEdit\"'");
//        system("osascript -e 'activate'");
//        system("osascript -e 'tell application \"System Events\" to keystroke \"l\"'");
//        system("osascript -e 'end tell'");
//        system("osascript -e 'tell application \"emptyExampleDebug\"'");
//        system("osascript -e 'activate'");
//        system("osascript -e 'end tell'");
        
//        system ("osascript -e 'tell app 'Finder' to sleep'");
    }
    else if (key =='x' || key =='x') {
        cout << "key X pressed" << endl;
    }
    else if (key != 0) {
        cout << key << endl;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}