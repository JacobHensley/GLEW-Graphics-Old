#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils/FileUtils.h"
#include "graphics/Shader.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "math/math.h"


int main() {
	if (!glfwInit())
		return 1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
	if (!window)
		return 2;

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		return 3;
	}

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	float vertices[] =
	{
		-0.5f, -0.5f,  0.0f,
		-0.5,   0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};
	
	uint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mat4 matrix = mat4::Translate(vec3(0.1f, -0.25f, 0.0f));

	VertexArray vertexArray;
	IndexBuffer ibo = IndexBuffer(indices, 6);
	vertexArray.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

	vertexArray.bind();
	ibo.bind();

	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
	shader.Bind();

	shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetUniformMat4("u_Matrix", matrix);

	float x = -1;
	float y = 1;

	float r = 0.0f, g = 0.0f, b = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetUniformMat4("u_Matrix", mat4::Translate(vec3(x, y, 0.0f)));
		shader.SetUniform4f("u_Color", r, x, y, 1.0f);
		ibo.draw();

		x +=  0.005;
		y += -0.005;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}