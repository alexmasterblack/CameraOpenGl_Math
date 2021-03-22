#pragma once

int WIDTH = 800, HEIGHT = 600;

class Camera {
public:
	Camera() {
		// позиция камеры
		// x - камера сдвигается вправо, картинка влево y - камера поднимается вверх, картинка вниз, z - чем больше, тем дальше камера
		positionCamera = Vec3(0.0f, 0.0f, 3.0f);
		// позиция цели
		frontCamera = Vec3(0.0f, 0.0f, -1.0f);
		// вектор вверх
		upCamera = Vec3(0.0f, 1.0f, 0.0f);
		// вверх - вниз
		pitch = 0.0f;
		// поворот вправо - влево
		yaw = -90.0f;

	}
	Mat4 GetViewMatrix() {
		Mat4 result;
		return result.LookAt(positionCamera, positionCamera + frontCamera, upCamera);
	}

	Mat4 GetProjectionMatrix() {
		// поле обзора, соотношение сторон, ближняя и дальняя плоскость усечения пирамиды
		Mat4 result;
		return result.Perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	}

	void ReadInput() {
		// вперед, приближение к цели
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			positionCamera += frontCamera * speed;
		}
		// влево, векторное произведение дает перпендикуляр
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			Vec3 crossResult(frontCamera.CrossProduct(upCamera));
			positionCamera -= crossResult.Normalize() * speed;
		}
		// вправо
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			Vec3 crossResult(frontCamera.CrossProduct(upCamera));
			positionCamera += crossResult.Normalize() * speed;
		}
		// вниз, отдаление от цели
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			positionCamera -= frontCamera * speed;
		}
	}

	void MouseInput(sf::Window& window) {
		//тормоза
		//sf::Vector2i center(window.getSize().x / 2, window.getSize().y / 2);
		//sf::Mouse::setPosition(center, window);

		if (mouseMove) {
			mouseMove = false;
			xPos = sf::Mouse::getPosition(window).x;
			yPos = sf::Mouse::getPosition(window).y;
		}

		// смещение с прошлого положения мыши
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
	float xPos = WIDTH / 2.0f;
	float yPos = HEIGHT / 2.0f;
	// движение мышью в первый раз 
	bool mouseMove = true;
};