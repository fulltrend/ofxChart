/* Copyright (C) 2013 Sergey Yershov*/


#pragma once

#include "ofMain.h"
#include "ofxChartDataPoint.h"
#include "ofxChartDataSeries.h"

#define DEGREES_TO_RADIANS(degrees) degrees * PI / 180

///////////    PIE SLICE ///////////////
class ofxChartSeriesPieSlice
{
public:
    void setupSlice(int pixelOffset, int radius, float _percentage, float height, ofColor colof);
    void draw();
    ofMesh mFace, mEdge, mBottom;
    float percent;

    
    ofVec3f normalize(ofVec3f vector){
        float magnitude =  getMagnitude(vector);
        ofVec3f normalizedVector;
        normalizedVector.x = vector.x / magnitude;
        normalizedVector.y = vector.y / magnitude;
        normalizedVector.z = vector.z / magnitude;
        return normalizedVector;
    }
    
    float getMagnitude(ofVec3f vector){
        return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    
};




///////////    PIE CHART ///////////////

template<class ValueType>
class ofxChartSeriesPie_ :  public ofxChartSeriesSingleAxis<ofxChartDataPointXY_<ValueType, int> >
{
public:
    
    ~ ofxChartSeriesPie_(){}
    ofxChartSeriesPie_(){
    
        _Radius = 30; _PixelHeight = 10;
         _AxialTilt =0;
  
    }

    SERIESACCESSOR(AxialTilt, float)
    SERIESACCESSOR(Radius, int)
    SERIESACCESSOR(PixelHeight, int)
    
    
    
    
    void addSlice(ValueType val, string title){
        addSlice(val, title, 0, ofColor(ofRandom(0, 255),ofRandom(0, 255),ofRandom(0, 255) ));
        update();
    }
    
    void addSlice(ValueType val, string title, int pixelOffset){
        addSlice(val, title, pixelOffset
                 ,ofColor(ofRandom(0, 255),ofRandom(0, 255),ofRandom(0, 255) ));
        update();
    }
    
    
    void addSlice(ValueType val, string title,  int pixelOffset, ofColor color)
    {
    ofxChartDataPointXY_<ValueType, int> sp = ofxChartDataPointXY_<ValueType, int>(val, pixelOffset);
    sp.color = color;
    sp.title = title;
    this->addDataPoint(sp);
    update();
}

    void   draw();
     void update();
    BaseSeriesPointer clone();
    

    
private:
    
    float _AxialTilt;
    int _Radius, _PixelHeight;
    
    
    //rotate to specified angle, if needed
    //drawing each slice. If needs offset or any other visual adjustment do it her
    
//    void drawSlice( float _percentage, float height);
    
    // convert radius to local space. INLINE??
    float localRadius(){
        return _Radius;
        //return ofxChartSeriesBase::areaContainer->convertToLocalSpace(radius);
    }
    
      vector<ofxChartSeriesPieSlice> slices;
    
};


template<class ValueType>
void ofxChartSeriesPie_<ValueType>::draw()
{

    
    ofPushMatrix();
    ofRotate(_AxialTilt, 1, 0, 0 );
    
    //calculate starting degree based on percentage and rotate accordingly
    this->lightsOn();
    float rotateDegree=0;
    //vector<ofxChartDataPointXY_<ValueType, DepthType> >dataPoints = this->getDataPoints();
    int numSlices = slices.size();
    for(int i=0; i< numSlices; i++)
    {
        if(this->getEnableLights())
        {
            this->materialColor.set(this->getPointRef(i)->color);
        }
        
        
        //drawing transformations
        ofPushMatrix();
        //set up title here, so we don't tilt the text
        
        
        ofRotate(rotateDegree);
        
        //calculate starting offset point
        float pixelOffset = this->getDataPoints()[i].y;
        float xbase = pixelOffset * cosf(ofDegToRad((slices[i].percent *360)/2));
        float ybase = pixelOffset * sinf(ofDegToRad((slices[i].percent *360)/2));
        ofTranslate(xbase, ybase);
   
        
        slices[i].draw();
        ofPopMatrix();
        rotateDegree += slices[i].percent *360;
        
        
        
        
        //setup text position at the beginning of each arc
        const float fontSize = 8.0f;
        int fontLength = (int)this->getDataPoints()[i].title.length();
        
        float x = localRadius() * cosf(ofDegToRad(rotateDegree));
        float y = (rotateDegree == 360 ? 0 : localRadius() * sinf(ofDegToRad(rotateDegree)));
        x = (rotateDegree<270 && rotateDegree > 90 ? x - (fontLength*fontSize) : x);
        ofPushMatrix();
        ofTranslate(x*1.2, y);
        
    
        ofSetColor(255,255,255);
        ofRotate(-_AxialTilt, 1, 0, 0 );
        
        ofDrawBitmapString(this->getDataPoints()[i].title, 0, 10, 0);
        
        ofPopMatrix();
    }
    this->lightsOff();
    ofPopMatrix();
    
}

template<class ValueType>
void ofxChartSeriesPie_<ValueType>::update()
{
    //clean existing
    slices.clear();
    
    vector< ofxChartDataPointXY_<ValueType, int>   > dataPoints =  this->getDataPoints();
    
    float xTotal = 0;
    for(int i=0; i< dataPoints.size(); i++)
    {
        xTotal += ofxChart::getDoubleValue(dataPoints[i].x);
        //calculate height if Z is <> 0
    }
    
    for(int i=0; i< dataPoints.size(); i++)
    {
        float percent =  dataPoints[i].x/xTotal;
        //TODO: calculate height percentage
        
        
        ofxChartSeriesPieSlice slice;
        slice.setupSlice(10, localRadius(), percent, _PixelHeight, dataPoints[i].color);
        slices.push_back(slice);
    }
    
}



typedef ofxChartSeriesPie_<float> ofxChartSeriesPie;




