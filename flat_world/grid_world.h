#ifndef GRID_WORLD_H_
#define GRID_WORLD_H_

#include <glm/glm.hpp>
#include <vector>
#include <map>


enum CellType {
	SAND,
	WATER,
	STONE,
	EMPTY
};

struct Cell {
	CellType type;
};

class GridWorld {
public:
	GridWorld(int width, int height);
	~GridWorld();
	
	// interaction
	void addCell(int row, int column, int size);

	void setCellType(CellType newType) { current_type_ = newType; }

	// update
	void update();
	void reset();

	// show w/ gl shader program
	void draw(GLuint program_id);

private:
	// the grid to collect the structs
	int width_, height_;
	Cell ** grid_;
	// grid_[i][j] == nullptr
	CellType current_type_;
	// for ogl 2D drawing
	GLuint vao_;
	GLuint position_vbo_;
	GLuint indices_vbo_;
	// actual data, positon data
	std::vector<glm::vec2> grid_vecticies_;
	// element type : (vector, valid size)
	std::map<CellType, std::pair<std::vector<unsigned int>, int>> type_to_idx_arr_map_;

	void collectGridToVectexArr();

	// helpers
	bool cellEmpty(int row, int col);
};


#endif