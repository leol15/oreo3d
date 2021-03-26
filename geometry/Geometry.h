#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "../resource/Mesh.h"

class Geometry
{
public:
	Geometry();
	virtual ~Geometry();

	Mesh * getMesh() { return mesh_; };
protected:
	Mesh * mesh_;
	
};




#endif	// GEOMETRY_H_