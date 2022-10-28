#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    
    ofxKinect kinect;
    
    ofImage thresholdImg;
    ofImage redImg;
    ofImage blueImg;
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::ContourFinder contourFinder2;
    
    ofParameter<float> nearThreshold;
    ofParameter<float> farThreshold;
    ofParameter<int> offset;
    ofParameter<ofColor>color1;
    ofParameter<ofColor>color2;
    
    ofxPanel guiPanel;
    bool showImg;
    
    
    
};
