/* Copyright (C) 2013 Sergey Yershov*/



#include "ofxChartAxisSet.h"

void ofxChartAxisSetBase::init()
{
    _container = ofPtr<ofxChartContainerAxisSet>(new ofxChartContainerAxisSet());
    
    ofColor defaultColor = ofColor(255,255,255);
    walls.left = new ofxChartAxisWall(OFX_CHART_AXIS_WALL_LEFT,_container);
    walls.left->setColor(defaultColor/2);
    walls.back = new ofxChartAxisWall(OFX_CHART_AXIS_WALL_BACK,_container);
    walls.back ->setColor(defaultColor);
    walls.right = new ofxChartAxisWall(OFX_CHART_AXIS_WALL_RIGHT,_container);
    walls.bottom = new ofxChartAxisWall(OFX_CHART_AXIS_WALL_BOTTOM,_container);
    walls.bottom->setColor(defaultColor/3);
    walls.top = new ofxChartAxisWall(OFX_CHART_AXIS_WALL_TOP,_container);
    walls.top->setColor(defaultColor);
    
    ofAddListener(ofEvents().setup, this, &ofxChartAxisSetBase::setup);
    _isDynamicRange = true;
    
}




void ofxChartAxisSetBase::setup(ofEventArgs &data)
{
    
    
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.useDepth = false;
    s.useStencil = true;
    //s.depthStencilAsTexture = true;
    fbo.allocate(s);
    
    
    //ofAddListener(ofEvents().draw, this, &ofxChartAxisSetBase::draw);
    
}


void ofxChartAxisSetBase::setStaticRange(ofxChartVec3d min, ofxChartVec3d max)
{
    _isDynamicRange = false;
    //update range
    //update point size
    getContainer()->dataRange.min = min;
    getContainer()->dataRange.max = max;
    
    //BUG:
    //getContainer()->calculateDataPointSize(max-min) ;
    
    
    this->invalidate();
}


void ofxChartAxisSetBase::update()
{
    ofPtr<ofxChartContainerAxisSet> c = this->getContainer();
    
    //UPDATE RANGE OF ALL SERIES
    
    if(_isDynamicRange){
        ofxChartVec3d svRange;
        
        for (int i=0; i< this->getSeries().size(); i++) {
            ofxChartDataRange r = ofxChartAxisSetBase::getDataSeries(i)->getRange();
            //TODO: Value vs. Index range
            //calculate data point size
            if(i==0)
            {
                c->dataRange = r;
                svRange = ofxChartAxisSetBase::getDataSeries(i)->getShortestValueRange();
            }
            else
            {
                c->dataRange.min = c->getMin(c->dataRange.min, r.min);
                c->dataRange.max = c->getMax(c->dataRange.max, r.max);
                c->dataRange.size = MAX(c->dataRange.size, r.size);
                
                svRange = c->getMin(svRange, ofxChartAxisSetBase::getDataSeries(i)->getShortestValueRange()) ;
            }
            
            //    ofxChartAxisSetBase::getDataSeries(i)->update(c);
            
        }
        //CALCULATE DATA POINT SIZE. TODO: calculate indexed size
        c->calculateDataPointSize(svRange);
    }
    c->isInvalid = false;
}




void ofxChartAxisSetBase::draw()
{
    if(!this->getContainer()->getVisible())
        return;
    
    if(this->getContainer()->isInvalid)
    {
        update();
        drawFBO();
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    fbo.draw(0,0);
    glDisable(GL_BLEND);
    
    
}

void ofxChartAxisSetBase::drawFBO()
{
    //DRAW TO FBO:
    ofPtr<ofxChartContainerAxisSet> c = this->getContainer();
    GLfloat modl[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, modl); // TODO: get the current modelview matrix
    
    this->fbo.begin();
    
    ofPushStyle();
    ofLoadMatrix(ofMatrix4x4(modl));
    ofMultMatrix(ofxChartAxisSetBase::getContainer()->getModelMatrix());
    
    
    glClearColor(0, 0, 0, 0);
    glClear( GL_COLOR_BUFFER_BIT);
    
    //DRAW WALLS
    ofxChartAxisSetBase::walls.back->draw();
    ofxChartAxisSetBase::walls.left->draw();
    ofxChartAxisSetBase::walls.bottom->draw();
    ofxChartAxisSetBase::walls.top->draw();
    ofxChartAxisSetBase::walls.right->draw();
    
    //DRAW AXES
    for(int axi=0; axi< axes.size(); axi++)
        axes[axi]->draw();
    
    //glEnable(GL_DEPTH_TEST);
    
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glColorMask(0, 0, 0, 0);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    
    ofSetHexColor(0xffffff);
    //draw rect mesh
    {
        ofMesh m;
        ofxChartCreate3dRect(&m, ofVec3f().zero(), this->getContainer()->getDimensions(), ofColor(255,255,255));
        m.draw();
    }
    
    glColorMask(1, 1, 1, 1);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    ofPushMatrix();
    int seriesSize = _series.size();
    for(int i=0; i < seriesSize; i++)
    {
        ofxChartAxisSetBase::getDataSeries(i)->draw();
    }
    ofPopMatrix();
        
    
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    
    ofPopStyle();

    
    this->fbo.end();
    
}