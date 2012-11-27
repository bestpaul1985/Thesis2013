#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetWindowShape(650, 1000);
    ofBackground(40);
    
    //FFT
    
    ofSoundStreamSetup(0, 2, this, 44100, BUFFER_SIZE, 4);
    left = new float [BUFFER_SIZE];
    right= new float [BUFFER_SIZE];
    FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
    
    FFTanalyzer.peakHoldTime    = 30;
    FFTanalyzer.peakDecayRate   = 0.095f;
    FFTanalyzer.linearEQIntercept = 0.9f;
    FFTanalyzer.linearEQSlope   = 0.01f;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //fft stuffs
    float avg_power = 0.0f;
    myfft.powerSpectrum(0, (int) BUFFER_SIZE/2, left, BUFFER_SIZE, &magnitude[0], &phase[0], &power[0], &avg_power);
    
    for(int i = 0; i<BUFFER_SIZE/2; i++){
        freq[i] = magnitude[i];
    }
    
    FFTanalyzer.calculate(freq);
    
    
    for (int i = 0;i < FFTanalyzer.nAverages; i++){
        
//            cout << FFTanalyzer.averages[FFTanalyzer.nAverages/6] << endl;
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*3/12] > 3) {
            b1  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*3/12] < 3) {
            b1  =   false;
        }
        
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*4/12] > 3) {
            b2  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*4/12] < 3) {
            b2  =   false;
        }
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*5/12] > 3) {
            b3  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*5/12] < 3) {
            b3  =   false;
        }
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*6/12] > 3) {
            b4  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*6/12] < 3) {
            b4  =   false;
        }
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*7/12] > 3) {
            b5  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*7/12] < 3) {
            b5  =   false;
        }
        //
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*8/12] > 3) {
            b1  =   true;
        }
        
        if (FFTanalyzer.averages[FFTanalyzer.nAverages*8/12] < 3) {
            b1  =   false;
        }
        
        

    }
    
//    for (int i = 0 ; i< FFTanalyzer.nAverages; i++) {
//        ofRect(200+(i*40), 600-FFTanalyzer.peaks[i]*6, 20, -4);
//    }
 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255);
    float speedMod = ofGetElapsedTimef()*1200;
    
    ofPushMatrix();
        ofTranslate(0, speedMod);
        
        int d = 100;

        //deal with left button
        ofSetColor(0, 169,157);
        if (b1 == false) {
            range1.draw(50, 50, speedMod, false);
        }
        else if (b1 == true){
            range1.draw(50, 50, speedMod, true);
        }
        //up
        
        ofSetColor(0, 114, 188);
        if (b2 == false) {
            range2.draw(50 + d, 50,speedMod, false);
        }
        else if (b2 == true){
            range2.draw(50 + d, 50, speedMod, true);
        }
        
        //right
        ofSetColor(247, 148, 29);
        if (b3 == false) {
            range3.draw(50 +d*2, 50,speedMod, false);
        }
        else if (b3 == true){
            range3.draw(50 +d*2, 50, speedMod, true);
        }
        //down
        ofSetColor(168, 100, 168);
        if (b4 == false) {
            range4.draw(50+d*3, 50,speedMod, false);
        }
        else if (b4 == true){
            range4.draw(50+d*3, 50, speedMod, true);
        }
        //Z
        ofSetColor(255, 245, 104);
        if (b5 == false) {
            range5.draw(50+d*4, 50,speedMod, false);
        }
        else if (b5 == true){
            range5.draw(50+d*4, 50, speedMod, true);
        }
        //X
        ofSetColor(242, 108, 79);
        if (b6 == false) {
            range6.draw(50+d*5, 50,speedMod, false);
        }
        else if (b6 == true){
            range6.draw(50+d*5, 50, speedMod, true);
        }
        
    
    ofPopMatrix();
    
    ofSetLineWidth(1);
    ofSetColor(255);
    ofLine(0, ofGetHeight()*6/7, ofGetWidth(), ofGetHeight()*6/7);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
     
   
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    


}
//--------------------------------------------------------------
void testApp::audioIn(float *input, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        left[i]     =input [i*2];
        right[i]    =input [i*2+1];
    }
    
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