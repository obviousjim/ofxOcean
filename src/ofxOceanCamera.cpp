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
	dampening = 0;
	heading = 0;
}

void ofxOceanCamera::update(){
	if(ocean == NULL){
		return;
	}

	float currentYRot = heading;
	//currentYRot = 0;
//	ofQuaternion currentOrientation = getOrientationQuat();
	ofVec3f middle = getPosition();
	ofVec3f front = middle + ofVec3f(0, 0, baseWidth).getRotated(currentYRot, ofVec3f(0,1,0));
	ofVec3f back = middle + ofVec3f(0, 0, -baseWidth).getRotated(currentYRot, ofVec3f(0,1,0));
	ofVec3f left = middle + ofVec3f(-baseWidth, 0, 0).getRotated(currentYRot, ofVec3f(0,1,0));
	ofVec3f right = middle + ofVec3f(baseWidth, 0, 0).getRotated(currentYRot, ofVec3f(0,1,0));
	
	middleBuoyant = ocean->floatingPosition(middle,false);
	frontBuoyant  = ocean->floatingPosition(front,false);
	backBuoyant   = ocean->floatingPosition(back,false);
	leftBuoyant   = ocean->floatingPosition(left,false);
	rightBuoyant  = ocean->floatingPosition(right,false);

	ofVec3f rollDirection = rightBuoyant - leftBuoyant;
	ofVec3f dipDirection =  frontBuoyant - backBuoyant;
	upDirection = (rollDirection).getCrossed(dipDirection).normalized();
	
	//find the opposing angles
	float lrAngle = ofVec3f(1,0,0).getRotated(currentYRot, ofVec3f(0,1,0)).angle(rollDirection);
	if(leftBuoyant.y > rightBuoyant.y) lrAngle *= -1;
	ofQuaternion sideRotation;
	sideRotation.makeRotate(lrAngle, 0, 0, 1);

	float fbAngle = ofVec3f(0,0,1).getRotated(currentYRot, ofVec3f(0,1,0)).angle(dipDirection);
	if(backBuoyant.y < frontBuoyant.y) fbAngle *= -1;
	ofQuaternion frontRotation;
	frontRotation.makeRotate(fbAngle, 1, 0, 0);
	
	ofVec3f newPosition = middleBuoyant + ofVec3f(0,lift,0);
	setPosition(getPosition() + (newPosition - getPosition()) * (1.0-dampening) );

	setOrientation(frontRotation * sideRotation);
	rotate(currentYRot, ofVec3f(0,1,0));

}

void ofxOceanCamera::drawDebug(){
	
	ofSphere(frontBuoyant, 2);
	ofSphere(backBuoyant, 2);
	ofSphere(leftBuoyant, 2);
	ofSphere(rightBuoyant,2);
	
	ofNode::draw();
}

