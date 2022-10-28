// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1280, 960);
    
    // Start the depth sensor.
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    contourFinder.setUseTargetColor(true);
    
    // Setup the parameters.
    nearThreshold.set("Near Threshold", 0.01f, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.011f, 0.0f, 0.1f);
    offset.set("Offset",20,0,100);
    color1.set("Color 1", ofColor(255, 0, 0));
    color2.set("Color 2", ofColor(0, 0, 255));
    
    // Setup the gui.
    guiPanel.setup("255 0 255 rays", "settings.json");
    guiPanel.add(nearThreshold);
    guiPanel.add(farThreshold);
    guiPanel.add(offset);
    guiPanel.add(color1);
    guiPanel.add(color2);
}

void ofApp::update()
{
    kinect.update();
    if(kinect.isFrameNew()){
        // Update parameters.
        contourFinder.setTargetColor(255);
        contourFinder.setThreshold(250);
        // Find contours.
        
    }
}

void ofApp::draw()
{
    //kinect.getDepthTexture().draw(0, 0);
    ofBackground(0);
    if (kinect.isFrameNew())
    {
        
        
        // Get the point distance using the SDK function.
        float distAtMouse = kinect.getDistanceAt(ofGetMouseX(), ofGetMouseY());
        //ofDrawBitmapStringHighlight(ofToString(distAtMouse, 3), ofGetMouseX(), ofGetMouseY());
        
        // Threshold the depth.
        ofFloatPixels rawDepthPix = kinect.getRawDepthPixels();
        ofFloatPixels thresholdNear, thresholdFar, thresholdResult;
        ofxCv::threshold(rawDepthPix, thresholdNear, nearThreshold);
        ofxCv::threshold(rawDepthPix, thresholdFar, farThreshold, true);
        ofxCv::bitwise_and(thresholdNear, thresholdFar, thresholdResult);
        
        // Upload pixels to image.
        thresholdImg.setFromPixels(thresholdResult);
        
        contourFinder.findContours(thresholdImg);
        
        
    }
    
    // Draw the gui.
    guiPanel.draw();

    ofTranslate(400, 100);
    
    if(showImg){
        ofSetColor(255,0,0);
        thresholdImg.draw(30, 0);
    }
    
    for (int i = 0; i < 2; i ++){
        for(int j = 0; j < 8; j ++){
            
            if ( i == 0){
                ofTranslate(0, 0, offset * j);
                ofSetColor(color2);
            }else {
                //ofTranslate(0, 0, -1 * offset * j);
                ofSetColor(color1);
            }
            contourFinder.draw();
        }
    }
}

void ofApp::mousePressed(int x, int y, int button){
    showImg = !showImg;
}
