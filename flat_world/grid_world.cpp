

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstring>

#include "grid_world.h"

#include <iostream>
#include <algorithm>

static std::vector<std::pair<int, int>> ORDERS;

GridWorld::GridWorld(int width, int height)
		: width_(width), height_(height),
		grid_(nullptr), current_type_(CellType::SAND),
		vao_(0), position_vbo_(0), indices_vbo_(0) {
	grid_ = new Cell*[width_];

	// allocate grid
	for (int i = 0; i < width_; i++) {
		grid_[i] = new Cell[height_];
		// memset(grid_[i], CellType::EMPTY, sizeof(CellType) * width);
		for (int j = 0; j < height_; j++) {
			grid_[i][j].type = CellType::EMPTY;
			ORDERS.push_back(std::make_pair(i, j));
		}
	}

	std::random_shuffle(ORDERS.begin(), ORDERS.end());

	// set up vertex buffer
	type_to_idx_arr_map_[CellType::SAND] = std::make_pair(std::vector<unsigned int>(), 0);
	type_to_idx_arr_map_[CellType::STONE] = std::make_pair(std::vector<unsigned int>(), 0);
	type_to_idx_arr_map_[CellType::WATER] = std::make_pair(std::vector<unsigned int>(), 0);

	type_to_idx_arr_map_[CellType::SAND].first.reserve(6 * (width_ + 1) * (height_ + 1));
	type_to_idx_arr_map_[CellType::STONE].first.reserve(6 * (width_ + 1) * (height_ + 1));
	type_to_idx_arr_map_[CellType::WATER].first.reserve(6 * (width_ + 1) * (height_ + 1));

	// 0~1
	// triangle locations, width + 1, height + 1
	for (int i = 0; i < width_ + 1; i++) {
		for (int j = 0; j < height_ + 1; j++) {
			grid_vecticies_.push_back({(float) i / width_, (float) j / height_});
		}
	}

	// create VAO
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// the default arrays
	glGenBuffers(1, &position_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * grid_vecticies_.size(), grid_vecticies_.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glGenBuffers(1, &indices_vbo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_);

}

GridWorld::~GridWorld() {
	for (int i = 0; i < width_; i++) {
		delete[] grid_[i];
	}
	delete[] grid_;

	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &position_vbo_);
	glDeleteBuffers(1, &indices_vbo_);
}


void GridWorld::addCell(int row, int column, int size) {
	for (int i = -size / 2; i <= size / 2; i++) {
		for (int j = -size / 2; j <= size / 2; j++) {
			if (row + i < 0 || width_ <= row + i || column + j < 0 || height_ <= column + j) continue;
			grid_[row + i][column + j].type = current_type_;
		}
	}
}

bool GridWorld::cellEmpty(int row, int col) {
	if (row < 0 || width_ <= row || col < 0 || height_ <= col) return false;
	return grid_[row][col].type == CellType::EMPTY;
}

// most important!!! simulate
void GridWorld::update() {
	std::random_shuffle(ORDERS.begin(), ORDERS.end());
	// for (int row = width_ - 1; row >= 0; row--) {
		// for (int col = height_; col >= 0; col--) {
		for (auto [row, col] : ORDERS) {
			switch(grid_[row][col].type) {
				case CellType::SAND:
					if (cellEmpty(row, col + 1)) {
						grid_[row][col].type = CellType::EMPTY;
						grid_[row][col + 1].type = CellType::SAND;
					}
					break;
				case CellType::WATER:
					// TODO: COULD MOVE LEFT/RIGHT BEFORE DOWN
					{
					bool topEmpty = cellEmpty(row, col - 1);
					bool botEmpty = cellEmpty(row, col + 1);
					bool leftEmpty = cellEmpty(row - 1, col);
					bool rightEmpty = cellEmpty(row + 1, col);
					int randVal = rand() % 10;
					if (botEmpty) {
						grid_[row][col].type = CellType::EMPTY;
						grid_[row][col + 1].type = CellType::WATER;
					} else if (leftEmpty && rightEmpty) {
						// move to sides
						// 50 50 split
						if (randVal < 5) {
							// move right
							grid_[row][col].type = CellType::EMPTY;
							grid_[row + 1][col].type = CellType::WATER;
						} else {
							grid_[row][col].type = CellType::EMPTY;
							grid_[row - 1][col].type = CellType::WATER;
						}
					} else if (leftEmpty) {
						grid_[row][col].type = CellType::EMPTY;
						grid_[row - 1][col].type = CellType::WATER;		
					} else if (rightEmpty) {
						grid_[row][col].type = CellType::EMPTY;
						grid_[row + 1][col].type = CellType::WATER;
					} else if (topEmpty && randVal < 5) {
						grid_[row][col].type = CellType::EMPTY;
						grid_[row][col - 1].type = CellType::WATER;
					}
					}
					break;
				case CellType::STONE:
					break;
				default:
					break;
			}
		}
		// }
	// }
	collectGridToVectexArr();
}

void GridWorld::reset() {
	for (int i = 0; i < width_; i++) {
		for (int j = 0; j < height_; j++) {
			grid_[i][j].type = CellType::EMPTY;
		}
	}
}


// draw
void GridWorld::draw(GLuint program_id) {
	
	glUseProgram(program_id);
	GLuint type_loc = glGetUniformLocation(program_id, "CELL_TYPE");
	glBindVertexArray(vao_);
	// draw each element type
	for (auto & [type, indices_size] : type_to_idx_arr_map_) {
		auto & indices = indices_size.first;
		auto & size = indices_size.second;
		if (size == 0) continue;
		glUniform1i(type_loc, type);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, indices.data(), GL_STATIC_DRAW);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

// fill cell_locations_ based on type_to_idx_arr_map_
void GridWorld::collectGridToVectexArr() {
	// clear indices
	for (auto & [type, indices_size] : type_to_idx_arr_map_) {
		indices_size.second = 0;
	}

	// fill indices
	for (int row = 0; row < width_; row++) {
		for (int col = 0; col < height_; col++) {
			if (grid_[row][col].type == CellType::EMPTY) continue;
			// add 6 indices to type_to_idx_arr_map_
			// A B
			// C D
			unsigned int A = row * (width_ + 1) + col;
			unsigned int B = A + 1;
			unsigned int C = A + (width_ + 1);
			unsigned int D = C + 1;

			auto & vec_size = type_to_idx_arr_map_[grid_[row][col].type];
			vec_size.first[vec_size.second++] = A;
			vec_size.first[vec_size.second++] = B;
			vec_size.first[vec_size.second++] = C;

			vec_size.first[vec_size.second++] = C;
			vec_size.first[vec_size.second++] = B;
			vec_size.first[vec_size.second++] = A;

			vec_size.first[vec_size.second++] = C;
			vec_size.first[vec_size.second++] = B;
			vec_size.first[vec_size.second++] = D;
		}
	}
}





