#include "Shader.h"
#include <GL/glew.h>
#include <vector>
#include "utils/FileUtils.h"

Shader::Shader(const String& vertPath, const String& fragPath) 
 : m_VertPath(vertPath), m_FragPath(fragPath)
{	
	m_ShaderID = Load();
	ASSERT(m_ShaderID);
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

uint Shader::Load()
{
	uint program = glCreateProgram();
	uint vertex = glCreateShader(GL_VERTEX_SHADER);
	uint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	String vertexSrc = ReadFile(m_VertPath);
	String fragmentSrc = ReadFile(m_FragPath);
	const char* vs = vertexSrc.c_str();

	glShaderSource(vertex, 1, &vs, NULL);
	glCompileShader(vertex);

	int compileResult;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		int length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << &error[0] << std::endl;
		std::cout << "Vertex Error" << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	const char* fs = fragmentSrc.c_str();

	glShaderSource(fragment, 1, &fs, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		int length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << &error[0] << std::endl;
		std::cout << "Fragment Error" << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}
