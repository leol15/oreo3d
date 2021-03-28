#ifndef SCENE_NODE_
#define SCENE_NODE_

#include <glm/glm.hpp>

#include <vector>

#include "Transformable.h"
#include "Drawable.h"

// the tree like sceen graph
class SceneNode : public Transformable {
public:
	SceneNode() : Transformable(),
		children_(), drawable_(nullptr) { };

	void render(const glm::mat4& proj_matrix, 
		const glm::mat4& view_matrix,
		glm::mat4 model_matrix = glm::mat4(1));

	void setDrawable(Drawable *d) { drawable_ = d; }

	// add child node, takes ownership too
	void addSceneNode(SceneNode * node) {
		children_.push_back(node);
	}

	virtual ~SceneNode();
private:
	std::vector<SceneNode *> children_;
	Drawable * drawable_;

};




#endif  // SCENE_NODE_