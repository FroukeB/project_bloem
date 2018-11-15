#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//   //Kinect:
//    // kinect initialiseren
//    kinect.init();
//    // kinect (connectie) openen
//    kinect.open();
//    // als de kinect geconecteerd is log dan: kinect connected
//    if(kinect.isConnected()) {
//        ofLog() << "kinect connected";
//    }

    //openNIDevice:
    // openNIDevice (object van die ofxOpenNi) setup doen
    openNIDevice.setup();
    // diepte beeld genereren
    openNIDevice.addDepthGenerator();
    // images genereren
    openNIDevice.addImageGenerator();
    // user('s) aanmaken die camera ziet
    openNIDevice.addUserGenerator();
    // openNIDevice starten
    openNIDevice.start();
    
    openNIDevice.setRegister(true);
    
    ofLog();
    
    
    void ofLog();
    
    // frame rate op 60 frames per seconde zetten
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
//    //kinect:
//    // update de kinect
//    kinect.setCameraTiltAngle(10);
//    kinect.update();

    //openNIDevice:
    // update de openNIDevice
    openNIDevice.update();
    
    if (openNIDevice.getNumTrackedUsers() > 0) {
        ofxOpenNIUser user = openNIDevice.getTrackedUser(0);
        ofxOpenNIJoint joint = user.getJoint(JOINT_HEAD);
        
        headPos.x = joint.getProjectivePosition().x;
        headPos.y = joint.getProjectivePosition().y;
        
    }
    
   // openNIDevice.setTiltAngle(10);
}

//-----------------------------------x---------------------------
void ofApp::draw(){
    // kinect:
    // rgb beeld tekenen
    //kinect.draw(0.0, 0.0);
    

ofPushStyle();
    // openNIDevice:
    // diepte beeld tekenen (links)
    openNIDevice.drawDepth(0, 0);
    // image beeld tekenen (rechts)
    openNIDevice.drawImage(640, 0);
    // skeleton:
    // skeleton op diepte beeld tekenen (links)
    openNIDevice.drawSkeletons(0, 0);
    // skeleton op image beeld tekenen (rechts)
    openNIDevice.drawSkeletons(640, 0);
    ofSetColor(255, 0, 0);
    ofDrawCircle(headPos.x,headPos.y, 40);
    ofPopStyle();
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
