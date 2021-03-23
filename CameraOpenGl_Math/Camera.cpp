#include "Camera.h"

float Radians(float number) {
	return number * static_cast<float>(0.01745329251994329576923690768489);
}

Camera::Camera()
{
	// ïîçèöèÿ êàìåðû
	// x - êàìåðà ñäâèãàåòñÿ âïðàâî, êàðòèíêà âëåâî y - êàìåðà ïîäíèìàåòñÿ ââåðõ, êàðòèíêà âíèç, z - ÷åì áîëüøå, òåì äàëüøå êàìåðà
	positionCamera = Vec3(0.0f, 0.0f, 3.0f);
	// ïîçèöèÿ öåëè
	frontCamera = Vec3(0.0f, 0.0f, -1.0f);
	// âåêòîð ââåðõ
	upCamera = Vec3(0.0f, 1.0f, 0.0f);
	// ââåðõ - âíèç
	pitch = 0.0f;
	// ïîâîðîò âïðàâî - âëåâî
	yaw = -90.0f;
}

Mat4 Camera::GetViewMatrix()
{
	Mat4 result;
	return result.LookAt(positionCamera, positionCamera + frontCamera, upCamera);
}

Mat4 Camera::GetProjectionMatrix()
{
	// ïîëå îáçîðà, ñîîòíîøåíèå ñòîðîí, áëèæíÿÿ è äàëüíÿÿ ïëîñêîñòü óñå÷åíèÿ ïèðàìèäû
	Mat4 result;
	return result.Perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::ReadInput()
{
	// âïåðåä, ïðèáëèæåíèå ê öåëè
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		positionCamera += frontCamera * speed;
	}
	// âëåâî, âåêòîðíîå ïðîèçâåäåíèå äàåò ïåðïåíäèêóëÿð
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera -= crossResult.Normalize() * speed;
	}
	// âïðàâî
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Vec3 crossResult(frontCamera.CrossProduct(upCamera));
		positionCamera += crossResult.Normalize() * speed;
	}
	// âíèç, îòäàëåíèå îò öåëè
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		positionCamera -= frontCamera * speed;
	}
}

void Camera::MouseInput(sf::Window& window)
{
	//òîðìîçà
	//sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
	//sf::Mouse::setPosition(center, window);

	if (mouseMove) {
		mouseMove = false;
		xPos = sf::Mouse::getPosition(window).x;
		yPos = sf::Mouse::getPosition(window).y;
	}

	// ñìåùåíèå ñ ïðîøëîãî ïîëîæåíèÿ ìûøè
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
