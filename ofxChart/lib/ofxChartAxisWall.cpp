/* Copyright (C) 2013 Sergey Yershov*/


#include "ofxChartAxisWall.h"

void ofxChartAxisWall::draw(){
    if(!enableSeeThrough)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
        glDisable(GL_CULL_FACE);
    
    m.draw();
    
    glDisable(GL_CULL_FACE);
}


void ofxChartAxisWall::update( vector<ofxChartAxisBase* > axes)
{
    //if(!container->isInvalid)return;
    //if see through then set percentage of see though
    m.clear();
    if( !visible) return;
    
    //if not filled (no background), just show the line loops
    
    float cw = container->width, ch =container->height, cz = container->depth;
    //ofColor shadedColor = color/2;shadedColor.a = color.a;
    
    float z = 0, w= 0, h=0;
    float vx =0, vy=0, vz=0;
    int axs = axes.size();
    
    switch(position)
    {
        case OFX_CHART_AXIS_WALL_LEFT:
            vx = -thickness;
            w = thickness;
            h = ch;
            z=cz;
            
            for(int a=0; a< axs; a++)
            {
                axes[a]->updateWall(ofVec3f(0,0,0), ofVec3f(0,h,-z));
            }

            break;
        case OFX_CHART_AXIS_WALL_BACK:
            vz=-cz;
            w=cw;h=ch;z=thickness;
            //draw lines. todo: switch on line types, check if drawing of lines enabled on the aix

            for(int a=0; a< axs; a++)
            {
                axes[a]->updateWall(ofVec3f(0,0,vz), ofVec3f(w,h,vz));

            }
            break;
        case OFX_CHART_AXIS_WALL_BOTTOM:
            h=-thickness;
            z=cz;
            w = cw;
            for(int a=0; a< axs; a++)
            {
                axes[a]->updateWall(ofVec3f(0,0,0), ofVec3f(w,0,-z));

            }
            break;
        case OFX_CHART_AXIS_WALL_RIGHT:
            
            break;
        case    OFX_CHART_AXIS_WALL_TOP:
            h=thickness;
            vy = ch;
            z=cz;
            w = cw;
            for(int a=0; a< axs; a++)
            {
                axes[a]->updateWall(ofVec3f(0,ch,0), ofVec3f(cw,ch,-z));
                
            }
            break;
    }
    
    ofxChartCreate3dRect(&m, ofVec3f(vx,vy,vz), ofVec3f(w,h,z), color);
    m.setMode(OF_PRIMITIVE_TRIANGLES);
    
}


