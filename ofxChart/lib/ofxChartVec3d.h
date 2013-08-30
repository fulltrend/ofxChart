/* Copyright (C) 2013 Sergey Yershov*/

#pragma once

#include "ofVec3f.h"

// redefining ofVec3f to hanld large data, such as date/time
struct  ofxChartVec3d{
    double x; double y; double z;
    ofxChartVec3d(){x=0;y=0;z=0;}
    ofxChartVec3d( const ofVec3f& vec  )
    {x = vec.x;y=vec.y;z=vec.z;}
    ofxChartVec3d( double _x, double _y, double _z =0 )
    {
        x = _x; y=_y;z=_z;
    }
    
    ofxChartVec3d  operator+( const ofxChartVec3d& pnt ) const;
    ofxChartVec3d& operator+=( const ofxChartVec3d& pnt );
    ofxChartVec3d  operator-( const ofxChartVec3d& vec ) const;
    ofxChartVec3d& operator-=( const ofxChartVec3d& vec );
    ofxChartVec3d  operator*( const ofxChartVec3d& vec ) const;
    ofxChartVec3d  operator*( float v ) const;
    ofxChartVec3d& operator*=( const ofxChartVec3d& vec );
    ofxChartVec3d  operator/( const ofxChartVec3d& vec ) const;
    ofxChartVec3d& operator/=( const ofxChartVec3d& vec );
    ofxChartVec3d  operator-() const;
    double  distance(const ofxChartVec3d& v2) const;
    static double  distance(const ofxChartVec3d& v1, const ofxChartVec3d& v2)
    {
        return v1.distance(v2);
    }
    
    ofVec3f toVec3f()
    {
        return ofVec3f(x,y,z);
    }
    
    ofxChartVec3d getCenter(const ofxChartVec3d& v2)
    {
        return ofxChartVec3d( ((x + v2.x) / 2), ((y + v2.y )/ 2.0) , ((z + v2.z) / 2.0) );
    }
    
};


inline ofxChartVec3d ofxChartVec3d::operator+( const ofxChartVec3d& pnt ) const {
	return ofxChartVec3d( x+pnt.x, y+pnt.y, z+pnt.z );
}

inline ofxChartVec3d& ofxChartVec3d::operator+=( const ofxChartVec3d& pnt ) {
	x+=pnt.x;
	y+=pnt.y;
	z+=pnt.z;
	return *this;
}

inline ofxChartVec3d ofxChartVec3d::operator-( const ofxChartVec3d& vec ) const {
	return ofxChartVec3d( x-vec.x, y-vec.y, z-vec.z );
}

inline ofxChartVec3d& ofxChartVec3d::operator-=( const ofxChartVec3d& vec ) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

inline ofxChartVec3d ofxChartVec3d::operator*( const ofxChartVec3d& vec ) const {
	return ofxChartVec3d( x*vec.x, y*vec.y, z*vec.z );
}
inline ofxChartVec3d ofxChartVec3d::operator*(  float v ) const {
	return ofxChartVec3d( x*v, y*v, z*v );
}

inline ofxChartVec3d& ofxChartVec3d::operator*=( const ofxChartVec3d& vec ) {
	x*=vec.x;
	y*=vec.y;
	z*=vec.z;
	return *this;
}

inline ofxChartVec3d ofxChartVec3d::operator/( const ofxChartVec3d& vec ) const {
	return ofxChartVec3d( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y, vec.z!=0 ? z/vec.z : z );
}

inline ofxChartVec3d& ofxChartVec3d::operator/=( const ofxChartVec3d& vec ) {
	vec.x!=0 ? x/=vec.x : x;
	vec.y!=0 ? y/=vec.y : y;
	vec.z!=0 ? z/=vec.z : z;
	return *this;
}

inline ofxChartVec3d ofxChartVec3d::operator-() const {
	return ofxChartVec3d( -x, -y, -z );
}


inline double ofxChartVec3d::distance( const ofxChartVec3d& v2) const
{
    return sqrt( pow((v2.x - x), 2 ) + pow((v2.y - y), 2) );
}
