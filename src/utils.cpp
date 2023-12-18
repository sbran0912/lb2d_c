#include <cmath>
#include "raylib.h"
#include "utils.h"

Vec2d::Vec2d(float x, float y) 
	: pos{x, y} {}

Vec2d Vec2d::copy() {
	return Vec2d(pos.x, pos.y);
}
void Vec2d::set(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Vec2d::mult(float n) {
	pos.x = pos.x * n;
	pos.y = pos.y * n;
}

void Vec2d::div(float n) {
	pos.x = pos.x / n;
	pos.y = pos.y / n;
}

void Vec2d::add(Vec2d v) {
	pos.x = pos.x + v.pos.x;
	pos.y = pos.y + v.pos.y;
}

void Vec2d::sub(Vec2d v) {
	pos.x = pos.x + v.pos.x;
	pos.y = pos.y + v.pos.y;
}

float Vec2d::dot(Vec2d v) {
	return pos.x * v.pos.x + pos.y * v.pos.y;
}

float Vec2d::cross(Vec2d v) {
	return pos.x * v.pos.y - pos.y * v.pos.x;
}

float Vec2d::magsq() {
	return pos.x * pos.y + pos.y * pos.y;
}

float Vec2d::mag() {
	return sqrt(magsq());
}

void Vec2d::normalize() {
	float len = mag();
	if (len > 0) div(len);
}

void Vec2d::setmag(float magnitude) {
	normalize();
	mult(magnitude);
}

void Vec2d::limit(float max) {
	if (mag() > max) {
		setmag(max);
	}
}


Matrix3x1 vecToMatrix3x1(Vec2d point) {

	return { {point.pos.x, point.pos.y, 1} };
}

Vec2d matrix3x1ToVec(Matrix3x1 matrix) {

	//return { matrix.index[0], matrix.index[1] };
	return Vec2d(matrix.index[0], matrix.index[1]);
}

Matrix3x1 matmul3x1(Matrix3x3 a, Matrix3x1 b) {
	Matrix3x1 result = { {0, 0, 0} };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.index[i] += a.index[i][j] * b.index[j];
		}
	}
	return result;
}

Matrix3x1 rotate(Vec2d point, Vec2d center, float angel) {

	Matrix3x1 matrix_point = vecToMatrix3x1(point);
	Matrix3x1 matrix_center = vecToMatrix3x1(center);

	Matrix3x3 m_rotate = {{
		{cosf(angel), -sinf(angel), 0}, 
		{sinf(angel), cosf(angel), 0}, 
		{0, 0, 1}
		}};

	Matrix3x3 m_transform_center = {{
		{1, 0, -matrix_center.index[0]},
        {0, 1, -matrix_center.index[1]},
    	{0, 0, 1}
	}};

	Matrix3x3 m_transform_center_back = {{
		{1, 0, matrix_center.index[0]},
        {0, 1, matrix_center.index[1]},
    	{0, 0, 1}
	}}; 
		
	Matrix3x1 matrix_p_transformed = matmul3x1(m_transform_center, matrix_point);
    Matrix3x1 matrix_p_transformed_rotated = matmul3x1(m_rotate, matrix_p_transformed);

	return matmul3x1(m_transform_center_back, matrix_p_transformed_rotated);
}