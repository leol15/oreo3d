#ifndef TRACER_H_
#define TRACER_H_

#include <glm/glm.hpp>
// #include <glm/ext.hpp>

#include <string>
#include <vector>


struct Light {
	glm::vec3 pos;
	glm::vec3 color;
	// TODO could put >> << def here
};

struct Sphere {
	glm::vec3 pos;
	float radius;
};


class Tracer {
public:
	Tracer();
	Tracer(const std::string path);
	virtual ~Tracer();

	void trace(std::vector<glm::vec3>& grid, int w, int h,
		const glm::vec3 eye,
		const glm::vec3 top_left,
		const glm::vec3 top_side,
		const glm::vec3 left_side) const;

	void saveToFile(const std::string path) const;

private:
	std::vector<Light> lights;
};



#endif	// TRACER_H_