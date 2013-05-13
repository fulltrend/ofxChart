/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartSeriesOCHL.h"

void ofxChartSeriesOCHL::addDataPoint(float open, float close, float high, float low, Poco::DateTime date)
{
    ofxChartDataPointOCHL dp = ofxChartDataPointOCHL(open, close, high, low, date);
    ofxChartVec3d fvl = dp.getDoubleValueLow(), fvh = dp.getDoubleValueHigh();
    if(this->_pointsGen.size() == 0)
        _range.min = fvl, _range.max = fvh, _range.min.z=0, _range.max.z=1;
    else
    {
        _range.min.x = min(fvl.x, _range.min.x);
        _range.min.y = min(fvl.y, _range.min.y);
        
        _range.max.x = max(fvh.x, _range.max.x);
        _range.max.y = max(fvh.y, _range.max.y);
        
    }
    
    this->_pointsGen.push_back(dp);
    this->_range.size = this->_pointsGen.size();
}


void ofxChartSeriesOCHL::draw(){
    //draw lines for high-low
    //draw filled boxes for open/close. if close < open - draw red(or preferred color) , else - white
    //based on the actual dimensional point width, the box width should be set to 0.8 by default
    const int dps = this->getDataPoints().size();
    
    ofxChartVec3d cs = axisContainer->getDataPointSize();
    float pointWidth = cs.x * this->_PointContainerSize;
    //float pointWidth = MIN(cs.x, 10); TODO: Use in BAR charts)
    ofPushStyle();
    for(int i=0; i<dps; i++)
    {
        ofVec3f cpl = axisContainer->getContainerPoint(this->getPointRef(i)->getDoubleValueLow(),i);
        ofVec3f cph = axisContainer->getContainerPoint(this->getPointRef(i)->getDoubleValueHigh(),i);
        ofVec3f cpo = axisContainer->getContainerPoint(this->getPointRef(i)->getDoubleValueOpen(),i);
        ofVec3f cpc = axisContainer->getContainerPoint(this->getPointRef(i)->getDoubleValueClose(),i);
        bool bear = this->getDataPoints()[i].c < this->getPointRef(i)->o;
       
        if(_DisplayStyle == OFX_CHART_OCHL_BAR)
            ofSetColor(bear? ofColor(255,0,0) : ofColor(0,255,0));
        else
            ofSetColor(0, 0, 0);
        ofLine(cpl,cph);
        
        
        ofSetColor(bear? ofColor(255,0,0) : ofColor(0,255,0));
        if(_DisplayStyle == OFX_CHART_OCHL_CANDLESTICK)
            ofRect(cpo.x-(pointWidth/2), MIN(cpo.y,cpc.y), pointWidth, MAX(cpo.y, cpc.y)-MIN(cpo.y,cpc.y));
        else if(_DisplayStyle == OFX_CHART_OCHL_BAR)
        {
        //draw lines
             ofLine(ofPoint(cpo.x-(pointWidth/2), cpo.y), cpo);
            ofLine(ofPoint(cpc.x+(pointWidth/2), cpc.y), cpc);
        }
        
        
    }
    
    ofPopStyle();
}
