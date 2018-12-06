#include "ofApp.h"

int index = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	PORT = 12345;
	HOST = "localhost";
	sender.setup(HOST, PORT);

	m.setAddress("/tracking/position");

	// default alpha op 0 transparante lagen afzetten geen mogelijkheid tot gebruik transparant zoekt een matching kleur
	//ofDisableAlphaBlending();
	
	outputPixels.allocate(640, 480, 4);
	outputTexture.allocate(640, 480, GL_RGBA);

	// kinect:
	// initialiseren van kinect sensor
	kinect.initSensor();
	//kinect.initIRStream(640, 480);
	// aanmaken van kleur scherm en grote
	kinect.initColorStream(640, 480, true);
	// aanmaken van diepte scherm en grote
	kinect.initDepthStream(640, 480, true);
	// aanmaken van skelleton is het zittend persoon
	kinect.initSkeletonStream(false);

	// kinect starten
	kinect.start();

	// window 1280 op 480 zetten
	ofSetWindowShape(1280 * 2, 480  * 2 * 2);
	
	// background:
	background.loadImage("img/background.jpg");
	// bloem:
	bloem_head.loadImage("img/bloem_klein.png");
	// bloem vallen:
	bloem_drop.loadImage("img/bloem.png");
	// blad links:
	blad_lhand.loadImage("img/left_blad.png");
	// blad rechts:
	blad_rhand.loadImage("img/right_blad.png");
	x = 100;
	y = 0;
	pos_bloem = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::update(){
	// Kinect:
	// kinect.getNuiSensor.ElevationAngle(90);
	kinect.update();

	// camera motor draaien
	if (ofGetFrameNum() == 30) {
		long currentAngle;
		kinect.getNuiSensor().NuiCameraElevationGetAngle(&currentAngle);
		//ofLog() << currentAngle;
		kinect.getNuiSensor().NuiCameraElevationSetAngle(0);
	}

	// Schermen:
	// om uitgeknipte beeld te kunnen genereren hij vergelijk pixel per pixel of het overeen komt met de diepte camera alles die zwart is op het diepte beeld blijft over de rest knipt hij weg
	if (kinect.isFrameNew()) {
		ofPixels colorPixelsRef = kinect.getColorPixelsRef();
		ofColor alpha = ofColor(0, 0, 0, 0);
		NUI_DEPTH_IMAGE_PIXEL* nuiDepthPixels = kinect.getNuiDepthPixelsRef();
		ofShortPixels rawDepthPixels = kinect.getRawDepthPixelsRef();

		INuiSensor * sensor = & kinect.getNuiSensor();
		NUI_IMAGE_RESOLUTION _sourceDepthResolution = NUI_IMAGE_RESOLUTION_640x480;
		NUI_IMAGE_RESOLUTION _sourceRGBResolution = NUI_IMAGE_RESOLUTION_640x480;
		USHORT packedDepth;
		long depthX, depthY, rgbX, rgbY;
		for (int y = 0; y < 480; y++) {
			for (int x = 0; x < 640; x++) {
				int index = y * 640 + x;
				NUI_DEPTH_IMAGE_PIXEL nuiDepthPixel = nuiDepthPixels[index];

				packedDepth = rawDepthPixels.getPixels()[index] << 4;

				if (nuiDepthPixel.playerIndex > 0) {
					sensor->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(_sourceRGBResolution,
						_sourceDepthResolution,
						NULL,
						x, 
						y, 
						packedDepth,
						&rgbX,
						&rgbY
					);
					if (rgbX < 640 && rgbY < 480 && rgbX >= 0 && rgbY >= 0) {
						outputPixels.setColor(x, y, colorPixelsRef.getColor(rgbX, rgbY));
					} else {
						outputPixels.setColor(x, y, alpha);
					}					
				} else {
					outputPixels.setColor(x, y, alpha);
				}
			}
		}

		outputTexture.loadData(outputPixels, GL_RGBA);
	}

	// kinect als er een newSkeleton is dan:
	if(kinect.isNewSkeleton()) {
		//per skelleton
		for( int i = 0; i < kinect.getSkeletons().size(); i++)
		{
      		// als het skelleton een hoofd heeft dan:
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{
				// zoek naar het hoofd
				SkeletonBone head = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
				// positie berekenen van waar het hoofd zich op het scherm bevind
				ofVec2f headScrenPosition( head.getScreenPosition().x, head.getScreenPosition().y);
				changeKinectTiltAngle(head.getScreenPosition().y);
				
				return;
			}
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT) != kinect.getSkeletons().at(i).end()) {
				SkeletonBone leftHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
				
			}
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT) != kinect.getSkeletons().at(i).end()) {
				SkeletonBone rightHand = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
				
			}
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_LEFT) != kinect.getSkeletons().at(i).end()) {
				SkeletonBone rightFoot = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_LEFT)->second;
				
			}
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_RIGHT) != kinect.getSkeletons().at(i).end()) {
				SkeletonBone rightFoot = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_FOOT_RIGHT)->second;
		
			}
		}
	}

	y += 1;
	pos_bloem = ofVec2f(x, y);
	bloem_drop.draw(pos_bloem);
}

//--------------------------------------------------------------
void ofApp::draw(){	
	ofPushStyle();
	ofPushMatrix();
	// background: IMG
	// plaatsen van background
	background.draw(0,0);
	ofPopMatrix();
	ofPopStyle();

	ofPushStyle();
	ofPushMatrix();
	// schermen tekenen:
	// beelde groter maken
	ofScale(2, 2);
	// teken kinect beeld op scherm
	kinect.draw(640,0);
	// teken dieptebeeld
	// kinect.drawDepth(0, 0);
	// tekenen uitgeknipte beeld
	// outputTexture.draw(0, 480, 640, 480);
	ofPopStyle();
	
	// style aanmaken om later iets te wijzigen
	ofPushStyle();
	// skelleton:
	// kleur op rood zetten
	 //ofSetColor(255, 0, 0);
	// lijdikte instellen
	ofSetLineWidth(3.0f);
	// skeletons opvragen
	auto skeletons = kinect.getSkeletons();
	// voor elk skeleton in de skeletons doe:
	for(auto & skeleton : skeletons) {
		if(skeleton.find(NUI_SKELETON_POSITION_HEAD) != skeleton.end()) {
			SkeletonBone headBone = skeleton.find(NUI_SKELETON_POSITION_HEAD)->second;
			ofPushStyle();
			ofSetColor(255, 0, 0);
			ofCircle(headBone.getScreenPosition(), 30);
			ofPopStyle();	
			//ofLog() << bloem_head.getHeight;
			bloem_head.draw(headBone.getScreenPosition());
			/*float devider = 2;
			ofLog() << bloem_head.getHeight/devider;
			x_bloem_head = bloem_head.getWidth/devider;
			y_bloem_head = bloem_head.getHeight/devider;*/
			
			bloem_head.setAnchorPoint(150, 150);
		}
		if(skeleton.find(NUI_SKELETON_POSITION_HAND_LEFT) != skeleton.end()) {
			SkeletonBone leftHand = skeleton.find(NUI_SKELETON_POSITION_HAND_LEFT)->second;
			ofPushStyle();
			ofSetColor(255, 255, 0);
			ofCircle(leftHand.getScreenPosition(), 20);
			ofPopStyle();
			blad_lhand.draw(leftHand.getScreenPosition());
		}
		if(skeleton.find(NUI_SKELETON_POSITION_HAND_RIGHT) != skeleton.end()) {
			SkeletonBone rightHand = skeleton.find(NUI_SKELETON_POSITION_HAND_RIGHT)->second;
			ofPushStyle();
			ofSetColor(255, 255, 255);
			ofCircle(rightHand.getScreenPosition(), 20);
			ofPopStyle();
			blad_rhand.draw(rightHand.getScreenPosition());
		}
		if(skeleton.find(NUI_SKELETON_POSITION_FOOT_LEFT) != skeleton.end()) {
			SkeletonBone rightFoot = skeleton.find(NUI_SKELETON_POSITION_FOOT_LEFT)->second;
			ofSetColor(255, 255, 0);
			ofCircle(rightFoot.getScreenPosition(), 20);
		}
		if(skeleton.find(NUI_SKELETON_POSITION_FOOT_RIGHT) != skeleton.end()) {
			SkeletonBone rightFoot = skeleton.find(NUI_SKELETON_POSITION_FOOT_RIGHT)->second;
			ofSetColor(255, 255, 255);
			ofCircle(rightFoot.getScreenPosition(), 20);
		}
		// voor elk bot in het skelet doe
		for(auto & bone : skeleton) {
			// switch vraag als indicator de getTrackingState
			switch(bone.second.getTrackingState()) {
			// als de getTrackingState Inferred is dan:
			case SkeletonBone::Inferred:
				// zet de kleur in blauw
				ofSetColor(0, 0, 255);
				break;
			// als de getTrackingState Tracked is dan:
			case SkeletonBone::Tracked:
				// zet de kleur in groen
				ofSetColor(0, 255, 0);
				break;
			// als de getTrackingState NotTracked is dan:
			case SkeletonBone::NotTracked:
				// zet de kleur in rood
				ofSetColor(255, 0, 0);
				break;
			}

			auto index = bone.second.getStartJoint();
			auto connectedTo = skeleton.find((_NUI_SKELETON_POSITION_INDEX) index);
			if (connectedTo != skeleton.end()) {
				ofLine(connectedTo->second.getScreenPosition(), bone.second.getScreenPosition());
			}
			ofCircle(bone.second.getScreenPosition(), 10.0f);
		}
	}

	// stijl wijzigingen terug afzetten/normaal zetten
	ofPopStyle();
	ofPopMatrix();

	ofPushStyle();
	ofPushMatrix();
	// IMG: vallende bloem
	// plaatsen van vallende bloem
	bloem_drop.draw(pos_bloem);
	ofPopMatrix();
	ofPopStyle();

	/* ofPushStyle();
	ofPushMatrix();
	// background: IMG
	// plaatsen van background
	bloem.draw(0,0);
	ofPopMatrix();
	ofPopStyle(); */
}

//--------------------------------------------------------------
void ofApp::trackMovement(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::changeKinectTiltAngle(int y ){
	// ofLog() << "change tilt";
	// ofLog() << y;	
	if(y > 70){
		// camera omhoog draaien = - max 30°
		long currentAngle;
		kinect.getNuiSensor().NuiCameraElevationGetAngle(&currentAngle);
		// ofLog() << "to high";
		// ofLog() << currentAngle;
		currentAngle-=6;
		// ofLog() << currentAngle;
		kinect.getNuiSensor().NuiCameraElevationSetAngle(currentAngle);
	}
	if(y < 30){
		// camera moet omlaag draaien = + max 30°
		long currentAngle;
		kinect.getNuiSensor().NuiCameraElevationGetAngle(&currentAngle);
		// ofLog() << "to low";
		// ofLog() << currentAngle;
		currentAngle+=6;
		// ofLog() << currentAngle;
		kinect.getNuiSensor().NuiCameraElevationSetAngle(currentAngle);
	}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
