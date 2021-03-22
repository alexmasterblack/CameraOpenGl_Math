#pragma once

class Shader {
public:
	Shader(std::string vertexPath, std::string fragmentPath) {
		shaderProgram = LoadShaders(vertexPath, fragmentPath);
	}
	void Use() {
		glUseProgram(shaderProgram);
	}
	void SetMat4(std::string id, const Mat4& data) {
		glm::mat4 matrix = TrueView(data);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, id.c_str()), 1, GL_FALSE, &matrix[0][0]);
	}

private:
	glm::mat4 TrueView(const Mat4& data) {
		return glm::mat4(
			data.data[0][0], data.data[0][1], data.data[0][2], data.data[0][3],
			data.data[1][0], data.data[1][1], data.data[1][2], data.data[1][3],
			data.data[2][0], data.data[2][1], data.data[2][2], data.data[2][3],
			data.data[3][0], data.data[3][1], data.data[3][2], data.data[3][3]);
	}

	unsigned int shaderProgram;
};