/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartDataSeries.h"

#include "of3dPrimitives.h"
#include "ofxChartSeriesPie.h"

ofxChartSeriesBase::~ofxChartSeriesBase()
{}

void ofxChartSeriesBase::rotateMatP2(ofVec3f p1, ofVec3f target)
{
    ofVec3f center(0, 0, 0);
    //ofVec3f tar(target.x- p1.x, target.y - p1.y, target.z - p1.z);
    
    
    glTranslatef(p1.x, p1.y, p1.z);
    
    
    ofVec3f normal = target - p1;
    normal.normalize();
    
    ofVec3f forward(0, 1, 0);
    ofVec3f axis	= forward.crossed(normal);
    axis.normalize();
    float angle		= forward.angle(normal);
    glTranslatef(0, 0, 0);
    glRotatef( angle, axis.x, axis.y, axis.z );
    
}


////////            SINGLE        /////////////



template<typename ChartDataPoint>
BaseSeriesPointer ofxChartSeriesSingleAxis<ChartDataPoint>::clone() {
    //clone
    BaseSeriesPointer bsp = BaseSeriesPointer(new ofxChartSeriesSingleAxis<ChartDataPoint>());
    
    ofPtr<ofxChartSeriesSingleAxis<ChartDataPoint> > p_orig =   dynamic_pointer_cast<ofxChartSeriesSingleAxis<ChartDataPoint> >(bsp);
    
    for(int i=0; i<ofxChartSeriesSingleAxis<ChartDataPoint>::_pointsGen.size(); i++)
        p_orig->addDataPoint(*new ChartDataPoint(_pointsGen[i].x
                                                 ,_pointsGen[i].color));
    
    p_orig->_BaseColor = _BaseColor;
    return bsp;
    
}
template<typename ChartDataPoint>
void ofxChartSeriesSingleAxis<ChartDataPoint>::copyTo(ofPtr<ofxChartSeriesSingleAxis<ChartDataPoint> > &mom) {
    for(int i=0; i<_pointsGen.size(); i++)
        mom->addDataPoint(*new ChartDataPoint(_pointsGen[i].x
                                              ,_pointsGen[i].color));
    
    mom->_BaseColor = this->_BaseColor;
    
    
}





////////            XY        /////////////








template<typename ChartDataPoint>
BaseSeriesPointer ofxChartSeriesXY<ChartDataPoint>::clone() {
    //clone
    BaseSeriesPointer bsp = BaseSeriesPointer(new ofxChartSeriesXY<ChartDataPoint>());
    
    ofPtr<ofxChartSeriesXY<ChartDataPoint> > p_orig =   dynamic_pointer_cast<ofxChartSeriesXY<ChartDataPoint> >(bsp);
    for(int i=0; i<ofxChartSeriesXY<ChartDataPoint>::_pointsGen.size(); i++)
        p_orig->addDataPoint(*new ChartDataPoint(ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].x
                                                 , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].y
                                                 ,ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].color));
    
    p_orig->_BaseColor = this->_BaseColor;
    return bsp;
    
}
template<typename ChartDataPoint>
void ofxChartSeriesXY<ChartDataPoint>::copyTo(ofPtr<ofxChartSeriesXY<ChartDataPoint> > &mom) {
    for(int i=0; i<ofxChartSeriesXY<ChartDataPoint>::_pointsGen.size(); i++)
        mom->addDataPoint(*new ChartDataPoint(ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].x
                                              , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].y
                                              ,ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].color));

    mom->_BaseColor = this->_BaseColor;

}









////////            XYZ        /////////////



template<typename ChartDataPoint>
BaseSeriesPointer ofxChartSeriesXYZ<ChartDataPoint>::clone() {
    //clone
    BaseSeriesPointer bsp = BaseSeriesPointer(new ofxChartSeriesXYZ<ChartDataPoint>());
    
    ofPtr<ofxChartSeriesXYZ<ChartDataPoint> > p_orig =   dynamic_pointer_cast<ofxChartSeriesXYZ<ChartDataPoint> >(bsp);
    for(int i=0; i<ofxChartSeriesXY<ChartDataPoint>::_pointsGen.size(); i++)
        p_orig->addDataPoint(*new ChartDataPoint(ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].x
                                                 , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].y
                                                 , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].z,
                                                 ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].color));
    
    p_orig->_BaseColor = ofxChartSeriesXY<ChartDataPoint>::_BaseColor;
  
    return bsp;
    
}
template<typename ChartDataPoint>
void ofxChartSeriesXYZ<ChartDataPoint>::copyTo(ofPtr<ofxChartSeriesXYZ<ChartDataPoint> > &mom) {
    
    for(int i=0; i<ofxChartSeriesXY<ChartDataPoint>::_pointsGen.size(); i++)
        mom->addDataPoint(*new ChartDataPoint(ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].x
                                              , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].y
                                              , ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].z,
                                              ofxChartSeriesXY<ChartDataPoint>::_pointsGen[i].color));
    
    mom->_BaseColor = ofxChartSeriesXY<ChartDataPoint>::_BaseColor;
 
}








