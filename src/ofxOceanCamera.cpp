//
//  ofxOceanCamera.cpp
//  VSOcean
//
//  Created by James George on 7/27/13.
//
//

#include "ofxOceanCamera.h"
#include "ofxOcean.h"

ofxOceanCamera::ofxOceanCamera(){
	ocean = NULL;
	baseWidth = 5;
	lift = 10;
}

void ofxOceanCamera::update(){
	if(ocean == NULL){
		return;
	}
	
	ofVec3f middle = getPosition();
	ofVec3f front = middle + ofVec3f(0, 0, baseWidth);
	ofVec3f back = middle + ofVec3f(0, 0, -baseWidth);
	ofVec3f left = middle + ofVec3f(-baseWidth, 0, 0);
	ofVec3f right = middle + ofVec3f(baseWidth, 0, 0);
	
	middleBuoyant = ocean->floatingPosition(middle,false);
	frontBuoyant = ocean->floatingPosition(front,false);
	backBuoyant  = ocean->floatingPosition(back,false);
	leftBuoyant  = ocean->floatingPosition(left,false);
	rightBuoyant = ocean->floatingPosition(right,false);

	upDirection = (frontBuoyant - backBuoyant).getCrossed(rightBuoyant - leftBuoyant).normalized();
	
	float lrAngle = ofVec3f(1,0,0).angle(rightBuoyant - leftBuoyant);
	if(leftBuoyant.y > rightBuoyant.y) lrAngle *= -1;
	ofQuaternion sideRotation;
	sideRotation.makeRotate(lrAngle, 0, 0, 1);

	float fbAngle = ofVec3f(0,0,1).angle(backBuoyant - frontBuoyant);
	if(backBuoyant.y > frontBuoyant.y) fbAngle *= -1;
	ofQuaternion frontRotation;
	
	frontRotation.makeRotate(fbAngle, 1, 0, 0);
//	cout << fbAngle << " fb and " << lrAngle << " lr " << endl;
	
	setPosition( middleBuoyant + ofVec3f(0,lift,0) );
//	lookAt(frontBuoyant, upDirection );
	ofQuaternion flip;
	flip.makeRotate(180, 0, 0, 1);
	setOrientation( flip * frontRotation * sideRotation);

}

void ofxOceanCamera::drawDebug(){
	
	ofSphere(frontBuoyant, 2);
	ofSphere(backBuoyant, 2);
	ofSphere(leftBuoyant, 2);
	ofSphere(rightBuoyant,2);
	//ofSphere(middleBuoyant, 2);
	
	ofNode::draw();
}

