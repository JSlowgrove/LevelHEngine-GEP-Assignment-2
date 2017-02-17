#pragma once

#include "../Maths/Vec3.h"
#include "../Maths/Mat4.h"
#include "Component.h"

/**
@brief A class that handles the transform component.
*/
class TransformComponent : public Component
{

public:
	/**
	@brief A virtual destructor.
	*/
	virtual ~TransformComponent();

	/**
	@brief A function to get the position.
	@returns The position of the component.
	*/
	Vec3 getPos() { return pos; }

	/**
	@brief A function to get the rotation.
	@returns The rotation of the component.
	*/
	Vec3 getRotation() { return rotation; }

	/**
	@brief A function to get the scale.
	@returns The scale of the component.
	*/
	Vec3 getScale() { return scaleSize; }

	/**
	@brief A function to set the position.
	@param inPos The position of the component.
	*/
	void setPos(Vec3 inPos) { pos = inPos; }

	/**
	@brief A function to set the rotation.
	@param inRotation The rotation of the component.
	*/
	void setRotation(Vec3 inRotation) { rotation = inRotation; }

	/**
	@brief A function to set the scale.
	@param inScaleSize The scale of the component.
	*/
	void setScale(Vec3 inScaleSize) { scaleSize = inScaleSize; }

	/**
	@brief A function to get the transform matrix.
	@returns The transform matrix.
	*/
	Mat4 getTransformMat4();

	/**
	@brief A function to rotate the component.
	@param angles The angles of rotation (radians).
	*/
	void rotate(Vec3 angles);

	/**
	@brief A function to translate the component.
	@param translation The amount to translate by.
	*/
	void translate(Vec3 translation);

	/**
	@brief A function to look at a specific world position.
	@param worldPosition The position to look at.
	*/
	void lookAt(Vec3 worldPosition);

	/**
	@brief A function to rotate around a specific world point.
	@param center The position to roate around
	@param axis The axis to roate around.
	@param amount The amount to roate around.
	*/
	void rotateAround(Vec3 center, Vec3 axis, float amount);

	/**
	@brief A virtual function for the componets awake.
	*/
	virtual void onAwake();

	/**
	@brief A virtual function for the componets destroy.
	*/
	virtual void onDestroy();

private:
	///The vector transform variables
	Vec3 pos;
	Vec3 rotation;
	Vec3 scaleSize;

	
};