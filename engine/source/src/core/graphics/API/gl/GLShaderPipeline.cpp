#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/gl/GLShaderPipeline.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;
using namespace qz;

GLShaderPipeline::GLShaderPipeline()
{
	m_id = GLCheck(glCreateProgram());
}

GLShaderPipeline::~GLShaderPipeline()
{
	if (m_id != 0)
		GLCheck(glDeleteProgram(m_id));
}

GLShaderPipeline::GLShaderPipeline(GLShaderPipeline&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_shaders = std::move(o.m_shaders);
}

GLShaderPipeline& GLShaderPipeline::operator=(GLShaderPipeline&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	m_shaders = std::move(o.m_shaders);

	return *this;
}

void GLShaderPipeline::addStage(ShaderType stage, const char* shaderSource)
{
	unsigned int shader = GLCheck(glCreateShader(gfxToOpenGL(stage)));
	GLCheck(glShaderSource(shader, 1, &shaderSource, nullptr));
	GLCheck(glCompileShader(shader));

	int success;
	char infoLog[1024];
	GLCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		GLCheck(glGetShaderInfoLog(shader, 1024, nullptr, infoLog));
		LWARNING("[SHADER COMPILATION]", infoLog);
	}

	m_shaders.push_back(shader);
}

void GLShaderPipeline::build()
{
	for (unsigned int shader : m_shaders)
	{
		GLCheck(glAttachShader(m_id, shader));
	}

	GLCheck(glLinkProgram(m_id));

	for (unsigned int shader : m_shaders)
	{
		GLCheck(glDetachShader(m_id, shader));
		GLCheck(glDeleteShader(shader));
	}

	m_shaders.clear();
}

void GLShaderPipeline::use() const
{
	GLCheck(glUseProgram(m_id));
}

void GLShaderPipeline::setUniform1(const std::string& name, int a) const
{
	GLCheck(glUniform1i(glGetUniformLocation(m_id, name.c_str()), a));
}

void GLShaderPipeline::setUniform2(const std::string& name, int a, int b) const
{
	GLCheck(glUniform2i(glGetUniformLocation(m_id, name.c_str()), a, b));
}

void GLShaderPipeline::setUniform3(const std::string& name, int a, int b, int c) const
{
	GLCheck(glUniform3i(glGetUniformLocation(m_id, name.c_str()), a, b, c));
}

void GLShaderPipeline::setUniform4(const std::string& name, int a, int b, int c, int d) const
{
	GLCheck(glUniform4i(glGetUniformLocation(m_id, name.c_str()), a, b, c, d));
}

void GLShaderPipeline::setUniform1(const std::string& name, float a) const
{
	GLCheck(glUniform1f(glGetUniformLocation(m_id, name.c_str()), a));
}

void GLShaderPipeline::setUniform2(const std::string& name, float a, float b) const
{
	GLCheck(glUniform2f(glGetUniformLocation(m_id, name.c_str()), a, b));
}

void GLShaderPipeline::setUniform3(const std::string& name, float a, float b, float c) const
{
	GLCheck(glUniform3f(glGetUniformLocation(m_id, name.c_str()), a, b, c));
}

void GLShaderPipeline::setUniform4(const std::string& name, float a, float b, float c, float d) const
{
	GLCheck(glUniform4f(glGetUniformLocation(m_id, name.c_str()), a, b, c, d));
}

void GLShaderPipeline::setVec2(const std::string& name, const Vector2& data) const
{
	GLCheck(glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &data.x));
}

void GLShaderPipeline::setVec3(const std::string& name, const Vector3& data) const
{
	GLCheck(glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &data.x));
}

void GLShaderPipeline::setMat4(const std::string& name, const Matrix4x4& mat) const
{
	GLCheck(glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat.elements[0]));
}

void GLShaderPipeline::bindAttributeLocation(const std::string& attribName, int index)
{
	GLCheck(glBindAttribLocation(m_id, index, attribName.c_str()));
}

int GLShaderPipeline::retrieveAttributeLocation(const std::string& attribName)
{
	return GLCheck(glGetAttribLocation(m_id, attribName.c_str()));
}
