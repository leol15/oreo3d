

CPP=g++ -std=c++17
CPPFLAGS=-Wall -g

COMPILE_FLAG = -lglfw -lGLEW -lGLU -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl -lglad -I../../libs/glm-0.9.7.1/

GLM_PATH =  -I../../libs/glm-0.9.7.1/ 

# things in resource/
EDITOR_OBJS = ../editor/Control.o
EDITOR_HEADERS = ../editor/Control.h

RESOURCE_OBJS = ../resource/Mesh.o ../resource/GLMesh.o ../resource/ShaderProgram.o
RESOURCE_HEADERS = ../resource/Mesh.h ../resource/GLMesh.h ../resource/ShaderProgram.h

GEOMETRY_OBJS = ../geometry/Geometry.o ../geometry/Cube.o ../geometry/Sphere.o
GEOMETRY_HEADERS = ../geometry/Geometry.h ../geometry/Cube.h ../geometry/Sphere.h

SCENE_OBJS = ../scene/SceneNode.o ../scene/Drawable.o
SCENE_HEADERS = ../scene/SceneNode.h ../scene/Drawable.h

# build and run it

all: trace_world
	./trace_world

trace_world: trace_world.cpp Tracer.o
	$(CPP) $(CPPFLAGS) $< -pthread -o $@ $(RESOURCE_OBJS) \
		$(GEOMETRY_OBJS) $(EDITOR_OBJS) $(SCENE_OBJS) Tracer.o\
		$(COMPILE_FLAG)



Tracer.o: Tracer.cpp Tracer.h
	$(CPP) $(CPPFLAGS) -c $< $(GLM_PATH)
