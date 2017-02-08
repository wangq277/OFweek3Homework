#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(128);
    
    mCamWidth = 320;
    mCamHeight = 240;
    
    mVideoGrabber.setDeviceID(0);
    mVideoGrabber.setDesiredFrameRate(60);
    mVideoGrabber.initGrabber(mCamWidth, mCamHeight);

    mColorImg.allocate(mCamWidth, mCamHeight);
    
    mGrayImage.allocate(mCamWidth, mCamHeight);
    mGrayBg.allocate(mCamWidth, mCamHeight);
    mGrayDiff.allocate(mCamWidth, mCamHeight);
    
    mThreshold = 80;
    mLearnBackground = true;
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    mVideoGrabber.update();
    
    if (mVideoGrabber.isFrameNew()){
        mColorImg.setFromPixels(mVideoGrabber.getPixels());
        
        mGrayImage = mColorImg;
        
        if (mLearnBackground == true){
            mGrayBg = mColorImg;
            mLearnBackground = false;
        }
        
        mGrayDiff.absDiff(mGrayBg, mGrayImage);
        mGrayDiff.threshold(mThreshold);
        }
    
    mContourFinder.findContours(mGrayDiff, 20, (340*240)/3, 10, true);
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    mVideoGrabber.draw(20,20);
    
    mGrayImage.draw(360,20);
    mGrayBg.draw(20, 280);
    mGrayDiff.draw(360, 280);
    
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(360, 540, 320, 240);
    ofSetColor(255);
    
    mContourFinder.draw(360, 540);
    
    mVideoGrabber.draw(20, 540);
    
    for ( int i= 0; i < mContourFinder.nBlobs; i++){
        mContourFinder.blobs[i].draw(20, 540);
        
        ofSetColor(255);
        if(mContourFinder.blobs[i].hole){
            ofDrawBitmapString("hole", mContourFinder.blobs[i].boundingRect.getCenter().x +20, mContourFinder.blobs[i].boundingRect.getCenter().y+540);
        
        }
    
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case ' '   :
            mLearnBackground = true;
            break;

            case 's':
            ofImage snapshot;
            snapshot.allocate(ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_COLOR);
            snapshot.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
            snapshot.save("snapshot.png");
            break;
    
    }
    
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
