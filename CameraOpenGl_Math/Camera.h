#pragma once
#include <SFML/Window.hpp>
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

class Camera {
public:
	Camera();
	Mat4 GetViewMatrix();
	Mat4 GetProjectionMatrix();
	void ReadInput();
	void MouseInput(sf::Window&);

private:
	// ������� ������
	Vec3 positionCamera;
	Vec3 frontCamera;
	Vec3 upCamera;
	// �������� ������
	float speed = 0.05f;
	// ���� ������
	float yaw;
	float pitch;
	// ���������� ����
	float xPos = 800 / 2.0f;
	float yPos = 600 / 2.0f;
	// �������� ����� � ������ ��� 
	bool mouseMove = true;
};