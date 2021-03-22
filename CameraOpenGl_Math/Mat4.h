#pragma once
#include <vector>
#include <assert.h>
#include <cmath>

class Mat4 {
public:
	Mat4();
	Mat4(float);
	Mat4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	Mat4(const Vec4&, const Vec4&, const Vec4&, const Vec4&);
	Mat4(const Mat4&);
	Mat4 operator+(const Mat4&) const;
	Mat4& operator+=(const Mat4&);
	Mat4 operator-(const Mat4&) const;
	Mat4& operator-=(const Mat4&);
	Mat4 operator*(const Mat4&) const;
	Mat4& operator*=(const Mat4&);
	Mat4 operator*(float) const;
	Mat4& operator*=(float);
	Mat4 operator/(float) const;
	Mat4& operator/=(float);
	Mat4 operator+(float) const;
	Mat4& operator+=(float);
	Mat4 operator-(float) const;
	Mat4& operator-=(float);
	Vec4 operator*(const Vec4&) const;
	Vec4 operator[](int);
	Mat4 GetIdentity();
	Mat4 GetTransposed();
	Vec4 GetColumn(int);
	Vec4 GetRow(int);
	Mat4 Rotate(float, Vec3&);
	Mat4 Translate(const Vec3&);
	Mat4 Scale(const Vec3&);
	Mat4 LookAt(Vec3, Vec3, Vec3);
	Mat4 Perspective(float, float, float, float);
	Mat4 Ortho(float, float, float, float);
	friend const bool operator==(const Mat4&, const Mat4&);
	friend const bool operator!=(const Mat4&, const Mat4&);

	std::vector<std::vector<float>> data;
};

