
/*
 * Primitives ported from Ogre Procedural 0.1
 * Ogre Procedural by 2010 Michael Broutin
 * http://code.google.com/p/ogre-procedural/
 *
 * Port started by Andreas Müller
 * andreas [at] nanikawa [dot] com
 *
 */



#pragma once

#include "ofGraphics.h"
#include "ofVectorMath.h"

bool ofGetPrimitiveGenerateTexCoords();
void ofEnablePrimitiveGenerateTexCoords();
void ofDisablePrimitiveGenerateTexCoords();

namespace ofxChart {
    
    
    // The default resolutions for the primitives are set in their helper classes at the bottom
    
    
    
    //----------------------------------------------------------
    // Box
    
    void ofBox3d(float x, float y, float z, float size);
    void ofBox3d(float x, float y, float size);
    void ofBox3d(const ofPoint& position, float size);
    void ofBox3d(float size);
    
    
    
    //----------------------------------------------------------
    // Torus
    
    void ofTorus(float x, float y, float z, float radius, float sectionRadius);
    void ofTorus(float x, float y, float radius, float sectionRadius);
    void ofTorus(const ofPoint& position, float radius, float sectionRadius);
    void ofTorus(float radius, float sectionRadius );
    
    void ofSetTorusResolution( int numSegSection, int numSegCircle );
    void ofGenerateTorusMesh( ofMesh& _mesh, float _radius, float _sectionRadius, int _numSegSection = 16, int _numSegCircle = 16 );
    
    
    
    
    
    
    
    //----------------------------------------------------------
    // Cylinder
    
    void ofCylinder(float x, float y, float z, float radius, float height, bool capped = true );
    void ofCylinder(float x, float y, float radius, float height, bool capped = true );
    void ofCylinder(const ofPoint& position, float radius, float height, bool capped = true );
    void ofCylinder(float radius, float height, bool capped = true );
    
    void ofSetCylinderResolution( int numSegBase, int numSegHeight );
    void ofGenerateCylinderMesh( ofMesh& _mesh, float _radius, float _height, int _numSegBase = 16, int _numSegHeight = 16, bool capped = true );
    
    
    
    
    //----------------------------------------------------------
    // Capsule
    
    void ofCapsule(float x, float y, float z, float radius, float height);
    void ofCapsule(float x, float y, float radius, float height );
    void ofCapsule(const ofPoint& position, float radius, float height );
    void ofCapsule(float radius, float height );
    
    void ofSetCapsuleResolution( int _numRings, int _numSegments, int _numSegHeight );
    void ofGenerateCapsuleMesh( ofMesh& _mesh, float _radius, float _height, int _numRings = 8, int _numSegments = 16, int _numSegHeight = 1 );
    
    
    
    //----------------------------------------------------------
    // Cone
    
    void ofCone3d(float x, float y, float z, float radius, float height);
    void ofCone3d(float x, float y, float radius, float height);
    void ofCone3d(const ofPoint& position, float radius, float height);
    void ofCone3d(float radius, float height );
    
    void ofSetConeResolution( int numSegBase, int numSegHeight );
    void ofGenerateConeMesh( ofMesh& _mesh, float _radius, float _height, int _numSegBase = 16, int _numSegHeight = 16 );
    
    
    
    
    
    
    // Small helper classes to keep track of with what settings we've generated meshes with
    
    //----------------------------------------------------------
    class ofSphereParameters{
    public:
        
        ofSphereParameters() {
            radius = -1.0f; numRings = 16; numSegments = 16; // set defaults, apart from radius
        }
        
        bool equals( float _radius, int _numRings, int _numSegments ){
            if( radius == _radius && numRings == _numRings && numSegments == _numSegments ){
                return true;
            } else {
                return false;
            }
        }
        
        float radius;
        int numRings;
        int numSegments;
    };
    
    
    //----------------------------------------------------------
    class ofTorusParameters{
    public:
        
        ofTorusParameters() {
            radius = -1.0f; sectionRadius = -1.0f; numSegSection = 16; numSegCircle = 25; // set defaults, apart from radius
        }
        
        bool equals( float _radius, float _sectionRadius, int _numSegSection, int _numSegCircle ){
            if( radius == _radius && sectionRadius == _sectionRadius && numSegSection == _numSegSection && numSegCircle == _numSegCircle ){
                return true;
            } else {
                return false;
            }
        }
        
        float radius;
        float sectionRadius;
        int numSegSection;
        int numSegCircle;
    };
    
    
    //----------------------------------------------------------
    class ofConeParameters{
    public:
        
        ofConeParameters() {
            radius = -1.0f; height = -1.0f; numSegBase = 16; numSegHeight = 16; // set defaults, apart from radius and height
        }
        
        bool equals( float _radius, float _height, int _numSegBase, int _numSegHeight ){
            if( radius == _radius && height == _height && numSegBase == _numSegBase && numSegHeight == _numSegHeight ){
                return true;
            } else {
                return false;
            }
        }
        
        float radius;
        float height;
        int numSegBase;
        int numSegHeight;
    };
    
    
    //----------------------------------------------------------
    class ofCylinderParameters{
    public:
        
        ofCylinderParameters() {
            radius = -1.0f; height = -1.0f; numSegBase = 16; numSegHeight = 16; capped = true; // set defaults, apart from radius and height
        }
        
        bool equals( float _radius, float _height, int _numSegBase, int _numSegHeight, bool _capped ){
            if( radius == _radius && height == _height && numSegBase == _numSegBase && numSegHeight == _numSegHeight && capped == _capped ){
                return true;
            } else {
                return false;			
            }
        }
        
        float radius;
        float height;
        int numSegBase;
        int numSegHeight;
        bool capped;
    };
    
    
    //----------------------------------------------------------
    class ofCapsuleParameters{
    public:	
        
        ofCapsuleParameters() { 
            radius = -1.0f; height = -1.0f; numRings = 8; numSegments = 16; numSegHeight = 1; // set defaults, apart from radius and height
        }
        
        bool equals( float _radius, float _height, int _numRings, int _numSegments, int _numSegHeight ){
            if( radius == _radius && height == _height && numRings == _numRings && numSegments == _numSegments && numSegHeight == _numSegHeight ){
                return true;
            } else {
                return false;			
            }
        }
        
        float radius;
        float height;
        int numRings;
        int numSegments;
        int numSegHeight;
    };
    
}