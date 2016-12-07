#pragma once

#include <memory>
//uses glm for mat4's as my mat4's are not 100% complete
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Component.h"
#include "Vec3.h"
#include "Vec2.h"

namespace Maths
{

	class TransformComponent : public Core::Component
	{

	public:
		virtual ~TransformComponent();

		Vec3 getPos() { return pos; }
		Vec3 getRotation() { return rotation; }
		Vec3 getScale() { return scale; }
		void setPos(Vec3 pos) { this->pos = pos; }
		void setRotation(Vec3 rotation) { this->rotation = rotation; }
		void setScale(Vec3 scale) { this->scale = scale; }

		void rotate(Vec3 angles);
		void translate(Vec3 translation);
		void lookAt(Vec3 worldPosition);
		void rotateAround(Vec3 center, Vec3 axis, float amount);

	private:
		Vec3 pos;
		Vec3 rotation;
		Vec3 scale;

		virtual void onAwake();
		virtual void onDestroy();
	};

}