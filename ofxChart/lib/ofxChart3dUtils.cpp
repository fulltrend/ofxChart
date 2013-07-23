/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChart3dUtils.h"

void rotateMatP2(ofVec3f p1, ofVec3f target)
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