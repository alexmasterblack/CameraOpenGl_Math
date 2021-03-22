#pragma once

int WIDTH = 800, HEIGHT = 600;

class Camera {
public:
	Camera() {
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
	Mat4 GetViewMatrix() {
		Mat4 result;
		return result.LookAt(positionCamera, positionCamera + frontCamera, upCamera);
	}

	Mat4 GetProjectionMatrix() {
		// ���� ������, ����������� ������, ������� � ������� ��������� �������� ��������
		Mat4 result;
		return result.Perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	}

	void ReadInput() {
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

	void MouseInput(sf::Window& window) {
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
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		frontCamera = front.Normalize();
	}

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
	float xPos = WIDTH / 2.0f;
	float yPos = HEIGHT / 2.0f;
	// �������� ����� � ������ ��� 
	bool mouseMove = true;
};