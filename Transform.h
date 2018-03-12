// (c) Marco Gilardi, 2017
#pragma once
#include "glm\glm.hpp"
#include"glm\gtc\matrix_access.hpp"
using namespace glm;

class Transform
{
private:
	mat3 transformMatrix;
	
public:
	Transform();
	virtual ~Transform() {}

	void Translate(vec2& translation);
	void Scale(vec2& scaling);
	void Rotate(float angle);
	//void RotateX(float angle);
	//void RotateY(float angle);

	vec2 getPosition() const;
	vec2 getScale() const;
	vec2 getOrientation() const;
	vec2 getUpDir() const;
	vec2 getLeftDir() const;
	//vec2 getFrontDir() const;

	mat3 localToWorldMatrix();
	mat3 worldToLocalMatrix();
};