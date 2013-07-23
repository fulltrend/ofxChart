/* Copyright (C) 2013 Sergey Yershov*/


#ifndef __ofxChart__ofxChartContainer__
#define __ofxChart__ofxChartContainer__

#include "ofMain.h"
#include "ofxChartVec3d.h"
#include "ofxChartRect3d.h"

typedef struct  {
    ofxChartVec3d min; ofxChartVec3d  max; int size;
}ofxChartDataRange;


enum ofxChartTextPosition
{
    OFX_CHART_TEXT_POS_LEFT = 1,
    OFX_CHART_TEXT_POS_RIGHT = 2,
    OFX_CHART_TEXT_POS_TOP = 3,
    OFX_CHART_TEXT_POS_BOTTOM = 4,
};

enum ofxChartTextDirection
{
    OFX_CHART_TEXT_DIR_HORIZONTAL = 1,
    OFX_CHART_TEXT_DIR_DOWN = 2,
    OFX_CHART_TEXT_DIR_UP = 3,
    OFX_CHART_TEXT_DIR_TILT_RIGHT = 4,
    OFX_CHART_TEXT_DIR_TILT_LEFT = 5,
};

#ifndef SERIESACCESSOR
#define SERIESACCESSOR(propName, propType) propType get##propName() const { return _##propName; }  \
void set##propName(const propType &newVal) { _##propName = newVal;  this->invalidate();}
#endif



struct ofxChartContainer
{
public:
    ofxChartContainer()
    {
		isInvalid = false;_Visible=true;
        depth=100;mPosition = ofPoint(0,0);
        //areaSpace = ofVec3f(100,100,100) ;
        _DataScale = ofVec3f().one(); _DataOffset = ofVec3f().zero();
        _ModelMatrix = ofMatrix4x4(); dataPointSize=ofxChartVec3d(10,10,10);
    }
    //MATRIX TRANSFORMATIONS
    void setPosition(float x, float y, float z=0)
    {
        ofPoint p = ofPoint(x,y,z);
        setPosition( p);
    }
    void setPosition(ofPoint &p)
    {
        mPosition = ofPoint(p);
        _ModelMatrix.setTranslation(mPosition);
        invalidate();
    }
    ofPoint getModelPosition(){return mPosition;}
    
    void rotateY(float degrees)
    {
        _ModelMatrix.preMultRotate(ofQuaternion(degrees, ofVec3f(1,0,0)));
        invalidate();
    }
    void rotateX(float degrees)
    {
		_ModelMatrix.preMultRotate(ofQuaternion(degrees, ofVec3f(0,1,0)));
        invalidate();
    }
    
    void setModelRotation(float degreesX, float degreesY, float degreesZ = 0)
    {
		mRotation = ofQuaternion(degreesX, ofVec3f(1,0,0), degreesY, ofVec3f(0,1,0), degreesZ, ofVec3f(0,0,1));
		_ModelMatrix.setRotate(mRotation);
        invalidate();
    }
    
    
    SERIESACCESSOR(Visible, bool)
    SERIESACCESSOR(ModelMatrix, ofMatrix4x4 )
    SERIESACCESSOR(DataScale, ofVec3f)
    SERIESACCESSOR(DataOffset, ofVec3f)
  
    ofMatrix4x4* getModelMatrixRef()
	{
		return &_ModelMatrix;
	}
    bool isInvalid;
    ofxChartDataRange dataRange;
    
    
    int width, height, depth;
    
    
    void invalidate(){isInvalid = true;}
    //rectangle representing container for data elements. TODO: consider data margin offsets
     ofxChartRect3d getDataRectangle()
    {
        return ofxChartRect3d(ofVec3f(0,0,0), getDimensions());
    }
    
    
    ofVec3f getDimensions()
    {
        return ofVec3f(width, height, depth);
    }
    
    ofxChartVec3d getRangeVector()
    {
        return  ofxChartVec3d(dataRange.max.x - dataRange.min.x, dataRange.max.y - dataRange.min.y, dataRange.max.z - dataRange.min.z);
    }
    
    ofxChartVec3d getDataPointSize(){
        return ofxChartVec3d(dataPointSize);
    }
    
    
    static ofxChartVec3d getMin(ofxChartVec3d a, ofxChartVec3d b)
    {
        return ofxChartVec3d(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
    }
    static ofxChartVec3d getMax(ofxChartVec3d a, ofxChartVec3d b)
    {
        return ofxChartVec3d(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
    }
protected:
    ofxChartVec3d dataPointSize;
    ofPoint mPosition;
	ofQuaternion mRotation;
    ofVec3f _DataScale,_DataOffset;
    bool _Visible;
    ofMatrix4x4 _ModelMatrix;

};




////////            AXIS SET CONTAINER          ///////////



struct ofxChartContainerAxisSet: public ofxChartContainer
{
public:
    
    ofxChartContainerAxisSet()
    {
        xIndex = false, yIndex = false, zIndex = false;
    }
    ofxChartVec3d getAspect()
    {
        ofxChartVec3d d = getDimensions();
        ofxChartVec3d r = getRangeVector();
        ofxChartVec3d s = _DataScale;
        
        return (d/r)*s;
    }
    
    ofVec3f getContainerPoint(ofxChartVec3d p, int index){
        return getContainerPoint(p, index, false);
    }
    //RETURN A VECTOR POINT BASED ON  THE CONTAINER SPACE
    ofVec3f getContainerPoint(ofxChartVec3d p, int index, bool absolute);
    
    //value of a data point given  a container point space
    ofxChartVec3d getContainerValue(ofVec3f containerPoint);
    
    //RECALCULATES VECTOR SIZE OF A DATA POINT
    void calculateDataPointSize(ofxChartVec3d shortestValueVector);
    
    //SCALE ALL THREE DIMENSIONS TO A 1:1:1 SCALE, MINUS MARGINAL OFFSET
    void autoScalePosition(ofVec3f containerMargin);
    
    void setPositionIndexed(bool x, bool y, bool z)
    {
        xIndex = x; yIndex=y;zIndex=z;
        invalidate();
    }
    
private:
    bool xIndex, yIndex, zIndex;
    
};

#endif /* defined(__ofxChart__ofxChartContainer__) */
