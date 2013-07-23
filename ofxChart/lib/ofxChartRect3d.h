/* Copyright (C) 2013 Sergey Yershov*/

#pragma once

#include "ofRectangle.h"

    class ofxChartRect3d: public ofRectangle {
        
    public:
        
       ofxChartRect3d(): z(position.z) {
            set(0,0,0,0,0,0);
       }        virtual ~ ofxChartRect3d(){}
        ofxChartRect3d(float px, float py,  float pz, float w, float h, float d) : z(position.z){
            set(px,py,pz,w,h,d);
        }
        ofxChartRect3d(const ofVec3f& p0, const ofVec3f& p1) : z(position.z) {
            set(p0,p1);
        }
        
        //        Rectangle3d(const ofPoint& p0, const ofPoint& p1);
        
        void set(float px, float py, float pz, float w, float h, float d){
            {
                x		= px;
                y		= py;
                z = pz;
                width	= w;
                height	= h;
                depth = d;
            }
        }
        void set(const ofVec3f& p0, const ofVec3f& p1){
            float x0,y0,z0,x1,y1,z1;
            
            x0 = MIN(p0.x, p1.x);
            x1 = MAX(p0.x, p1.x);
            y0 = MIN(p0.y, p1.y);
            y1 = MAX(p0.y, p1.y);
            z0 = MIN(p0.z, p1.z);
            z1 = MAX(p0.z, p1.z);
            
            float w = x1 - x0;
            float h = y1 - y0;
            float d = z1 - z0;
            
            set(x0,y0,z0,w,h,d);
            
        }
        
        void setZ(float pz) {
            z = pz;
        }
        
        
        bool inside(float px, float py, float pz) const {
            return inside(ofVec3f(px,py, pz));
        }
        
        //----------------------------------------------------------
        bool inside(const ofVec3f& p) const {
            return p.x >= getMinX() && p.y >= getMinY() && -p.z >= getMinZ() &&
            p.x <= getMaxX() && p.y <= getMaxY() && -p.z <= getMaxZ() ;
        }
        
        //----------------------------------------------------------
        bool inside(const ofxChartRect3d& rect) const {
            return inside(rect.getMinX(),rect.getMinY(), rect.getMinZ()) &&
            inside(rect.getMaxX(),rect.getMaxY(), rect.getMaxZ());
        }
        
        
        bool intersects(const ofxChartRect3d& rect) const {
            return (getMinX() <= rect.getMaxX() && getMaxX() >= rect.getMinX() &&
                    getMinY() <= rect.getMaxY() && getMaxY() >= rect.getMinY() &&
            getMinZ() >= -rect.getMaxZ() && getMaxZ() <= -rect.getMinZ()) ;
        }
        
        
        //        bool intersects(const ofPoint& p0, const ofPoint& p1) const;
        
        //        void growToInclude(float px, float py);
        //        void growToInclude(const ofPoint& p);
        //        void growToInclude(const ofRectangle& rect);
        //        void growToInclude(const ofPoint& p0, const ofPoint& p1);
        //
        //        ofRectangle getIntersection(const ofRectangle& rect) const;
        //
        //        ofRectangle getUnion(const ofRectangle& rect) const;
        
        //        void standardize();
        //        ofRectangle getStandardized() const;
        //        bool isStandardized() const;  // are width/height >= 0.0f
        
        //        float getArea() const;
        //        float getPerimeter() const;
        //        float getAspectRatio() const;
        
        
        //----------------------------------------------------------
        ofVec3f getMin() const {
            return ofVec3f(getMinX(),getMinY(), getMinZ());
        }
        
        //----------------------------------------------------------
        ofVec3f getMax() const {
            return ofVec3f(getMaxX(),getMaxY(), getMaxZ());
        }
        
        float getMinZ() const{
            return MIN(z, z + depth);
        }

        float getMaxZ() const{
        return MAX(z, z + depth);
    }

        
        //        float getLeft()   const;
        //        float getRight()  const;
        //        float getTop()    const;
        //        float getBottom() const;
        //
        //        ofPoint getTopLeft() const;
        //        ofPoint getTopRight() const;
        //        ofPoint getBottomLeft() const;
        //        ofPoint getBottomRight() const;
        //
        //        float getHorzAnchor(ofAlignHorz anchor) const;
        //        float getVertAnchor(ofAlignVert anchor) const;
        //
        //        ofPoint  getPosition() const;
        //        ofPoint& getPositionRef();
        //        
        //        ofPoint getCenter() const;
        
        float getZ() const{return z;}
        float getDepth() const{return depth;}
        
        
        float& z;
        float depth;
    };


