#include "Shader.h"
#include <GL/glew.h>
#include <vector>
#include "utils/FileUtils.h"
#include "math/math.h"

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

int Shader::GetUniformLocation(const String& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_ShaderID, name.c_str());
	ASSERT(location != -1);
	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetUniform1i(const String & name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const String& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform2f(const String& name, const vec2& vec)
{
	glUniform2f(GetUniformLocation(name), vec.x, vec.y);
}

void Shader::SetUniform3f(const String& name, const vec3& vec)
{
	glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const String& name, const vec4& vec)
{
	SetUniform4f(name, vec.x, vec.y, vec.z, vec.w);
}


void Shader::SetUniform4f(const String& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformMat4(const String& name, const mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, matrix.elements);
}