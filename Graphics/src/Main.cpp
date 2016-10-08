#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils/FileUtils.h"
#include "graphics/Shader.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "math/math.h"
#include "graphics/stb_image.h"
#include "graphics/Texture.h"
#include "graphics/Window.h"

void OnWindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	// update Orthographic mat4
}

int main() {

	Window window = Window("Test", 1280, 720);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f
	};

	uint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mat4 matrix = mat4::Translate(vec3(0.0f, 0.0f, 0.0f));

	mat4 ortho = mat4::Orthographic(16, -16, -9, 9, -1, 1000.0f);
	mat4 prespective = mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

	VertexArray vertexArray;
	IndexBuffer ibo = IndexBuffer(indices, 6);
	vertexArray.addBuffer(new Buffer(vertices, 4 * 5, 3), 0);

	vertexArray.bind();
	ibo.bind();

	Texture text = Texture("res/jungle.png");

	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
	shader.Bind();

	shader.SetUniform1i("u_Texture", 0);

	shader.SetUniformMat4("u_ProjMatrix", prespective);
	shader.SetUniformMat4("u_ModelMatrix", matrix);

	float z = 0.0f;

	while (!window.closed()) {
		window.clear();

		z -= 0.01f;
		matrix = mat4::Translate(vec3(0.0f, 0.0f, z));
		shader.SetUniformMat4("u_ModelMatrix", matrix);
		ibo.draw();

		window.update();
	}

	window.~Window();
	return 0;
}