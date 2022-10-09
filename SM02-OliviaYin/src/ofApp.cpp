#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    grabber.setup(640, 480);
    myplayer.load("corn.mp4");
    
    displacement.set("Displacement", 0.5,0.5,1.5);
    briThreshold.set("Bri Threshold", 127,0,255);
    captureBackground.set("Capture BG",true);
    debugMode.set("Debug", false);
    camera.set("Video", false);
    onlyBackground.set("Background Move", false);
    
    
    guiPanel.setup("3D Filter");
    
    guiPanel.add(displacement);
    guiPanel.add(briThreshold);
    guiPanel.add(camera);
    guiPanel.add(onlyBackground);
    guiPanel.add(captureBackground);
    //guiPanel.add(debugMode);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0);

    if(!camera && onlyBackground){
        grabber.update();
        if(grabber.isFrameNew()){
            grabberColorMat = ofxCv::toCv(grabber.getPixels());
            ofxCv::copyGray(grabberColorMat, grabberGrayMat);
            
            
            if(captureBackground){
                backgroundMat = grabberGrayMat.clone();
                ofxCv::toOf(backgroundMat, backgroundImg);
                captureBackground = false;
            }
        
            ofxCv::absdiff(backgroundMat,grabberGrayMat, resultMat);
            ofxCv::threshold(resultMat, briThreshold);
            
            // Convert the result CV image back to OF space.
            ofxCv::toOf(resultMat, resultImg);
            resultImg.update();
        }
    }
    //if camera capture and all with displacement
    if(!camera && !onlyBackground){
        grabber.update();
        if(grabber.isFrameNew()){
            grabberColorMat = ofxCv::toCv(grabber.getPixels());
            ofxCv::copyGray(grabberColorMat, grabberGrayMat);
            backgroundMat = grabberGrayMat.clone();
            ofxCv::toOf(backgroundMat, backgroundImg);
            resultMat = grabberGrayMat.clone();
//            ofxCv::toOf(resultMat, resultImg);
//            resultImg.update();
        }
        
    }
    if (camera){
        myplayer.update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(!camera){
        myplayer.stop();
        
        ofPushMatrix();
        //ofTranslate(ofGetWidth()/4, ofGetHeight()/4,0);
        resultImg.draw(0, 0,640, 480);
        
        ofPixels& backgroundPix = backgroundImg.getPixels();
        
        for (int y = 0; y < backgroundPix.getHeight(); y++)
        {
            for (int x = 0; x < backgroundPix.getWidth(); x++)
            {
                ofColor backCol = backgroundPix.getColor(x,y);
                ofPushMatrix();
                ofSetColor(backCol);
                ofFill();
                
                int pixBrightness = backCol.getBrightness();
                ofTranslate(0, 0, displacement * pixBrightness);
                ofDrawCircle(x, y, 0.4);
                ofPopMatrix();
            }
        }
        if (debugMode)
        {
            ofSetColor(255);
            backgroundImg.draw(0, 0);
        }
        ofPopMatrix();
        
    }else{
        myplayer.play();
        //myplayer.draw(0,0);
        ofPixels& colorpix = myplayer.getPixels();
        
        for (int y = 0; y < colorpix.getHeight(); y++)
        {
            for (int x = 0; x < colorpix.getWidth(); x++)
            {
                ofColor backCol = colorpix.getColor(x,y);
                ofPushMatrix();
                ofSetColor(backCol);
                ofFill();
                
                int pixBrightness = backCol.getBrightness();
                ofTranslate(0, 0, displacement * pixBrightness);
                ofDrawCircle(x, y, 0.4);
                ofPopMatrix();
            }
        }
        
    }
    
    
    guiPanel.draw();
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
