#include "Camera.h"

float Radians(float number) {
	return number * static_cast<float>(0.01745329251994329576923690768489);
}

Camera::Camera()
{
	// ������� ������
	// x - ������ ���������� ������, �������� ����� y - ������ ����������� �����, �������� ����, z - ��� ������, ��� ������ ������
	positionCamera = Vec3(0.0f, 0.0f, 3.0f);
	// ������� ����
	frontCamera = Vec3(0.0f, 0.0f, -1.0f);
	// ������ �����
	upCamera = Vec3(0.0f, 1.0f, 0.0f);
	// ����� - ����
	pitch = 0.0f;
	// ������� ������ - �����
	yaw = -90.0f;
}

Mat4 Camera::GetViewMatrix()
{
	Mat4 result;
	return result.LookAt(positionCamera, positionCamera + frontCamera, upCamera);
}

Mat4 Camera::GetProjectionMatrix()
{
	// ���� ������, ����������� ������, ������� � ������� ��������� �������� ��������
	Mat4 result;
	return result.Perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);
}

void Camera::ReadInput()
{
	// ������, ����������� � ����
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		positionCamera += frontCamera * speed;
	}
	// �����, ��������� ������������ ���� �������������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera -= crossResult.Normalize() * speed;
	}
	// ������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera += crossResult.Normalize() * speed;
	}
	// ����, ��������� �� ����
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		positionCamera -= frontCamera * speed;
	}
}

void Camera::MouseInput(sf::Window& window)
{
	//�������
	//sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
	//sf::Mouse::setPosition(center, window);

	if (mouseMove) {
		mouseMove = false;
		xPos = sf::Mouse::getPosition(window).x;
		yPos = sf::Mouse::getPosition(window).y;
	}

	// �������� � �������� ��������� ����
	float xOffset = sf::Mouse::getPosition(window).x - xPos;
	float yOffset = yPos - sf::Mouse::getPosition(window).y;
	xPos = sf::Mouse::getPosition(window).x;
	yPos = sf::Mouse::getPosition(window).y;

	yaw += (xOffset * speed);
	pitch += (yOffset * speed);

	Vec3 front;
	front.x = cos(Radians(yaw)) * cos(Radians(pitch));
	front.y = sin(Radians(pitch));
	front.z = sin(Radians(yaw)) * cos(Radians(pitch));
	frontCamera = front.Normalize();
}