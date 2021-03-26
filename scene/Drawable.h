#ifndef DRAWABLE_
#define DRAWABLE_

#include "../resource/GLMesh.h"

// contains everything you need to draw some triangles
class Drawable {
public:
	Drawable() : glmesh_() { };
	virtual ~Drawable() { };
	
	void draw();
protected:
	GLMesh glmesh_;

};


#endif	// DRAWABLE_

