
CPP=g++
CPPFLAGS=-Wall -g

COMPILE_FLAG = -lglfw -lGLEW -lGLU -lGL -lXrandr -lXi \
	-lXinerama -lX11 -lrt -ldl -lglad -I../libs/glm-0.9.7.1/

GLM_PATH =  -I../libs/glm-0.9.7.1/ 

# things in resource/
EDITOR_OBJS = editor/Control.o

RESOURCE_OBJS = resource/Mesh.o resource/GLMesh.o resource/ShaderProgram.o

GEOMETRY_OBJS = geometry/Geometry.o geometry/Cube.o

SCENE_OBJS = scene/SceneNode.o scene/Drawable.o

# build and run it
all: componenets test_main
	./test_main

test_main: test_main.cpp
	g++ $(CPPFLAGS) $< -pthread -o $@ $(RESOURCE_OBJS) \
		$(GEOMETRY_OBJS) $(EDITOR_OBJS) $(SCENE_OBJS) \
		$(COMPILE_FLAG)

# all ingredients
componenets: $(RESOURCE_OBJS) $(GEOMETRY_OBJS)\
	$(EDITOR_OBJS) $(SCENE_OBJS)

# resources
resource/%.o: resource/%.cpp resource/%.h
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)


# geometry
geometry/%.o: geometry/%.cpp geometry/%.h
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)

# editor
editor/%.o: editor/%.cpp editor/%.h
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)

# editor
scene/%.o: scene/%.cpp scene/%.h
	$(CPP) $(CPPFLAGS) -c $< -o $@ $(GLM_PATH)




