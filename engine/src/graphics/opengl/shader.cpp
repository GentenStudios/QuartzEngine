#include "engine/graphics/opengl/shader.hpp"

using namespace phoenix::graphics::opengl;

Shader::Shader()
{}

Shader::~Shader()
{
	glDeleteProgram(m_shaderID);
}

void Shader::compileShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	shaderErrorCheck(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	shaderErrorCheck(fragmentShader);

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShader);
	glAttachShader(m_shaderID, fragmentShader);
	glLinkProgram(m_shaderID);
	shaderErrorCheck(m_shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(m_shaderID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, Vector2& data) const
{
	glUniform2fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, &data.x);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_shaderID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, Vector3& data) const
{
	glUniform3fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, &data.x);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderID, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, Matrix4x4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, &mat.elements[0]);
}

unsigned int Shader::getShaderID() const
{
	return m_shaderID;
}

void Shader::setShaderID(unsigned int shaderID)
{
	m_shaderID = shaderID;
}

void Shader::shaderErrorCheck(GLuint shader)
{
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << infoLog << std::endl;
	}
}

