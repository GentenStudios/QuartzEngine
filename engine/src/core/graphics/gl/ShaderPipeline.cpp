#include <engine/core/graphics/gl/ShaderPipeline.hpp>

using namespace phx::gfx::gl;

ShaderPipeline::ShaderPipeline()
{}

ShaderPipeline::~ShaderPipeline()
{
	GLCheck(glDeleteProgram(m_shaderProgram));
}

void ShaderPipeline::addStage(ShaderType stage, const char* shaderSource)
{
	unsigned int shader;

	shader = GLCheck(glCreateShader(static_cast<GLenum>(stage)));
	GLCheck(glShaderSource(shader, 1, &shaderSource, nullptr));
	GLCheck(glCompileShader(shader));

	int success;
	char infoLog[1024];
	GLCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCheck(glGetShaderInfoLog(shader, 1024, nullptr, infoLog));
		RENDER_ERROR("[SHADER COMPILATION]", std::string("ERROR::SHADER::COMPILATION - ").append(infoLog));
	}

	m_shaders.push_back(shader);

}

void ShaderPipeline::build()
{
	m_shaderProgram = GLCheck(glCreateProgram());

	for (unsigned int shaderID : m_shaders)
	{
		GLCheck(glAttachShader(m_shaderProgram, shaderID));
	}

	GLCheck(glLinkProgram(m_shaderProgram));

	for (unsigned int shader : m_shaders)
	{
		GLCheck(glDetachShader(m_shaderProgram, shader));
		GLCheck(glDeleteShader(shader));
	}

	m_shaders.clear();
}

void ShaderPipeline::use() const
{
	GLCheck(glUseProgram(m_shaderProgram));
}

// specifications for setUniform1[f|d|i|ui]
template <> void ShaderPipeline::setUniform1<bool>(const std::string& name, bool a) const
{
	GLCheck(glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), static_cast<int>(a)));
}

template <> void ShaderPipeline::setUniform1<float>(const std::string& name, float a) const
{
	GLCheck(glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), a));
}

template <> void ShaderPipeline::setUniform1<double>(const std::string& name, double a) const
{
	GLCheck(glUniform1d(glGetUniformLocation(m_shaderProgram, name.c_str()), a));
}

template <> void ShaderPipeline::setUniform1<int>(const std::string& name, int a) const
{
	GLCheck(glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), a));
}

template <> void ShaderPipeline::setUniform1<unsigned int>(const std::string& name, unsigned int a) const
{
	GLCheck(glUniform1ui(glGetUniformLocation(m_shaderProgram, name.c_str()), a));
}

// specifications for setUniform2[f|d|i|ui]
template <> void ShaderPipeline::setUniform2<float>(const std::string& name, float a, float b) const
{
	GLCheck(glUniform2f(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b));
}

template <> void ShaderPipeline::setUniform2<double>(const std::string& name, double a, double b) const
{
	GLCheck(glUniform2d(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b));
}

template <> void ShaderPipeline::setUniform2<int>(const std::string& name, int a, int b) const
{
	GLCheck(glUniform2i(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b));
}

template <> void ShaderPipeline::setUniform2<unsigned int>(const std::string& name, unsigned int a, unsigned int b) const
{
	GLCheck(glUniform2ui(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b));
}

// specifications for setUniform3[f|d|i|ui]
template <> void ShaderPipeline::setUniform3<float>(const std::string& name, float a, float b, float c) const
{
	GLCheck(glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c));
}

template <> void ShaderPipeline::setUniform3<double>(const std::string& name, double a, double b, double c) const
{
	GLCheck(glUniform3d(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c));
}

template <> void ShaderPipeline::setUniform3<int>(const std::string& name, int a, int b, int c) const
{
	GLCheck(glUniform3i(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c));
}

template <> void ShaderPipeline::setUniform3<unsigned int>(const std::string& name, unsigned int a, unsigned int b, unsigned int c) const
{
	GLCheck(glUniform3ui(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c));
}

// specifications for setUniform4[f|d|i|ui]
template <> void ShaderPipeline::setUniform4<float>(const std::string& name, float a, float b, float c, float d) const
{
	GLCheck(glUniform4f(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c, d));
}

template <> void ShaderPipeline::setUniform4<double>(const std::string& name, double a, double b, double c, double d) const
{
	GLCheck(glUniform4d(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c, d));
}

template <> void ShaderPipeline::setUniform4<int>(const std::string& name, int a, int b, int c, int d) const
{
	GLCheck(glUniform4i(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c, d));
}

template <> void ShaderPipeline::setUniform4<unsigned int>(const std::string& name, unsigned int a, unsigned int b, unsigned int c, unsigned int d) const
{
	GLCheck(glUniform4ui(glGetUniformLocation(m_shaderProgram, name.c_str()), a, b, c, d));
}

void ShaderPipeline::setVec2(const std::string& name, phx::Vector2& data) const
{
	GLCheck(glUniform2fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x));
}

void ShaderPipeline::setVec2(const std::string& name, float x, float y) const
{
	GLCheck(glUniform2f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y));
}

void ShaderPipeline::setVec3(const std::string& name, phx::Vector3& data) const
{
	GLCheck(glUniform3fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, &data.x));
}

void ShaderPipeline::setVec3(const std::string& name, float x, float y, float z) const
{
	GLCheck(glUniform3f(glGetUniformLocation(m_shaderProgram, name.c_str()), x, y, z));
}

void ShaderPipeline::setMat4(const std::string& name, const phx::Matrix4x4& mat) const
{
	GLCheck(glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name.c_str()), 1, GL_FALSE, &mat.elements[0]));
}

unsigned int ShaderPipeline::getShaderProgram() const
{
	return m_shaderProgram;
}