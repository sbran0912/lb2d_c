#include "raylib.h"

#ifndef UTILS_H
#define UTILS_H

struct Matrix3x3 {
	float index[3][3];
};

struct Matrix3x1 {
	float index[3];
};

struct Vec2d {
	Vector2 pos;

	Vec2d(float x, float y);
	Vec2d copy();
	void set(float x, float y);
	void mult(float n);
	void div(float n);
	void add(Vec2d v);
	void sub(Vec2d v);
	float dot(Vec2d v);
	float cross(Vec2d v);
	void normalize();
	void limit(float max);
	float magsq();
	float mag();
	void setmag(float magnitude);
	float distance();
};

Matrix3x1 vecToMatrix3x1(Vec2d point);
Vec2d matrix3x1ToVec(Matrix3x1 matrix);
Matrix3x1 matmul3x1(Matrix3x3 a, Matrix3x1 b);
Matrix3x1 rotate(Vec2d point, Vec2d center, float angel);

#endif