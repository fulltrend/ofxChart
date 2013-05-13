/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartSeriesPie.h"
float colorHue = ofRandom(0,200);










void ofxChartSeriesPieSlice::setupSlice(int pixelOffset, int radius, float _percentage,float height, ofColor color)
{
    percent = _percentage;
    int numVertices = _percentage * 360 ;
    //setup topface 
    mFace.addVertex(ofVec3f(0,0,0));
    mFace.addNormal(ofVec3f(0,0,1));
    mFace.addColor(color);
    
    for (int i = 0; i < numVertices; i++) {
        float x = radius * cosf(ofDegToRad(i));
        float y = radius * sinf(ofDegToRad(i));
        mFace.addVertex(ofVec3f(x,y,0));
        mFace.addNormal(ofVec3f(0,0,1));
        mFace.addColor(color);
    }
    mFace.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    mBottom.addVertex(ofVec3f(0,0,height));
    mBottom.addNormal(ofVec3f(0,0,1));
        mBottom.addColor(color);
    for (int i = 0; i < numVertices; i++) {
        float x = radius * cosf(ofDegToRad(i));
        float y = radius * sinf(ofDegToRad(i));
        mBottom.addVertex(ofVec3f(x,y,height));
        mBottom.addNormal(ofVec3f(0,0,1));
        mBottom.addColor(color);
    }
    mBottom.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    
    
    
    vector<ofVec3f>edgeVertices =  vector<ofVec3f>(numVertices*2) ;
    vector<ofVec3f>edgeNormals =  vector<ofVec3f>(numVertices*2) ;

    //calculate edge color
    
    ofColor edgeColor = color/2;
    
    mEdge.addVertex(ofVec3f(0,0,0));
    mEdge.addVertex(ofVec3f(0,0,height));
    mEdge.addNormal(ofVec3f(0,0,1));
    mEdge.addNormal(ofVec3f(0,0,1));
    mEdge.addColor(edgeColor);
    mEdge.addColor(edgeColor);
    //setup edge
    for (int i = 0; i < numVertices; i++) {
        float x = radius * cosf(ofDegToRad(i));
        float y = radius * sinf(ofDegToRad(i));
        edgeVertices[2 * i] = ofVec3f(x, y, 0);
        edgeVertices[2 * i + 1] = ofVec3f(x, y, height);
    }
    
    for (int i = 0; i < (numVertices * 2)-3; i++) {
        ofVec3f v1 = edgeVertices[i];
        ofVec3f v2 = edgeVertices[i + 1];
        ofVec3f v3 = edgeVertices[i + 2];
        
        mEdge.addColor(edgeColor);
        

        
        
        if (i % 2 == 0) {
            ofVec3f u1 =v2- v1; //vector product
            ofVec3f u2 = v3-v1;
            
            ofVec3f normal = normalize(u1.cross(u2)); //normalized cross product
            
            edgeNormals[i] = normal;
            edgeNormals[i + 1] = normal;
        }
    }
    
    //add results to mesh
    
    mEdge.addVertices(edgeVertices);
    mEdge.addNormals(edgeNormals);
    mEdge.setMode(OF_PRIMITIVE_TRIANGLE_STRIP); //?

    
}




void ofxChartSeriesPieSlice::draw()
{
//
//    float halfrotate = (180 - (percent*180));
//    ofRotate(halfrotate);
//    ofTranslate(0,-20);
//    ofRotate(-halfrotate);

    //ofRotate(360 - (percent*360));
    mFace.draw();
    ofEnableSmoothing();
    mEdge.draw();
    ofDisableSmoothing();
    mBottom.draw();
    ofSetColor(255, 0, 0);

//    ofRotate(-(halfrotate*2));
//    ofRotate(halfrotate);
//    ofTranslate(0, 20);
//    ofRotate(-halfrotate);

    
    
}




//
//template<class ValueType>
//BaseSeriesPointer ofxChartSeriesPie_<ValueType>::clone() {
//    //clone
//    BaseSeriesPointer bsp = BaseSeriesPointer(new ofxChartSeriesPie_<ValueType>());
//    
//    
//    ofPtr<ofxChartSeriesXYZ<ofxChartDataPointXYZ_<ValueType, string, DepthType> > > p_xyz =
//    dynamic_pointer_cast<ofxChartSeriesXYZ<ofxChartDataPointFloatString> >(bsp);
//    
//    ofxChartSeriesXYZ<ofxChartDataPointXYZ_<ValueType, string, DepthType> >::copyTo(p_xyz);
//    
//    
//    ofPtr<ofxChartSeriesPie_ > p_orig =   dynamic_pointer_cast<ofxChartSeriesPie_ >(bsp);
//    
//    
//    p_orig ->radius = radius;
//    p_orig ->axialTilt = axialTilt;
//    p_orig ->maxPixelHeight = maxPixelHeight;
//    
//    p_orig->setup();
//    
//    return bsp;
//    
//}

