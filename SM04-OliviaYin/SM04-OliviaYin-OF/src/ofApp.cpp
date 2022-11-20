// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    //some notes from Olivia, because I combined another class assignment
    //so there are some narrative
    //the mechanic is using hand to pat the cat in another world to trigger next dialogue
    ofSetWindowShape(640, 480);
    
    // Start the depth sensor.
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    contourFinder.setUseTargetColor(true);
    
    // Setup the parameters.
    nearThreshold.set("Near Threshold", 0.0f, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.009f, 0.0f, 0.1f);
    contourThreshold.set("Contour Threshold", 120, 0, 1000);
    thresImgShow.set("Show Threshold Image", false);
    
    // Setup the gui.
    guiPanel.setup("Depth Threshold", "settings.json");
    guiPanel.add(nearThreshold);
    guiPanel.add(farThreshold);
    guiPanel.add(contourThreshold);
    guiPanel.add(thresImgShow);
    
    //OSC
    sendAddr = "localhost";
    sendPort = 9900;
    sender.setup(sendAddr, sendPort);
}

void ofApp::update()
{
    kinect.update();
    if(kinect.isFrameNew()){
        // Update parameters.
        contourFinder.setTargetColor(255);
        contourFinder.setThreshold(contourThreshold);
        // Find contours.
    }
}

void ofApp::draw()
{

    float distAtMouse = kinect.getDistanceAt(ofGetMouseX(), ofGetMouseY());
    
    // Threshold the depth.
    ofFloatPixels rawDepthPix = kinect.getRawDepthPixels();
    ofFloatPixels thresholdNear, thresholdFar, thresholdResult;
    ofxCv::threshold(rawDepthPix, thresholdNear, nearThreshold);
    ofxCv::threshold(rawDepthPix, thresholdFar, farThreshold, true);
    ofxCv::bitwise_and(thresholdNear, thresholdFar, thresholdResult);
    
    // Upload pixels to image.
    thresholdImg.setFromPixels(thresholdResult);
    contourFinder.getPolylines();
    
    contourFinder.findContours(thresholdImg);
    


    kinect.draw(0,0);

    if(thresImgShow){
        // Draw the result image.
        thresholdImg.draw(0, 0);
        contourFinder.draw();
    }else{
        // Draw the source image.
        contourFinder.draw();
    }

    ofSetColor(255);

    ofColor c(255, 255, 255);
    
    int n = contourFinder.size();
    for(int i = 0; i < n; i++) {

        ofVec2f center = ofxCv::toOf(contourFinder.getCenter(i));
        ofRectangle rects = ofxCv::toOf(contourFinder.getBoundingRect(i));
        ofPushStyle();
        ofSetColor(ofxCv::cyanPrint);
        ofDrawCircle(center, 1);
        ofPopStyle();
        
        // smallest rectangle that fits the contour
        //ofDrawRectangle(rects.x,rects.y,rects.width,rects.height);
        
        float heit = rects.height;
        float width = rects.width;
        
        if (n == 1){
            ofxOscMessage msg;
            msg.setAddress("/rect");
            msg.addFloatArg(center[0]);
            msg.addFloatArg(center[1]);
            msg.addFloatArg(width);
            msg.addFloatArg(heit);

            sender.sendMessage(msg);
        }
    }
      
    ofDrawBitmapStringHighlight(ofToString(distAtMouse, 3), ofGetMouseX(), ofGetMouseY());
    
    // Draw the gui.
    guiPanel.draw();
}

//test osc function
void ofApp::mouseDragged(int x, int y, int button)
{
//  ofxOscMessage msg;
//  msg.setAddress("/cursor/move");
//  msg.addIntArg(ofGetMouseX());
//  msg.addIntArg(ofGetMouseY());
//
//  sender.sendMessage(msg);
}

void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        thresImgShow = !thresImgShow;
    }
}
