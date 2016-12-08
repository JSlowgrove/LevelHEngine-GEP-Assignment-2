#pragma once

#include <memory>
//uses glm for mat4's as my mat4's are not 100% complete
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Maths/Vec3.h"
#include "../Maths/Vec2.h"
#include "Component.h"

class TransformComponent : public Component
{

public:
	virtual ~TransformComponent();

	Vec3 getPos() { return pos; }
	Vec3 getRotation() { return rotation; }
	Vec3 getScale() { return scaleSize; }
	void setPos(Vec3 pos) { this->pos = pos; }
	void setRotation(Vec3 rotation) { this->rotation = rotation; }
	void setScale(Vec3 scaleSize) { this->scaleSize = scaleSize; }

	Mat4 getTransformMat4();

	void rotate(Vec3 angles);
	void translate(Vec3 translation);
	void lookAt(Vec3 worldPosition);
	void rotateAround(Vec3 center, Vec3 axis, float amount);

	virtual void onAwake();
	virtual void onDestroy();

private:
	Vec3 pos;
	Vec3 rotation;
	Vec3 scaleSize;

	
};