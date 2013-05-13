/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChart3dUtils.h"

void ofxChartCreate3dRect(ofMesh *m, ofVec3f xyz, ofVec3f dimensions, ofColor color)
{
m->clear();

//if not filled (no background), just show the line loops

float w = dimensions.x, h =dimensions.y, z = dimensions.z;

float vx =xyz.x, vy=xyz.y, vz=xyz.z;


for(int i=0; i< 36;i++)
{
    m->addColor(color);
}
    // bottom (-z)
    m->addVertex(ofVec3f(        vx, vy, vz-z));
    m->addVertex(ofVec3f(        vx,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx+w, vy, vz-z));
    m->addVertex(ofVec3f(        vx+w, vy, vz-z));
    m->addVertex(ofVec3f(        vx,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx+w,  vy+h, vz-z));

    // top (+z)
    m->addVertex(ofVec3f(        vx, vy,  vz));
    m->addVertex(ofVec3f(        vx+w, vy,  vz));
    m->addVertex(ofVec3f(        vx,  vy+h,  vz));
    m->addVertex(ofVec3f(        vx,  vy+h,  vz));
    m->addVertex(ofVec3f(        vx+w, vy,  vz));
    m->addVertex(ofVec3f(        vx+w,vy+h,  vz));


    // right (+x)
    m->addVertex(ofVec3f(        vx+w, vy, vz-z));
    m->addVertex(ofVec3f(        vx+w,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx+w, vy,  vz));
    m->addVertex(ofVec3f(        vx+w, vy,  vz));
    m->addVertex(ofVec3f(        vx+w,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx+w,  vy+h,  vz));
    
    // left (-x)
    m->addVertex(ofVec3f(        vx, vy, vz-z));
    m->addVertex(ofVec3f(       vx, vy,  vz));
    m->addVertex(ofVec3f(        vx,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx,  vy+h, vz-z));
    m->addVertex(ofVec3f(       vx, vy,  vz));
    m->addVertex(ofVec3f(       vx,  vy+h,  vz));
    
    // front (+y)
    m->addVertex(ofVec3f(        vx, vy, vz-z));
    m->addVertex(ofVec3f(        vx+w, vy, vz-z));
    m->addVertex(ofVec3f(        vx, vy,  vz));
    m->addVertex(ofVec3f(        vx, vy,  vz));
    m->addVertex(ofVec3f(        vx+w, vy, vz-z));
    m->addVertex(ofVec3f(        vx+w, vy,  vz));
    
    // back (-y
    m->addVertex(ofVec3f(        vx,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx,  vy+h,  vz));
    m->addVertex(ofVec3f(        vx+w,  vy+h, vz-z));
    m->addVertex(ofVec3f(        vx+w,  vy+h, vz-z));
    m->addVertex(ofVec3f(       vx,  vy+h,  vz));
    m->addVertex(ofVec3f(        vx+w,  vy+h,  vz));
    
    m->setMode(OF_PRIMITIVE_TRIANGLES);

}