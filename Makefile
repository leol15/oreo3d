
CPP=g++
CPPFLAGS=-Wall -g

COMPILE_FLAG = -lglfw -lGLEW -lGLU -lGL -lXrandr -lXi -lXinerama -lX11 -lrt -ldl -lglad -I../libs/glm-0.9.7.1/

GLM_PATH =  -I../libs/glm-0.9.7.1/ 

# things in resource/
EDITOR_OBJS = editor/Control.o
EDITOR_HEADERS = editor/Control.h

RESOURCE_OBJS = resource/Mesh.o resource/GLMesh.o resource/ShaderProgram.o
RESOURCE_HEADERS = resource/Mesh.h resource/GLMesh.h resource/ShaderProgram.h

GEOMETRY_OBJS = geometry/Geometry.o geometry/Cube.o
GEOMETRY_HEADERS = geometry/Geometry.h geometry/Cube.h

SCENE_OBJS = scene/SceneNode.o scene/Drawable.o
SCENE_HEADERS = scene/SceneNode.h scene/Drawable.h

# build and run it
all: componenets test_main
	./test_main

test_main: test_main.cpp componenets
	g++ $(CPPFLAGS) $< -pthread -o $@ $(RESOURCE_OBJS) \
		$(GEOMETRY_OBJS) $(EDITOR_OBJS) $(SCENE_OBJS) \
		$(COMPILE_FLAG)

# all ingredients
componenets: $(EDITOR_OBJS) $(RESOURCE_OBJS) \
	$(GEOMETRY_OBJS) $(SCENE_OBJS)

# resources
resource/%.o: resource/%.cpp resource/%.h $(RESOURCE_HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)


# geometry
geometry/%.o: geometry/%.cpp geometry/%.h $(GEOMETRY_HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)

# editor
editor/%.o: editor/%.cpp editor/%.h $(EDITOR_HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)

# editor
scene/%.o: scene/%.cpp scene/%.h $(SCENE_HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)


clean:
	rm -rf editor/*.o geometry/*.o resource/*.o scene/*.o test_main
