#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(640, 480);

    // Setup the grabber.
    grabber.setup(640, 480);

    // Setup the contour finder and parameters.
    contourFinder.setUseTargetColor(true);

    colorTarget.set("Color Target", ofColor(255));
    minArea.set("Min Area", 0.001f, 0, 0.1f);
    maxArea.set("Max Area", 0.05f, 0, 0.1f);
    blurAmount.set("Blur Amount", 18, 0, 30);
    //briThreshold.set("Bri Thresh", 0, 0, 255);
    smoothAmount.set("Smooth Amount", 0.5f, 0.0f, 1.0f);

    // Setup the gui.
    guiPanel.setup("Color Tracker", "settings.json");
    guiPanel.add(colorTarget);
    guiPanel.add(minArea);
    guiPanel.add(maxArea);
    guiPanel.add(blurAmount);
    //guiPanel.add(briThreshold);
    guiPanel.add(smoothAmount);

    
    //OSC
    sendAddr = "localhost";
    sendPort = 6969;
    sender.setup(sendAddr, sendPort);
}



//--------------------------------------------------------------
void ofApp::update(){

    grabber.update();
    
    if (grabber.isFrameNew())
    {
        ofImage grabberColorImg;
        
        grabberColorImg.setFromPixels(grabber.getPixels());
        
        // Filter the image.
        if (blurAmount > 0)
        {
          //ofxCv::blur(processImg, blurAmount);
          //ofxCv::GaussianBlur(processImg, blurAmount);
          ofxCv::medianBlur(grabberColorImg, blurAmount);
          grabberColorImg.update();
        }
        
        grabberColorImg.mirror(false, true);
        // Convert input image to grayscale.
        ofxCv::copyGray(grabberColorImg, grabberGrayImg);
        
        grabberColorImg.update();
        grabberGrayImg.update();
        
        // Update parameters.
          //contourFinder.setThreshold(briThreshold);
        contourFinder.setMinAreaNorm(minArea);
        contourFinder.setMaxAreaNorm(maxArea);
        contourFinder.setTargetColor(colorTarget);
        contourFinder.setThreshold(0); //don't delete this you stupid!
      // Find contours.
      contourFinder.findContours(grabberGrayImg);
    }
    
    int n = contourFinder.size();
    for(int i = 0; i < n; i++) {

        ofVec2f center = ofxCv::toOf(contourFinder.getCenter(i));
        ofRectangle rects = ofxCv::toOf(contourFinder.getBoundingRect(i));
        ofPushStyle();
        ofSetColor(ofxCv::cyanPrint);
        ofDrawCircle(center, 1);
        ofPopStyle();
        
        if (n == 1)
        {
            rawCursor.x = center.x;
            rawCursor.y = center.y;
            rawCursor.width = rects.width;
            rawCursor.height = rects.height;
        }
        
        //float heit = rects.height;
        //float width = rects.width;

        
//        if (n == 1){
//            ofxOscMessage msg;
//            msg.setAddress("/rect");
//            msg.addFloatArg(center[0]);
//            msg.addFloatArg(center[1]);
//            msg.addFloatArg(width);
//            msg.addFloatArg(heit);
//
//            sender.sendMessage(msg);
//        }
    }
    
    smoothCursor.x = ofLerp(smoothCursor.x, rawCursor.x, smoothAmount);
    smoothCursor.y = ofLerp(smoothCursor.y, rawCursor.y, smoothAmount);
    smoothCursor.width = ofLerp(smoothCursor.width, rawCursor.width, smoothAmount);
    smoothCursor.height = ofLerp(smoothCursor.height, rawCursor.height, smoothAmount);
    
    ofxOscMessage msg;
    msg.setAddress("/rect");
    msg.addFloatArg(smoothCursor.x);
    msg.addFloatArg(smoothCursor.y);
    msg.addFloatArg(smoothCursor.width);
    msg.addFloatArg(smoothCursor.height);

    sender.sendMessage(msg);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

    if(!thresImgShow){
        // Draw the result image.
        grabber.draw(ofGetWidth(), 0, -ofGetWidth(), ofGetHeight());
    }else{
        // Draw the source image.
        grabberGrayImg.draw(0, 0,ofGetWidth(), ofGetHeight());
    }

    
    
    ofSetColor(255, 0, 0);

    contourFinder.draw();


    // Draw the gui.
    guiPanel.draw();
}



void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        thresImgShow = !thresImgShow;
    }
}
