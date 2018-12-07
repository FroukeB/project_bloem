#pragma once

#include "ofxKinectCommonBridge.h"
#include "ofMain.h"
#include "ofxSvg.h"
#include "ofxGui.h"
#include "ofxGif.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void trackMovement(int x, int y);
		void changeKinectTiltAngle(int y);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<ofPolyline> outlines;

		ofShader sh;
		ofImage img;

		ofxKinectCommonBridge kinect;

		ofPixels outputPixels;
		ofTexture outputTexture;

		unsigned char * colorAlphaPixels;	

		ofImage background;
		ofImage bloem_head;
		ofImage bloem_drop;
		ofImage blad_lhand;
		ofImage blad_rhand;

		ofVec2f	pos_bloem;
		float x;
		float y;

		float x_bloem_head;
		float y_bloem_head;

		float PORT;
		string HOST;

		ofxOscSender sender;
		ofxOscMessage m;
};
