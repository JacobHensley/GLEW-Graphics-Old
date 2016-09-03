#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils/FileUtils.h"
#include "graphics/Shader.h"
#include "graphics\IndexBuffer.h"
#include "graphics\Buffer.h"
#include "graphics\VertexArray.h"

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

	VertexArray vertexArray;
	IndexBuffer ibo = IndexBuffer(indices, 6);
	vertexArray.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);

	vertexArray.bind();
	ibo.bind();

	Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
	shader.Bind();

	int location = glGetUniformLocation(shader.GetID(), "u_Color");
	ASSERT(location != -1);
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f); 

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		ibo.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}