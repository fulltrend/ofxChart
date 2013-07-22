/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartAxis.h"




ofxChartAxisBase::ofxChartAxisBase( ofxChartAxisDirection _d, ofPtr<ofxChartContainerAxisSet> _c){
    direction = _d; container = _c;
    numMajTicks = 5, numMinorTicks = 5;
    majWidthPixels=8.0, minWidthPixels=4.0, maxOffsetPixels=0.0, minOffsetPixels=0.0, axisSize=2;
    crossing = OFX_CHART_AXIS_CROSS_CONTAINER;
    crossingValue = 0;
    axisDataType = OFX_CHART_AXIS_DATATYPE_DECIMAL;
    lineStyle = OFX_CHART_AXIS_LINE_SOLID;
    isLog=false;
    
    showMajLabel=true; showMinor=true; showMajor=true; visible=true;
    axisColor= ofColor(0,0,0); labelColor=ofColor(0,0,0);
    switch(_d)
    {
        case OFX_CHART_AXIS_DIRECTION_X:
            textPosition = OFX_CHART_TEXT_POS_BOTTOM;
            break;
        case OFX_CHART_AXIS_DIRECTION_Y:
            textPosition = OFX_CHART_TEXT_POS_LEFT;
            break;
        case OFX_CHART_AXIS_DIRECTION_Z:
            textPosition = OFX_CHART_TEXT_POS_LEFT;
            break;
    }
    
    //set default formatter
	
    labelFormatter = (ofxChart::baseLabelFormatter*)new ofxChart::simpleLabelFormatter();
    
}



void ofxChartAxisBase::calculateDateIncrementType (Poco::DateTime &_min, Poco::DateTime &_max)
{
    //Get a nice earliest date
    Timespan timeRange = _max - _min;
    
    
    if(timeRange.days()>365)
    {
        dit = OFX_CHART_DATERANGE_YEAR;
    }
    else if(timeRange.days()>31)
    {
        dit = OFX_CHART_DATERANGE_MONTH;
    }
    else if(timeRange.days() > 1)
    {
        dit = OFX_CHART_DATERANGE_DAY;
    }
    else if(timeRange.totalMinutes() > 60)
    {
        dit = OFX_CHART_DATERANGE_HOUR;
    }
    else if(timeRange.totalSeconds() > 60)
    {
        dit = OFX_CHART_DATERANGE_MINUTE;
    }
    else
        dit = OFX_CHART_DATERANGE_SECOND;
    
}

void ofxChartAxisBase::calculateMajorTickIncrement()
{
    
    double min = minValue, max = maxValue;
    if(axisDataType == OFX_CHART_AXIS_DATATYPE_DATE)
    {
        minValue = ceil(minValue);
        maxValue = floor(maxValue);
        DateTime minDate = ofxChart::getDateTime(minValue);
        DateTime maxDate = ofxChart::getDateTime(maxValue);
        calculateDateIncrementType(minDate, maxDate);
        min = 1;
        switch (dit) {
            case OFX_CHART_DATERANGE_YEAR:
                min = minDate.year();
                max = maxDate.year();
                break;
            case OFX_CHART_DATERANGE_MONTH:
                //minDate.month();
                max = maxDate.month() - minDate.month();
                break;
            case OFX_CHART_DATERANGE_DAY:
                //min = minDate.day();
                max = (maxDate - minDate).days();//maxDate.day();
                break;
            case OFX_CHART_DATERANGE_HOUR:
                //min = minDate.hour();
                max = (maxDate - minDate).totalHours();//maxDate.hour();
                break;
            case OFX_CHART_DATERANGE_MINUTE:
                //min = minDate.minute();
                max =(maxDate - minDate).totalMinutes(); //maxDate.minute();
                break;
            case OFX_CHART_DATERANGE_SECOND:
                //min = minDate.second();
                max =(maxDate - minDate).totalSeconds(); //maxDate.second();
                break;
            case OFX_CHART_DATERANGE_MILLISECOND:
                //min = minDate.second();
                max =(maxDate - minDate).totalMilliseconds(); //maxDate.second();
                break;
            default:
                break;
        }
    }
    
    
    // calculate an initial guess at step size
    double tempStep = (max - min)/numMajTicks;
    if(tempStep == 0)
    {
        majTickMin = 0;
        majTickMax = 0;
        majTickIncrement = 1;
        return;
    }
    // get the magnitude of the step size
    double mag = (double)floor(log10(tempStep));
    double magPow = (double)pow(10, mag);
    
    // calculate most significant digit of the new step size
    double magMsd = (int)(tempStep/magPow + 0.5);
    
    // promote the MSD to either 1, 2, or 5
    if (magMsd > 5.0)
        magMsd = 10.0f;
    else if (magMsd > 2.0)
        magMsd = 5.0f;
    else if (magMsd > 1.0)
        magMsd = 2.0f;
    
    majTickIncrement = magMsd*magPow;
    if(axisDataType == OFX_CHART_AXIS_DATATYPE_NUMERIC || axisDataType == OFX_CHART_AXIS_DATATYPE_DATE)
        majTickIncrement = ceil(majTickIncrement);
    
    majTickMin = (min == 0 ? 0 : ceil(min / majTickIncrement) * majTickIncrement);
    majTickMax = (max == 0 ? 0: floor(max / majTickIncrement) * majTickIncrement);
    majTickIncrement = MAX(majTickIncrement, 0.00001);
    
}



double ofxChartAxisBase::convertToValue(double tick)
{
    if(axisDataType == OFX_CHART_AXIS_DATATYPE_DATE)
    {
        DateTime dt = ofxChart::getDateTime(minValue);
        switch (dit) {
            case OFX_CHART_DATERANGE_YEAR:
                //loop years to insert
                dt = DateTime(dt.year()+tick, 1, 1);
                break;
            case OFX_CHART_DATERANGE_MONTH:
                dt = DateTime(dt.year(), dt.month(), 1);
                for(int i=0; i< tick; i++)
                    ofxChart::addMonth(dt);
                break;
            case OFX_CHART_DATERANGE_DAY:
            {
                dt = DateTime(dt.year(), dt.month(), dt.day());
                Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(  dt.utcTime()  + (864000000000 * (Int64)tick));
                dt = DateTime(ts);
                
                //86400000000
//                for(int i=0; i< tick; i++)
//                    addDay(dt);
                break;
            }
            case OFX_CHART_DATERANGE_HOUR:
            {
                dt = DateTime(dt.year(), dt.month(), dt.day(), dt.hour());
                Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(  dt.utcTime()  + (36000000000 * tick));
                dt = DateTime(ts);
                break;
            }
            case OFX_CHART_DATERANGE_MINUTE:
            {
                dt = DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute());
                Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(  dt.utcTime()  + (600000000 * tick));
                dt = DateTime(ts);
                break;
            }
            case OFX_CHART_DATERANGE_SECOND:
            {
                //1000000
                dt = DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
                Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(  dt.utcTime()  + (10000000 * tick));
                dt = DateTime(ts);
                break;
            }
            case OFX_CHART_DATERANGE_MILLISECOND:
            {
                //1000
                dt = DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
                Poco::Timestamp ts = Poco::Timestamp::fromUtcTime(  dt.utcTime()  + (10000 * tick));
                dt = DateTime(ts);
                break;
            }
            default:
                break;
        }
        return ofxChart::getDoubleValue(dt);
    }
    return tick;
}

static void createPathWall(ofMesh &m, ofxChartAxisLineStyle style, ofPoint from, ofPoint to)
{
    
    switch (style) {
        case OFX_CHART_AXIS_LINE_SOLID:
            m.addVertex(from);
            m.addVertex(to);
            m.setMode(OF_PRIMITIVE_LINES);
            break;
        case OFX_CHART_AXIS_LINE_DASHED:
        {
            m.setMode(OF_PRIMITIVE_LINES);
            float dist = from.distance(to);
            
           
            for(int i=0; i< dist;)
            {
                
                ofVec3f distVec= from + ( ((to-from)*i)/dist);
                m.addVertex(distVec);
                i+=5;
                distVec =from + ( ((to-from)*i)/dist);
                m.addVertex(distVec);
                i+=5;
            }
            break;
        }
        case OFX_CHART_AXIS_LINE_DOTTED:
        {
            m.setMode(OF_PRIMITIVE_POINTS);
            float dist = from.distance(to);
            
            
            for(int i=0; i< dist;)
            {
                
                ofVec3f distVec= from + ( ((to-from)*i)/dist);
                m.addVertex(distVec);
                i+=5;
            }
            break;
        }

        default:
            break;
            
    }
    
  
}
void ofxChartAxisBase::updateWall(ofVec3f lower, ofVec3f higher)
{
    for(double i=majTickMin,c=0; i<=majTickMax; c++)
    {
        double val = convertToValue(i);
        ofxChartVec3d _valPoint = container->getContainerPoint(ofxChartVec3d(val,val,val),0, true);
        switch(direction)
        {
            case OFX_CHART_AXIS_DIRECTION_X:
            {
                if(lower.x == higher.x)
                    break;
                createPathWall(mWall, lineStyle, ofPoint(_valPoint.x, lower.y, lower.z), ofPoint(_valPoint.x, higher.y, higher.z));
                
                break;
                
            }
            case OFX_CHART_AXIS_DIRECTION_Y:
            {
                if(lower.y == higher.y)
                    break;
                createPathWall(mWall, lineStyle, ofPoint(lower.x, _valPoint.y, lower.z), ofPoint(higher.x, _valPoint.y, higher.z));
                break;
            }
            case OFX_CHART_AXIS_DIRECTION_Z:
                if(lower.z == higher.z)
                    break;
                createPathWall(mWall, lineStyle, ofPoint(lower.x, lower.y, _valPoint.z), ofPoint(higher.x, higher.y, _valPoint.z));
                break;
        }
        
        i += majTickIncrement;
    }
    
}


void ofxChartAxisBase::draw()
{
   
    ofSetColor(axisColor);
    mWall.draw();
}














void ofxChartAxis::update()
{
    ofxChartAxisBase::update();
    //calculating max and min based on the container's scale and offset
    //get range based on ticks direction
    ofxChartVec3d minContainerVector = container->getContainerValue(ofVec3f(0,0,0))
    , maxContainerVector = container->getContainerValue(container->getDimensions());
   
    switch(direction)
    {
        case OFX_CHART_AXIS_DIRECTION_X:
        {
            minValue = minContainerVector.x;//container->dataRange.min.x;
            maxValue = maxContainerVector.x;//container->dataRange.max.x;
             break;
        }
        case OFX_CHART_AXIS_DIRECTION_Y:
            minValue = minContainerVector.y;
            maxValue = maxContainerVector.y;
            break;
        case OFX_CHART_AXIS_DIRECTION_Z:
            minValue = -minContainerVector.z;
            maxValue = -maxContainerVector.z;
            break;
    }

    
    //update range vals: find lowest point in container dimensions
    calculateMajorTickIncrement();
    
    
}


void ofxChartAxis::draw(){
    //draw axis vertices (majors, minors, axis line (apply color, width, etc)
    if(!visible)
        return;
    
    ofxChartAxisBase::draw();
    
    
    ofPushStyle();
    ofPushMatrix();
    
    ofFill();
    ofSetColor(axisColor);
    ofxChartVec3d crossPoint = (crossing == OFX_CHART_AXIS_CROSS_VALUE
                                ? container->getContainerPoint(ofxChartVec3d(crossingValue,crossingValue,crossingValue),0, true)
                                : ofxChartVec3d(crossingValue, crossingValue, crossingValue));
    
    switch(direction)
    {
        case OFX_CHART_AXIS_DIRECTION_X:
            ofTranslate(0, crossPoint.y);
            ofRect(0, 0,  container->width,axisSize);
            break;
        case OFX_CHART_AXIS_DIRECTION_Y:
            ofTranslate(crossPoint.x, 0);
            ofRect(0, 0, axisSize, container->height);
            break;
        case OFX_CHART_AXIS_DIRECTION_Z:
            //TODO: rotate and draw rect
            ofTranslate(crossPoint.x,0, 0);
            break;
    }
    
    ofPath p;
    p.setFilled(false);
    p.setStrokeColor(axisColor);
    for(double i=majTickMin, c=0; i<=majTickMax;c++ )
    {
        
        double val = convertToValue(i);
        ofxChartVec3d _valPoint = container->getContainerPoint(ofxChartVec3d(val,val,val),0, true);
        ofPushMatrix();
        switch(direction)
        {
            case OFX_CHART_AXIS_DIRECTION_X:
            {
                ofTranslate(_valPoint.x, 0);
                p.moveTo(_valPoint.x, 0-(majWidthPixels/2));
                p.lineTo(_valPoint.x, majWidthPixels/2);
                
                //draw minors
                break;
                
            }
            case OFX_CHART_AXIS_DIRECTION_Y:
            {
                ofTranslate(0, _valPoint.y);
                p.moveTo(0-(majWidthPixels/2), _valPoint.y);
                p.lineTo(majWidthPixels/2, _valPoint.y);
                break;
            }
            case OFX_CHART_AXIS_DIRECTION_Z:
            {
                ofTranslate(0, 0, _valPoint.z);
                p.moveTo(0-(majWidthPixels/2), 0, _valPoint.z);
                p.lineTo(majWidthPixels/2, 0, _valPoint.z);
                break;
            }
        }
        
        //DRAW LABEL
        string valStr = "";
        if(axisDataType == OFX_CHART_AXIS_DATATYPE_DATE)
            valStr = labelFormatter->formatLabel( ofxChart::getDateTime(val), dit);
        else
            valStr = labelFormatter->formatLabel(val);
        static float fontHeight = 8;
        float labelY = valStr.length()*fontHeight; //TODO: TEXT ALIGN (CENTER, right, left)
        switch(textPosition)
        {
            case OFX_CHART_TEXT_POS_LEFT:
                ofTranslate(0-majWidthPixels-labelY, 0);
                break;
            case OFX_CHART_TEXT_POS_BOTTOM:
                ofTranslate(0-(labelY/2), 0-majWidthPixels-fontHeight);
                break;
            case OFX_CHART_TEXT_POS_RIGHT:
                ofTranslate(0, 0+majWidthPixels);
                break;
            case OFX_CHART_TEXT_POS_TOP:
                ofTranslate(0-(labelY/2), 0+majWidthPixels+fontHeight);
                break;
        }
        ofScale(1, -1); //after all we're drawing everything in axis space (i.e., upside down)
        
        ofSetColor(labelColor);
        ofDrawBitmapString(valStr, 0,0);
        
        
        
        
        i += majTickIncrement;
        ofPopMatrix();
    }
    
    ofNoFill();
    p.draw();
    
    ofPopMatrix();
    ofPopStyle();
    
    
    
    
    
}



