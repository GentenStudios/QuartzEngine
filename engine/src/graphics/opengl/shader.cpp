#include "engine/graphics/opengl/shader.hpp"

using namespace phoenix::graphics::opengl;
using namespace phoenix;

ShaderManager::ShaderManager()
{}

ShaderManager::~ShaderManager()
{
	glDeleteProgram(m_shaderProgram);
}

void ShaderManager::addStage(ShaderStage stage, const char* shaderSource)
{
	unsigned int shader;

	shader = glCreateShader(static_cast<GLenum>(stage));
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		ERROR(std::string("ERROR::SHADER::COMPILATION - ").append(infoLog));
	}

	m_shaders.push_back(shader);

}

void ShaderManager::build()
{
	m_shaderProgram = glCreateProgram();

	for (unsigned int shaderID : m_shaders)
	{
		glAttachShader(m_shaderProgram, shaderID);
	}

	glLinkProgram(m_shaderProgram);

	for (unsigned int shader : m_shaders)
	{
		glDetachShader(m_shaderProgram, shader);
		glDeleteShader(shader);
	}
}

void ShaderManager::use() const
{
	glUseProgram(m_shaderProgram);
}

void ShaderManager::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), static_cast<int>(value));
}

void ShaderManager::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderManager::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderManager::setVec2(const std::string& name, Vector2& data) const
{
	glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x);
}

void ShaderManager::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y);
}

void ShaderManager::setVec3(const std::string& name, Vector3& data) const
{
	glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x);
}

void ShaderManager::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z);
}

void ShaderManager::setMat4(const std::string& name, Matrix4x4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat.elements[0]);
}

unsigned int ShaderManager::getShaderProgram() const
{
	return m_shaderProgram;
}

