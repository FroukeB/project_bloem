#pragma once

#include "ofMain.h"
// kinect includen
#include "ofxKinect.h" // terug te vinden map addons > ofxKinect > src > ofxKinect.h (naar deze file verwijzen = automatisch nemen
// ofxOpenNi includen
#include "ofxOpenNI.h" // nodig voor skeleton tracking

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // kinect object/element aanmaken
    ofxKinect kinect;
    
    // ofxOpenNi object/element aanmaken
    ofxOpenNI openNIDevice;
    // ofxOpenNI user object/element aanmaken
    ofxOpenNI user;
    
    ofPoint headPos;
    
};
