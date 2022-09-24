#include "ofApp.h"
ofImage lifeImg; //original image
int gridSize = 20; // size of grid
ofPixels cellPixs; // this generation
ofPixels cellNxtPixs; //next generation
int timer = 200; //how long refresh next frame
bool newTurn; //whether to fresh
int rowNum = 30; //how many rows
int colNum = 40; // how many col
bool paused;
bool allWhite;
bool allBlack;

int mouseX;
int mouseY;
//press P to pause the game
//press R to restart

//--------------------------------------------------------------
void ofApp::setup(){
    initialState();
}

//--------------------------------------------------------------
void ofApp::update(){
    //timer
    if (timer > 0){
        timer --;
        newTurn = false;
    }else{
        newTurn = true;
        timer = 100;
    }
    
    //if timer is up, show next generation
    if(newTurn && !paused && !allBlack && !allWhite){
        for (int y = 0; y < lifeImg.getHeight(); y++)
        {
            for (int x = 0; x < lifeImg.getWidth(); x++)
            {
                ofColor lifeColor = cellPixs.getColor(x,y);
                if(lifeColor == ofColor(255)){
                    //Isolation: if this cell is live, less 2 live will die
                    if(checkLiveCells(x,y,cellPixs) < 2) {
                        lifeColor = ofColor(0);
                    }
                    //Overcrowding: if this cell is live, more than 3 live will die
                    if(checkLiveCells(x,y,cellPixs) > 3) {
                        lifeColor = ofColor(0);
                    }
                }
                //Reproduction: die with 3 live will live
                if(lifeColor == ofColor(0)){
                    if(checkLiveCells(x,y,cellPixs) == 3) {
                        lifeColor = ofColor(255);
                    }
                }
                cellNxtPixs.setColor(x, y, lifeColor);
            }
        }
        //update next to this
        cellPixs = cellNxtPixs;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //lifeImg.draw(0, 0);
    int wid =lifeImg.getWidth();
    int height = lifeImg.getHeight();
    
    for (int y = 0; y < lifeImg.getHeight(); y++)
    {
        for (int x = 0; x < lifeImg.getWidth(); x++)
        {
            ofColor lifeColor = cellPixs.getColor(x, y);
            ofSetColor(lifeColor);
            //draw in rectangle
            ofDrawRectangle(x*gridSize, y * gridSize, gridSize, gridSize);
        }
    }
    if (paused){
        ofSetColor(255);
        ofDrawBitmapString("PAUSE", wid/2, height/2);
    }
    
    if(allWhite){
        for (int y = 0; y < lifeImg.getHeight(); y++)
        {
            for (int x = 0; x < lifeImg.getWidth(); x++)
            {
                ofSetColor(255);
                ofDrawRectangle(x*gridSize, y * gridSize, gridSize, gridSize);
            }
        }
    }
    if(allBlack){
        for (int y = 0; y < lifeImg.getHeight(); y++)
        {
            for (int x = 0; x < lifeImg.getWidth(); x++)
            {
                ofSetColor(0);
                ofDrawRectangle(x*gridSize, y * gridSize, gridSize, gridSize);
            }
        }
    }
}

int ofApp:: checkLiveCells(int col, int row, ofPixels cellPix){
    int liveCount = 0;
    if (col > 0 && row > 0 && col < colNum && row < colNum){
        for (int y = -1; y < 2; y++){
            for(int x = -1; x < 2; x++){
                ofColor cellColor = cellPix.getColor(col+x, row+y);
                if(x != 0 && y != 0 && cellColor == ofColor(255)){
                    liveCount ++;
                }
            }
        }
    }
    
    return liveCount;
}
//press mouse to change color
void ofApp:: changeGridColor(int x, int y){
    x = x/gridSize;
    y = y / gridSize;
    
    ofColor gridColor = cellPixs.getColor(x,y);
    if(gridColor == 255){
        gridColor = 0;
    }else if (gridColor == 0){
        gridColor = 255;
    }
    
    cellPixs.setColor(x, y, gridColor);
    ofDrawRectangle(x*gridSize, y * gridSize, gridSize, gridSize);
}

void ofApp::initialState(){
    //allocate memory for the image without having to load a file from disk
    lifeImg.allocate(colNum, rowNum, OF_IMAGE_GRAYSCALE);
    // Set the window size to match the image.
    //ofSetWindowShape(dogImg.getWidth(), dogImg.getHeight());
    //get pixels
    ofPixels lifePix = lifeImg.getPixels();
    ofColor color;
    //set an initial state based on possibility
    for (int y = 0; y < lifeImg.getHeight(); y++)
    {
        for (int x = 0; x < lifeImg.getWidth(); x++)
        {
            if (ofRandomuf() < 0.5)
            {
                lifePix.setColor(x, y, ofColor(0));
                
            }
            else
            {
                lifePix.setColor(x, y, ofColor(255));
            }
            
        }
    }
    cellPixs = lifePix;
    cellNxtPixs = lifePix;
    lifeImg.setFromPixels(lifePix);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'p'){
        paused =! paused;
    }
    
    if(key == 'r'){
        initialState();
    }
    
    if (key == 'w'){
        allWhite = true;
        allBlack = false;
    }
    if (key == 'b'){
        allBlack = true;
        allWhite = false;
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
    if(button == 0){
        changeGridColor(x,y);
    }
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
