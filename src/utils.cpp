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
	pos.x = pos.x - v.pos.x;
	pos.y = pos.y - v.pos.y;
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

float Vec2d::distance(Vec2d v) {
	Vec2d vdist = copy();
	vdist.sub(v);
	return vdist.mag();
}

Vec2d Vec2d::perp() {
	return Vec2d(-pos.y, pos.x);
}

void Vec2d::rotate(Vec2d base, float n) {
	Vec2d direction = copy();
	direction.sub(base);
	float x = direction.pos.x * cosf(n) - direction.pos.y * sinf(n);
	float y = direction.pos.x * sinf(n) + direction.pos.y * cosf(n);
	pos.x = x + base.pos.x;
	pos.y = y + base.pos.y;
}

Vec2d addVec(Vec2d v1, Vec2d v2) {
	return Vec2d(v1.pos.x + v2.pos.x, v1.pos.y + v2.pos.y);
}

Vec2d subVec(Vec2d v1, Vec2d v2) {
	return Vec2d(v1.pos.x - v2.pos.x, v1.pos.y - v2.pos.y);
}

Vec2d multVec(Vec2d v, float n) {
	Vec2d vmult = v.copy();
	vmult.mult(n);
	return vmult;
}

Vec2d intersect(Vec2d start_a, Vec2d end_a, Vec2d start_b, Vec2d end_b) {
	/*
	line_a = end_a - start_a
    line_b = end_b - start_b
    cross1 = cross2d(line_a, line_b)
    cross2 = cross2d(line_b, line_a)
    if cross1 != 0:
        s = cross2d(start_b - start_a, line_b) / cross1
        u = cross2d(start_a - start_b, line_a) / cross2
        if s > 0 and s < 1 and u > 0 and u < 1:
            return start_a + line_a * s
        else:
            return None
	*/
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