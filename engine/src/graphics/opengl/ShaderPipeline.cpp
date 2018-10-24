#include "engine/graphics/opengl/ShaderPipeline.hpp"

using namespace phx::gfx::gl;

ShaderPipeline::ShaderPipeline()
{}

ShaderPipeline::~ShaderPipeline()
{
	glDeleteProgram(m_shaderProgram);
}

void ShaderPipeline::addStage(ShaderType stage, const char* shaderSource)
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

void ShaderPipeline::build()
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

	m_shaders.clear();
}

void ShaderPipeline::use() const
{
	glUseProgram(m_shaderProgram);
}

void ShaderPipeline::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), static_cast<int>(value));
}

void ShaderPipeline::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderPipeline::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void ShaderPipeline::setVec2(const std::string& name, phx::Vector2& data) const
{
	glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x);
}

void ShaderPipeline::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y);
}

void ShaderPipeline::setVec3(const std::string& name, phx::Vector3& data) const
{
	glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x);
}

void ShaderPipeline::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z);
}

void ShaderPipeline::setMat4(const std::string& name, phx::Matrix4x4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat.elements[0]);
}

unsigned int ShaderPipeline::getShaderProgram() const
{
	return m_shaderProgram;
}