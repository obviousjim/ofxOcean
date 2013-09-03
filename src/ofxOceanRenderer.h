//
//  ofxOceanRenderer.h
//  NMMVisualizer
//
//  Created by Jim on 4/11/11.
//  Copyright 2011 FlightPhase. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxOcean.h"

class ofxOceanTile;
class ofxOceanRenderer
{
  public:
    ofxOceanRenderer();
    ~ofxOceanRenderer();
    
    //ocean must already be initialized. # of tiles set level of detail
    void setup(ofxOcean* ocean, int tilesWide, int tilesTall); 
    void update();
	
    void draw(); //uses shader
    void drawWireframe();
    void drawVertices();
	
    void clearTiles();
    void setBumpTexture(string filename);
//	void setBumpTexture(ofBaseHasTexture* bumpTexture);
	
	void setReflectionTexture(string filename);
	void setReflectionTexture(ofBaseHasTexture* reflectionTexture);

	//extent of the whole ocean
	float getWidth();
	float getHeight();
	
    bool hasShader;
	string shaderLocation; //swappable ocean shader
	
    ofVec3f lightDirection;
    ofVec3f lightPosition;
    float lightIntensity;
	
    float bumpScale;
	float bumpSquish;
	float bumpBias;
	
	float brightness;
	float contrast;
	
	ofVec2f bumpMoveSpeed;
	ofVec2f bumpWobbleDamp;
	ofVec2f bumpWobbleRange;
	float reflectDistortion;
	float reflectScale;
    float reflectSquish;
	ofVec2f reflectOffset;
	
    int vertexCount;
	int frameCount;
  protected:
    
    ofxOcean* ocean;
    bool allocated;

    int max_LOD;
	vector< vector<ofxOceanTile*> > tiles_LOD;
    
    int tiles_x;
    int tiles_y;    
    
    ofImage* bumpTexture;
	ofBaseHasTexture* reflectionTexture;
    ofShader oceanShader;
};
