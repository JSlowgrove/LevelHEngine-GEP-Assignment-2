#include "TransformComponent.h"

//uses glm for mat4's as my mat4's are not 100% complete
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Maths/Vec2.h"

TransformComponent::~TransformComponent()
{
}

void TransformComponent::onAwake()
{
	scaleSize = Vec3(1, 1, 1);
	id = "transform";
}

void TransformComponent::onDestroy()
{
}

void TransformComponent::rotate(Vec3 angles)
{
	rotation.x += angles.x;
	rotation.y += angles.y;
	rotation.z += angles.z;
}

void TransformComponent::translate(Vec3 translation)
{
	pos.x += translation.x;
	pos.y += translation.y;
	pos.z += translation.z;
}

void TransformComponent::lookAt(Vec3 worldPosition)
{
	Vec2 diff2 = Vec2(pos.x, pos.z) - Vec2(worldPosition.x, worldPosition.z);

	float angle = atan2(diff2.x, diff2.y) * 180 / 3.14159265359f;
	rotation.y = angle - 180.0f;
}

void TransformComponent::rotateAround(Vec3 center, Vec3 axis, float amount)
{
	//translate with an identity mat4
	glm::mat4 mPos = glm::translate(glm::mat4(1.0f), glm::vec3(center.x, center.y, center.z));

	//rotate
	glm::vec3 axisRotation = glm::vec3(axis.x, axis.y, axis.z) * amount;

	glm::mat4 rot = glm::rotate(mPos, axisRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rot = glm::rotate(mPos, axisRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rot = glm::rotate(mPos, axisRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//create an identity mat4
	glm::mat4 curr = glm::mat4(1.0f);
	curr = curr * mPos;
	curr = curr * rot;
	curr = curr * glm::inverse(mPos);

	mPos = curr * mPos;
}

Mat4 TransformComponent::getTransformMat4()
{
	Mat4 m;
	m.setAsIdentityMatrix();
	m.translate(m, pos);
	m.rotate(m, rotation);
	m.scale(m, scaleSize);
	return m;
}