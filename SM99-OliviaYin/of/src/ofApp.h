#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void keyPressed(int key);
        
    
        ofVideoGrabber grabber;

        ofxCv::ContourFinder contourFinder;

        ofParameter<ofColor> colorTarget;
        ofParameter<int> colorOffset;
        ofParameter<int> briThreshold;
    
        ofParameter<float> minArea;
        ofParameter<float> maxArea;
    
        ofParameter<int> blurAmount;
    
        ofxPanel guiPanel;
    
        bool thresImgShow;
        ofImage grabberGrayImg;

    ofRectangle rawCursor;
    ofRectangle smoothCursor;
    ofParameter<float> smoothAmount;

        //osc
        std::string sendAddr;
        int sendPort;
        ofxOscSender sender;
};
