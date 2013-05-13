

/*
 * Primitives ported from Ogre Procedural 0.1
 * Ogre Procedural by 2010 Michael Broutin 
 * http://code.google.com/p/ogre-procedural/
 * 
 * Port started by Andreas Müller 
 * andreas [at] nanikawa [dot] com
 *
 */


#include "ofMath.h"
#include "ofLog.h"
#include "of3dPrimitives.h"


static bool		bPrimitiveGenerateTexCoords		= true;

bool ofGetPrimitiveGenerateTexCoords() {
	return bPrimitiveGenerateTexCoords;
}

void ofEnablePrimitiveGenerateTexCoords() {
	bPrimitiveGenerateTexCoords = true;
}

void ofDisablePrimitiveGenerateTexCoords() {
	bPrimitiveGenerateTexCoords = false;
}



//----------------------------------------------------------
// Box

#pragma mark ** Box **

ofMesh boxScratchMesh;

//----------------------------------------
void ofxChart::ofBox3d(float x, float y, float z, float size) {
	ofBox3d(ofPoint(x, y, z), size);
}

//----------------------------------------
void ofxChart::ofBox3d(float x, float y, float size) {
    ofxChart::ofBox3d(x, y, 0, size);
}

//----------------------------------------
void ofxChart::ofBox3d(const ofPoint& position, float size) {
	ofPushMatrix();
	ofTranslate(position);
	ofBox3d(size);
	ofPopMatrix();
}

//----------------------------------------
void ofxChart::ofBox3d(float size) {
	ofPushMatrix();
	if(ofGetCoordHandedness() == OF_LEFT_HANDED) {
		ofScale(1, 1, -1);
	}
	
	float h = size * .5;
	
	boxScratchMesh.clear();
	if(ofGetStyle().bFill) {
		ofVec3f vertices[] = {
			ofVec3f(+h,-h,+h), ofVec3f(+h,-h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,+h,+h),
			ofVec3f(+h,+h,+h), ofVec3f(+h,+h,-h), ofVec3f(-h,+h,-h), ofVec3f(-h,+h,+h),
			ofVec3f(+h,+h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,-h,+h), ofVec3f(+h,-h,+h),
			ofVec3f(-h,-h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,+h,-h), ofVec3f(-h,-h,-h),
			ofVec3f(-h,-h,+h), ofVec3f(-h,-h,-h), ofVec3f(+h,-h,-h), ofVec3f(+h,-h,+h),
			ofVec3f(-h,-h,-h), ofVec3f(-h,+h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,-h,-h)
		};
		boxScratchMesh.addVertices(vertices,24);
		
		static ofVec3f normals[] = {
			ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0),
			ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0),
			ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1),
			ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0),
			ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0),
			ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1)
		};
		boxScratchMesh.addNormals(normals,24);
		
		static ofVec2f tex[] = {
			ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1),
			ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1),
			ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0),
			ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
			ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
			ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0)
		};
		boxScratchMesh.addTexCoords(tex,24);
		
		static ofIndexType indices[] = {
			0,1,2, // right top left
			0,2,3, // right bottom right
			4,5,6, // bottom top right
			4,6,7, // bottom bottom left
			8,9,10, // back bottom right
			8,10,11, // back top left
			12,13,14, // left bottom right
			12,14,15, // left top left
			16,17,18, // ... etc
			16,18,19,
			20,21,22,
			20,22,23
		};
		boxScratchMesh.addIndices(indices,36);
		boxScratchMesh.setMode(OF_PRIMITIVE_TRIANGLES);
		//renderer->draw(vertexData);
		boxScratchMesh.draw();
	} else {
		ofVec3f vertices[] = {
			ofVec3f(+h,+h,+h),
			ofVec3f(+h,+h,-h),
			ofVec3f(+h,-h,+h),
			ofVec3f(+h,-h,-h),
			ofVec3f(-h,+h,+h),
			ofVec3f(-h,+h,-h),
			ofVec3f(-h,-h,+h),
			ofVec3f(-h,-h,-h)
		};
		boxScratchMesh.addVertices(vertices,8);
		
		static float n = sqrtf(3);
		static ofVec3f normals[] = {
			ofVec3f(+n,+n,+n),
			ofVec3f(+n,+n,-n),
			ofVec3f(+n,-n,+n),
			ofVec3f(+n,-n,-n),
			ofVec3f(-n,+n,+n),
			ofVec3f(-n,+n,-n),
			ofVec3f(-n,-n,+n),
			ofVec3f(-n,-n,-n)
		};
		boxScratchMesh.addNormals(normals,8);
		
		static ofIndexType indices[] = {
			0,1, 1,3, 3,2, 2,0,
			4,5, 5,7, 7,6, 6,4,
			0,4, 5,1, 7,3, 6,2
		};
		boxScratchMesh.addIndices(indices,24);
		
		boxScratchMesh.setMode(OF_PRIMITIVE_LINES);
		//renderer->draw(vertexData);
		boxScratchMesh.draw();
	}
	
	
	ofPopMatrix();
}





//----------------------------------------------------------
// Torus

#pragma mark ** Torus **



ofMesh torusScratchMesh;
ofxChart::ofTorusParameters lastGeneratedTorusParams;
ofxChart::ofTorusParameters currentTorusParams;


//----------------------------------------
void ofxChart::ofTorus(float x, float y, float z, float radius, float sectionRadius) {
	ofTorus(ofPoint(x, y, z), radius, sectionRadius);
}

//----------------------------------------
void ofxChart::ofTorus(float x, float y, float radius, float sectionRadius) {
    ofxChart::ofTorus(x, y, 0, radius, sectionRadius);
}

//----------------------------------------
void ofxChart::ofTorus(const ofPoint& position, float radius, float sectionRadius) {
	ofPushMatrix();
	ofTranslate(position);
	ofTorus(radius, sectionRadius);
	ofPopMatrix();
}

//----------------------------------------
void ofxChart::ofTorus(float radius, float sectionRadius ){
	
	if( torusScratchMesh.getNumVertices() == 0 ||
	   !lastGeneratedTorusParams.equals( radius, sectionRadius, currentTorusParams.numSegSection, currentTorusParams.numSegCircle ) ){
		
		ofGenerateTorusMesh( torusScratchMesh, radius, sectionRadius, currentTorusParams.numSegSection, currentTorusParams.numSegCircle );
		
		// Save the parameters of what we just generated
		lastGeneratedTorusParams.radius 		= radius;
		lastGeneratedTorusParams.sectionRadius 	= sectionRadius;		
		lastGeneratedTorusParams.numSegSection 	= currentTorusParams.numSegSection;
		lastGeneratedTorusParams.numSegCircle 	= currentTorusParams.numSegCircle;
	}
	
	if(ofGetStyle().bFill) {
		torusScratchMesh.drawFaces();
	} else {
		torusScratchMesh.drawWireframe(); // this won't really work, but leave it in for now.		
	}
}

//----------------------------------------
void ofxChart::ofSetTorusResolution( int numSegSection, int numSegCircle ){
	currentTorusParams.numSegSection = numSegSection;
	currentTorusParams.numSegCircle = numSegCircle;
}

//----------------------------------------
void ofxChart::ofGenerateTorusMesh( ofMesh& _mesh, float _radius, float _sectionRadius, int _numSegSection, int _numSegCircle ){
	
	///cout << "*** ofGenerateTorusMesh ***" << endl;
	
	_mesh.clear();	
		
	float uTile = 1.0f; // Texcoord tiling, do we want to support that?
	float vTile = 1.0f;	
	
	float deltaSection = (TWO_PI / _numSegSection);
	float deltaCircle = (TWO_PI / _numSegCircle);
	
	int offset = 0;
	
	for (int i = 0; i <= _numSegCircle; i++){
		for (int j = 0; j<= _numSegSection; j++) {
			
			ofVec3f c0( _radius, 0.0, 0.0);
			ofVec3f v0( _radius + _sectionRadius * cosf(j*deltaSection), _sectionRadius * sinf(j*deltaSection),0.0);
			
			ofQuaternion q( ofRadToDeg(i*deltaCircle), ofVec3f( 0.0f, 1.0f, 0.0f) );
			
			ofVec3f v = q * v0;
			ofVec3f c = q * c0;
			
			_mesh.addVertex( v );
			_mesh.addNormal( (v-c).getNormalized() );	
			
			if( ofGetPrimitiveGenerateTexCoords() ){
				_mesh.addTexCoord( ofVec2f(i/(float)_numSegCircle*uTile, j/(float)_numSegSection*vTile) );
			}
			
			if (i != _numSegCircle) {				
				_mesh.addIndex(offset + _numSegSection );
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + _numSegSection + 1);
				
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + 1);
				_mesh.addIndex(offset + _numSegSection + 1);				
			}
			offset ++;							  
		}
	}
	
}


//----------------------------------------------------------
// Cylinder

#pragma mark ** Cylinder **

ofMesh cylinderScratchMesh;
ofxChart::ofCylinderParameters lastGeneratedCylinderParams;
ofxChart::ofCylinderParameters currentCylinderParams;

//----------------------------------------
void ofxChart::ofCylinder(float x, float y, float z, float radius, float height, bool capped  ){
	ofCylinder( ofPoint(x,y,z), radius, height, capped );
}

//----------------------------------------
void ofxChart::ofCylinder(float x, float y, float radius, float height, bool capped ){
	ofCylinder( ofPoint(x,y,0), radius, height, capped );
}

//----------------------------------------
void ofxChart::ofCylinder(const ofPoint& position, float radius, float height, bool capped ){
	ofPushMatrix();
		ofTranslate(position);
		ofCylinder(radius, height, capped );
	ofPopMatrix();	
}

//----------------------------------------
void ofxChart::ofCylinder(float radius, float height, bool capped ){
	
	if( cylinderScratchMesh.getNumVertices() == 0 ||
	   !lastGeneratedCylinderParams.equals( radius, height, currentCylinderParams.numSegBase, currentCylinderParams.numSegHeight, capped ) ){
		
		ofGenerateCylinderMesh( cylinderScratchMesh, radius, height, currentCylinderParams.numSegBase, currentCylinderParams.numSegHeight, capped );
		
		// Save the parameters of what we just generated
		lastGeneratedCylinderParams.radius 			= radius;
		lastGeneratedCylinderParams.height 			= height;		
		lastGeneratedCylinderParams.numSegBase 		= currentCylinderParams.numSegBase;
		lastGeneratedCylinderParams.numSegHeight 	= currentCylinderParams.numSegHeight;
		lastGeneratedCylinderParams.capped 			= currentCylinderParams.capped;		
	}
	
	if(ofGetStyle().bFill) {
		cylinderScratchMesh.drawFaces();
	} else {
		cylinderScratchMesh.drawWireframe(); // this won't really work, but leave it in for now.		
	}
}


//----------------------------------------
void ofxChart::ofSetCylinderResolution( int numSegBase, int numSegHeight ){
	currentCylinderParams.numSegBase   = numSegBase;
	currentCylinderParams.numSegHeight = numSegHeight;		
}

//----------------------------------------
void ofxChart::ofGenerateCylinderMesh( ofMesh& _mesh, float _radius, float _height, int _numSegBase, int _numSegHeight, bool capped ){
	
	///cout << "*** ofGenerateCylinderMesh ***" << endl;
	
	_mesh.clear();	
		
	float uTile = 1.0f; // Texcoord tiling, do we want to support that?
	float vTile = 1.0f;	
	
	float deltaAngle = (TWO_PI / _numSegBase);
	float deltaHeight = _height/(float)_numSegHeight;
	
	int offset = 0;	
	
	for (int i = 0; i <=_numSegHeight; i++) {
		for (int j = 0; j<=_numSegBase; j++) {
			float x0 = _radius * cosf(j*deltaAngle);
			float z0 = _radius * sinf(j*deltaAngle);
			
			_mesh.addVertex( ofVec3f(x0, i*deltaHeight - (_height/2.0f), z0) );
			_mesh.addNormal( ofVec3f(x0,0,z0).getNormalized());
			
			if( ofGetPrimitiveGenerateTexCoords() ){
				_mesh.addTexCoord( ofVec2f(j/(float)_numSegBase*uTile, i/(float)_numSegHeight*vTile) );
			}
			
			if (i != _numSegHeight) {
				_mesh.addIndex(offset + _numSegBase );
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + _numSegBase + 1);
				
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + 1);
				_mesh.addIndex(offset + _numSegBase + 1);			
			}
			offset ++;
		}
	}
	if (capped)
	{
		//low cap
		int centerIndex = offset;
		_mesh.addVertex( ofVec3f(0,_height * -0.5f,0) );
		_mesh.addNormal( ofVec3f( 0.0f, -1.0f, 0.0f ) );
		if( ofGetPrimitiveGenerateTexCoords() ){
			_mesh.addTexCoord( ofVec2f(0.0,vTile) );
		}
		offset++;
		
		for (int j=0;j<=_numSegBase;j++)
		{
			float x0 = _radius * cosf(j*deltaAngle);
			float z0 = _radius * sinf(j*deltaAngle);
			
			_mesh.addVertex( ofVec3f(x0, _height * -0.5f, z0) );
			_mesh.addNormal( ofVec3f( 0.0f, -1.0f, 0.0f ) );
			if( ofGetPrimitiveGenerateTexCoords() ){
				_mesh.addTexCoord( ofVec2f(j/(float)_numSegBase,0.0) );
			}
			if (j!=_numSegBase)
			{
				_mesh.addIndex(offset+1);
				_mesh.addIndex(offset);
				_mesh.addIndex(centerIndex);
			}
			offset++;
		}
		
		// high cap
		centerIndex = offset;
		_mesh.addVertex( ofVec3f(0,_height * 0.5f,0) );
		_mesh.addNormal( ofVec3f( 0.0f, 1.0f, 0.0f ) );
		if( ofGetPrimitiveGenerateTexCoords() ){
			_mesh.addTexCoord( ofVec2f(0.0,0.0) );
		}
		offset++;
		
		for (int j=0;j<=_numSegBase;j++)
		{
			float x0 = _radius * cosf(j*deltaAngle);
			float z0 = _radius * sinf(j*deltaAngle);
			
			_mesh.addVertex( ofVec3f(x0, _height * 0.5f, z0) );
			_mesh.addNormal( ofVec3f( 0.0f, 1.0f, 0.0f ) );
			if( ofGetPrimitiveGenerateTexCoords() ){
				_mesh.addTexCoord( ofVec2f(j/(float)_numSegBase*uTile,vTile) );
			}
			
			if (j!=_numSegBase)
			{
				_mesh.addIndex(offset);
				_mesh.addIndex(offset+1);
				_mesh.addIndex(centerIndex);				
			}
			offset++;
		}
	}
}

//----------------------------------------------------------
// Capsule

#pragma mark ** Capsule **

ofMesh capsuleScratchMesh;
ofxChart::ofCapsuleParameters lastGeneratedCapsuleParams;
ofxChart::ofCapsuleParameters currentCapsuleParams;

//----------------------------------------
void ofxChart::ofCapsule(float x, float y, float z, float radius, float height){
	ofCapsule( ofPoint(x,y,z), radius, height );
}

//----------------------------------------
void ofxChart::ofCapsule(float x, float y, float radius, float height ){
	ofCapsule( ofPoint(x,y,0), radius, height );	
}

//----------------------------------------
void ofxChart::ofCapsule(const ofPoint& position, float radius, float height ){
	ofPushMatrix();
		ofTranslate(position);
		ofCapsule(radius, height );
	ofPopMatrix();		
}

//----------------------------------------
void ofxChart::ofCapsule(float radius, float height ){
	
	if( capsuleScratchMesh.getNumVertices() == 0 ||
	   !lastGeneratedCapsuleParams.equals( radius, height, currentCapsuleParams.numRings, currentCapsuleParams.numSegments, currentCapsuleParams.numSegHeight ) ){
		
		ofGenerateCapsuleMesh( capsuleScratchMesh, radius, height, currentCapsuleParams.numRings, currentCapsuleParams.numSegments, currentCapsuleParams.numSegHeight );
		
		// Save the parameters of what we just generated
		lastGeneratedCapsuleParams.radius 		= radius;
		lastGeneratedCapsuleParams.height 		= height;		
		lastGeneratedCapsuleParams.numRings 	= currentCapsuleParams.numRings;
		lastGeneratedCapsuleParams.numSegments 	= currentCapsuleParams.numSegments;
		lastGeneratedCapsuleParams.numSegHeight = currentCapsuleParams.numSegHeight;
		
	}
	
	if(ofGetStyle().bFill) {
		capsuleScratchMesh.drawFaces();
	} else {
		capsuleScratchMesh.drawWireframe(); // this won't really work, but leave it in for now.		
	}	
}

//----------------------------------------
void ofxChart::ofSetCapsuleResolution( int _numRings, int _numSegments, int _numSegHeight ){
	currentCapsuleParams.numRings     = _numRings;
	currentCapsuleParams.numSegments  = _numSegments;
	currentCapsuleParams.numSegHeight = _numSegHeight;	
}

//----------------------------------------
void ofxChart::ofGenerateCapsuleMesh( ofMesh& _mesh, float _radius, float _height, int _numRings, int _numSegments, int _numSegHeight ){
	
	///cout << "*** ofGenerateCapsuleMesh ***" << endl;
	
	_mesh.clear();	
	
	float uTile = 1.0f; // Texcoord tiling, do we want to support that?
	float vTile = 1.0f;	
	
	float fDeltaRingAngle = ((PI/2.0f) / _numRings);
	float fDeltaSegAngle = (TWO_PI / _numSegments);
	
	float sphereRatio   = _radius / (2 * _radius + _height);
	float cylinderRatio = _height / (2 * _radius + _height);
	
	int offset = 0;
	
	// Top half sphere
	
	// Generate the group of rings for the sphere
	for(unsigned int ring = 0; ring <= _numRings; ring++ ) {
		float r0 = _radius * sinf (ring * fDeltaRingAngle);
		float y0 = _radius * cosf (ring * fDeltaRingAngle);
		
		// Generate the group of segments for the current ring
		for(unsigned int seg = 0; seg <= _numSegments; seg++) {
			float x0 = r0 * cosf(seg * fDeltaSegAngle);
			float z0 = r0 * sinf(seg * fDeltaSegAngle);
			
			// Add one vertex to the strip which makes up the sphere
			_mesh.addVertex( ofVec3f( x0, 0.5*_height + y0, z0) );
			_mesh.addNormal( ofVec3f(x0, y0, z0).getNormalized() );
			
			if( ofGetPrimitiveGenerateTexCoords() ){
				//for (unsigned int tc=0;tc<numTexCoordSet;tc++)
				_mesh.addTexCoord( ofVec2f((float) seg / (float)_numSegments * uTile, (float) ring / (float)_numRings * vTile * sphereRatio) );
			}
			
			//if (ring != numRings) {
			// each vertex (except the last) has six indices pointing to it			
			_mesh.addIndex(offset);
			_mesh.addIndex(offset + _numSegments);
			_mesh.addIndex(offset + _numSegments + 1);
			
			_mesh.addIndex(offset + 1);
			_mesh.addIndex(offset);
			_mesh.addIndex(offset + _numSegments + 1);
			
			//}
			offset ++;
		}; // end for seg
	} // end for ring
	
	// Cylinder part
	float deltaAngle = (TWO_PI / _numSegments);
	float deltaHeight = _height/(float)_numSegHeight;
	
	for (int i = 1; i <= _numSegHeight-1; i++)
		for (int j = 0; j <= _numSegments; j++)
		{
			float x0 = _radius * cosf(j*deltaAngle);
			float z0 = _radius * sinf(j*deltaAngle);
			
			_mesh.addVertex( ofVec3f(x0, 0.5*_height-i*deltaHeight, z0) );
			_mesh.addNormal( ofVec3f(x0,0,z0).getNormalized());
			
			if( ofGetPrimitiveGenerateTexCoords() ){
				_mesh.addTexCoord( ofVec2f(j/(float)_numSegments*uTile, i/(float)_numSegHeight*vTile * cylinderRatio + sphereRatio) );
			}
			//if (i != numSegHeight) {
						
			_mesh.addIndex(offset);
			_mesh.addIndex(offset + _numSegments);
			_mesh.addIndex(offset + _numSegments + 1);
			
			_mesh.addIndex(offset + 1);
			_mesh.addIndex(offset);
			_mesh.addIndex(offset + _numSegments + 1);			
			
			//}
			offset ++;
		}
	
	// Bottom half sphere
	
	// Generate the group of rings for the sphere
	for(unsigned int ring = 0; ring <= _numRings; ring++ ) {
		float r0 = _radius * sinf ((PI/2.0f) + ring * fDeltaRingAngle);
		float y0 = _radius * cosf ((PI/2.0f) + ring * fDeltaRingAngle);
		
		// Generate the group of segments for the current ring
		for(unsigned int seg = 0; seg <= _numSegments; seg++) {
			float x0 = r0 * cosf(seg * fDeltaSegAngle);
			float z0 = r0 * sinf(seg * fDeltaSegAngle);
			
			// Add one vertex to the strip which makes up the sphere
			_mesh.addVertex( ofVec3f( x0, -0.5*_height + y0, z0) );
			
			_mesh.addNormal( ofVec3f(x0, y0, z0).getNormalized() );
			
			if( ofGetPrimitiveGenerateTexCoords() ){
				//for (unsigned int tc=0;tc<numTexCoordSet;tc++)
				_mesh.addTexCoord( ofVec2f((float) seg / (float)_numSegments * uTile, (float) ring / (float)_numRings * vTile*sphereRatio + cylinderRatio + sphereRatio) );
			}
			
			if (ring != _numRings) {
				// each vertex (except the last) has six indices pointing to it				
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + _numSegments);
				_mesh.addIndex(offset + _numSegments + 1);
				
				_mesh.addIndex(offset + 1);
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + _numSegments + 1);				
			}
			offset ++;
		}; // end for seg
	} // end for ring
}



//----------------------------------------------------------
// Cone

#pragma mark ** Cone **

ofMesh coneScratchMesh;
ofxChart::ofConeParameters lastGeneratedConeParams;
ofxChart::ofConeParameters currentConeParams;

//----------------------------------------
void ofxChart::ofCone3d(float x, float y, float z, float radius, float height){
	ofCone3d( ofPoint(x,y,z), radius, height );
}

//----------------------------------------
void ofxChart::ofCone3d(float x, float y, float radius, float height){
	ofCone3d( ofPoint(x,y,0), radius, height );
}

//----------------------------------------
void ofxChart::ofCone3d(const ofPoint& position, float radius, float height){
	ofPushMatrix();
    ofTranslate(position);
    ofCone3d(radius, height);
	ofPopMatrix();
}

//----------------------------------------
void ofxChart::ofCone3d(float radius, float height ){
	
	if( coneScratchMesh.getNumVertices() == 0 ||
	   !lastGeneratedConeParams.equals( radius, height, currentConeParams.numSegBase, currentConeParams.numSegHeight ) ){
		
		ofGenerateConeMesh( coneScratchMesh, radius, height, currentConeParams.numSegBase, currentConeParams.numSegHeight );
		
		// Save the parameters of what we just generated
		lastGeneratedConeParams.radius 			= radius;
		lastGeneratedConeParams.height 			= height;
		lastGeneratedConeParams.numSegBase 		= currentConeParams.numSegBase;
		lastGeneratedConeParams.numSegHeight 	= currentConeParams.numSegHeight;
	}
	
	if(ofGetStyle().bFill) {
		coneScratchMesh.drawFaces();
	} else {
		coneScratchMesh.drawWireframe(); // this won't really work, but leave it in for now.
	}
	
}

//----------------------------------------
void ofxChart::ofSetConeResolution( int numSegBase, int numSegHeight ){
	currentConeParams.numSegBase = numSegBase;
	currentConeParams.numSegHeight = numSegHeight;
}


//----------------------------------------
void ofxChart::ofGenerateConeMesh( ofMesh& _mesh, float _radius, float _height, int _numSegBase, int _numSegHeight )
{
	//cout << "*** ofGenerateConeMesh ***" << endl;
	
	_mesh.clear();
	
	float uTile = 1.0f; // Texcoord tiling, do we want to support that?
	float vTile = 1.0f;
	
	float deltaAngle = (TWO_PI / _numSegBase);
	float deltaHeight = _height/(float)_numSegHeight;
	
	ofVec3f refNormal = ofVec3f(_radius, _height, 0.f).getNormalized();
	
	ofQuaternion q;
	
	int offset = 0;
	
	for (int i = 0; i <= _numSegHeight; i++)
	{
		float r0 = _radius * (1 - i / (float)_numSegHeight);
		for (int j = 0; j<= _numSegBase; j++)
		{
			float x0 = r0 * cosf(j*deltaAngle);
			float z0 = r0 * sinf(j*deltaAngle);
			
			ofVec3f pos( x0, i*deltaHeight, z0 );
			_mesh.addVertex( pos );
			
			q.makeRotate( ofRadToDeg(-j*deltaAngle), 0.0f, 1.0f, 0.0f );
			
			_mesh.addNormal(q*refNormal);
			
			if( ofGetPrimitiveGenerateTexCoords()  ){
				_mesh.addTexCoord( ofVec2f(j/(float)_numSegBase*uTile, i/(float)_numSegHeight*vTile) );
			}
			
			
			if (i != _numSegHeight && j != _numSegBase)
			{
				_mesh.addIndex(offset + _numSegBase + 1);
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + _numSegBase + 2);
				
				_mesh.addIndex(offset);
				_mesh.addIndex(offset + 1);
				_mesh.addIndex(offset + _numSegBase + 2);
			}
			
			offset ++;
		}
	}
	
	//low cap
	int centerIndex = offset;
	
	_mesh.addVertex( ofVec3f(0,0,0) );
	_mesh.addNormal( ofVec3f(0.0f, -1.0f, 0.0) );
	if( ofGetPrimitiveGenerateTexCoords() ){
		_mesh.addTexCoord( ofVec2f(0.0,vTile) );
	}
	offset++;
	
	for (int j=0; j <= _numSegBase; j++)
	{
		float x0 = _radius * cosf(j*deltaAngle);
		float z0 = _radius * sinf(j*deltaAngle);
		
		_mesh.addVertex( ofVec3f(x0, 0.0f, z0) );
		_mesh.addNormal( ofVec3f(0.0f, -1.0f, 0.0) );
		_mesh.addTexCoord( ofVec2f(j/(float)_numSegBase*uTile,0.0) );
		if (j!=_numSegBase)
		{
            
			_mesh.addIndex(offset+1);
			_mesh.addIndex(offset);
			_mesh.addIndex(centerIndex);
		}
		offset++;
	}
}
