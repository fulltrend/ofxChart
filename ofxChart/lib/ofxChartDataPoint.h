/* Copyright (C) 2013 Sergey Yershov*/


#ifndef __ofxChart__ofxChartDataPoint__
#define __ofxChart__ofxChartDataPoint__

#include "ofmain.h"
#include "Poco/DateTime.h"
#include "ofxChartVec3d.h"
#include "ofxChartUtils.h"



class ofxChartDataPointBase
{
public:
    
    virtual ~ ofxChartDataPointBase(){}
    ofColor color;
    string title;
    
    
};




//////////////              SINGLE POINT            ///////////


template<class PT>
class ofxChartDataPointSingle_ : public ofxChartDataPointBase
{
public:
    PT pt;

    ~ ofxChartDataPointSingle_(){}
    ofxChartDataPointSingle_(){}
    ofxChartDataPointSingle_<PT>( PT pt);
     ofxChartDataPointSingle_<PT>( double pt);
    ofxChartDataPointSingle_<PT>(PT _x, ofColor _color );
    
    template<class srcPT>
    ofxChartDataPointSingle_<PT>operator=(ofxChartDataPointSingle_<srcPT>  mom){
        //copyFrom( mom );
        return ofxChartDataPointSingle_<PT>(mom.x, mom._color);
    }
    

    
    
};

template<class PT>
ofxChartDataPointSingle_<PT>::ofxChartDataPointSingle_(PT _p){
    pt = _p;
    
}
template<class PT>
ofxChartDataPointSingle_< PT>::ofxChartDataPointSingle_( PT _p, ofColor c){
    pt = _p;
    color = c;
}



typedef ofxChartDataPointSingle_<float> ofxChartDataPointFloat;
typedef ofxChartDataPointSingle_<Poco::DateTime> ofxChartDataPointDate;




///////        XY       //////////



template<class _X, class _Y>
class ofxChartDataPointXY_: public ofxChartDataPointBase
{
public:
    //	virtual ~ ofxChartDataPointXYZ(){}
    _X x;
    _Y y;

    ~ ofxChartDataPointXY_(){}
    ofxChartDataPointXY_(){}
    ofxChartDataPointXY_<_X,_Y>( _X _x, _Y _y);
    ofxChartDataPointXY_<_X,_Y>( _X _x, _Y _y, ofColor _color );
    
    //    template<class _srcX, class _srcY, class _srcZ>
    ofxChartDataPointXY_<float, string>operator=(ofxChartDataPointXY_<float, string>  mom){
        //copyFrom( mom );
        return ofxChartDataPointXY_<float, string>(mom.x, mom.y);
    }

    ofxChartDataPointXY_<float, float>operator=(ofxChartDataPointXY_<float, float>  mom){
        //copyFrom( mom );
        return ofxChartDataPointXY_<float, float>(mom.x, mom.y);
    }
    void setPointSize(float _point_size)
    {
        pointSize = _point_size;
        _ps_overwrite = true;
    }
    float getPointSize() {return pointSize;}
    ofxChartVec3d getDoubleValue()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(x),  ofxChart::getDoubleValue(y),0);
    }

protected:
    bool _ps_overwrite;
private:
    float pointSize;

};

typedef ofxChartDataPointXY_<float, std::string> ofxChartDataPointFloatString;
typedef ofxChartDataPointXY_<float, float> ofxChartDataPointFloat2d;
typedef ofxChartDataPointXY_<int, int> ofxChartDataPointInt2d;
typedef ofxChartDataPointXY_<float, Poco::DateTime> ofxChartDataPointFloatDate;



template<class _X, class _Y>
ofxChartDataPointXY_< _X,  _Y>::ofxChartDataPointXY_( _X _x, _Y _y){
    x = _x;
    y= _y;
    pointSize = 1;
    
}
template<class _X, class _Y>
ofxChartDataPointXY_< _X,  _Y>::ofxChartDataPointXY_( _X _x, _Y _y, ofColor c){
    x = _x;
    y= _y;
    color = c;
    pointSize = 1;
}






////////            XYZ DATAPOINT           /////////


template<class _X, class _Y, class _Z>
class ofxChartDataPointXYZ_: public ofxChartDataPointXY_<_X, _Y>
{
public:

    
    _Z z;
    
    ~ ofxChartDataPointXYZ_(){}
    ofxChartDataPointXYZ_(){}
    ofxChartDataPointXYZ_<_X,_Y,_Z>( _X _x, _Y _y );
    ofxChartDataPointXYZ_<_X,_Y,_Z>( _X _x, _Y _y,_Z _z );
    ofxChartDataPointXYZ_<_X,_Y,_Z>( _X _x, _Y _y,_Z _z, float _point_size );
    ofxChartDataPointXYZ_<_X,_Y,_Z>( _X _x, _Y _y,_Z _z, ofColor _color );

//    template<class _srcX, class _srcY, class _srcZ>
    ofxChartDataPointXYZ_<float, float, float>operator=(ofxChartDataPointXYZ_<float, float, float>  mom){
        //copyFrom( mom );
            return ofxChartDataPointXYZ_<float, float, float>(mom.x, mom.y, mom.z);
    }
    
    ofxChartDataPointXYZ_<float, string, float>operator=(ofxChartDataPointXYZ_<float, string, float>  mom){
        //copyFrom( mom );
        return ofxChartDataPointXYZ_<float, string, float>(mom.x, mom.y, mom.z);
    }
    
    ofxChartVec3d getDoubleValue()
    {
        return ofxChartVec3d( ofxChart::getDoubleValue(ofxChartDataPointXY_<_X, _Y>::x)
                       ,  ofxChart::getDoubleValue(ofxChartDataPointXY_<_X, _Y>::y)
                       ,  z);
    }
    
};

template<class _X, class _Y, class _Z>
    ofxChartDataPointXYZ_< _X,  _Y,  _Z>::ofxChartDataPointXYZ_( _X _x, _Y _y){
        this->ofxChartDataPointXYZ_(_x, _y, 0);
//        this->x = _x;
//    this->y= _y;
//    this->pointSize = 1;
//    z = 0;
}
    
template<class _X, class _Y, class _Z>
        ofxChartDataPointXYZ_< _X,  _Y,  _Z>::ofxChartDataPointXYZ_( _X _x, _Y _y,_Z _z){
            this->x = _x;
            this->y= _y;
            z = _z;
}

    template<class _X, class _Y, class _Z>
    ofxChartDataPointXYZ_< _X,  _Y,  _Z>::ofxChartDataPointXYZ_( _X _x, _Y _y,_Z _z, float _point_size){
        this->x = _x;
        this->y= _y;
        z = _z;
        this->setPointSize(_point_size);
    }

template<class _X, class _Y, class _Z>
ofxChartDataPointXYZ_< _X,  _Y,  _Z>::ofxChartDataPointXYZ_( _X _x, _Y _y,_Z _z, ofColor _color){
    this->x = _x;
    this->y= _y;
    this->pointSize = 1;
    z = _z;
    ofxChartDataPointBase::color = _color;
}

typedef ofxChartDataPointXYZ_<float, float, float> ofxChartDataPointFloat3d;
typedef ofxChartDataPointXYZ_<int, int, int> ofxChartDataPointInt3d;


#endif /* defined(__ofxChart__ofxChartDataPoint__) */
