

#include <glm/glm.hpp>
// #include <glm/ext.hpp>

#include <string>
#include <fstream>
#include <vector>

#include "Tracer.h"

// reading 
std::ostream & operator<<(std::ostream& out, glm::vec3 vec) {
	out << vec.x << " " << vec.y << " " << vec.z;
	return out;
}

std::istream & operator>>(std::istream& in, glm::vec3 vec) {
	in >> vec.x >> vec.y >> vec.z;
	return in;
}

Tracer::Tracer() {
	Light l;
	lights.push_back(l);
}

void Tracer::saveToFile(const std::string path) const {
    std::ofstream out(path);
    // iterate through objects
    for (const Light & l : lights) {
    	out << "Light ";
    	out << "pos " << l.pos << " ";
    	out << "color " << l.color;
    	out << std::endl;
    }
    out.close();
}

Tracer::Tracer(const std::string path) {
	// read lights
	std::ifstream in(path);
	if (!in.is_open()) return;
	std::string type;
	while (in) {
		in >> type;
		if (type == "Light") {
			Light l;
			in >> type;
			in >> l.pos;
			in >> type;
			in >> l.color;
			lights.push_back(l);
		}
	}
}

Tracer::~Tracer() { }
