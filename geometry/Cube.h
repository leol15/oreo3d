#ifndef CUBE_H_
#define CUBE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

// #include "../resource/Mesh.h"
#include "Geometry.h"


/*
	Manage a cube
	8 points, 
*/
class Cube : public Geometry {
public:
	Cube();
	virtual ~Cube();

};


#endif	// CUBE_H_