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
	// позиция камеры
	Vec3 positionCamera;
	Vec3 frontCamera;
	Vec3 upCamera;
	// скорость камеры
	float speed = 0.05f;
	// углы эйлера
	float yaw;
	float pitch;
	// координаты мыши
	float xPos = 800 / 2.0f;
	float yPos = 600 / 2.0f;
	// движение мышью в первый раз 
	bool mouseMove = true;
};