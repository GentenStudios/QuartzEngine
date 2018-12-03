#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/MathUtils.hpp>

#include <engine/core/graphics/gl/GLEnums.hpp>
#include <engine/core/graphics/gl/GLDebug.hpp>
#include <GL/glew.h>

namespace phx
{
	namespace gfx
	{
		namespace gl
		{

			/**
			 * @brief The class to compile and link shader programs, as well as send uniforms to the GPU, for use in shaders. 
			 * 
			 */
			class ShaderPipeline
			{
			public:
				ShaderPipeline();
				~ShaderPipeline();

				/**
				 * @brief Adds a stage to the shader pipeline.
				 * 
				 * @param stage The type of shader which is being added, often VERTEX and FRAGMENT shaders.
				 * @param shaderSource The actual SOURCE of the shader, sent as a const char*, could be changed to a stringstream or string if required.
				 */
				void addStage(ShaderType stage, const char* shaderSource);

				/**
				 * @brief Compiles the shaders and links them to the usable shader program.
				 * 
				 */
				void build();

				/**
				 * @brief Uses the shader program, often called just before render calls.
				 * 
				 */
				void use() const;

				/**
				 * @brief Sends a single number/piece of data to the graphics card. 
				 * 
				 * @tparam T 	The type of data that needs to be sent to the GPU. EACH ONE NEEDS TO BE DONE DIFFERENTLY.
				 * @param name 	The name of the uniform that is being set.
				 * @param a		The actual variable to send. 
				 */
				template <typename T> void setUniform1(const std::string& name, T a) const;

				/**
				 * @brief Sends two numbers/pieces of data to the graphics card. 
				 * 
				 * @tparam T 	The type of data that needs to be sent to the GPU. EACH ONE NEEDS TO BE DONE DIFFERENTLY.
				 * @param name 	The name of the uniform that is being set.
				 * @param a		The actual variable to send (FIRST PART). 
				 * @param b		The actual variable to send (SECOND PART). 
				 */
				template <typename T> void setUniform2(const std::string& name, T a, T b) const;

				/**
				 * @brief Sends three numbers/pieces of data to the graphics card. 
				 * 
				 * @tparam T 	The type of data that needs to be sent to the GPU. EACH ONE NEEDS TO BE DONE DIFFERENTLY.
				 * @param name 	The name of the uniform that is being set.
				 * @param a		The actual variable to send (FIRST PART). 
				 * @param b		The actual variable to send (SECOND PART). 
				 * @param c		The actual variable to send (THIRD PART). 
				 */
				template <typename T> void setUniform3(const std::string& name, T a, T b, T c) const;

				/**
				 * @brief Sends four numbers/pieces of data to the graphics card. 
				 * 
				 * @tparam T 	The type of data that needs to be sent to the GPU. EACH ONE NEEDS TO BE DONE DIFFERENTLY.
				 * @param name 	The name of the uniform that is being set.
				 * @param a		The actual variable to send (FIRST PART). 
				 * @param b		The actual variable to send (SECOND PART). 
				 * @param c		The actual variable to send (THIRD PART). 
				 * @param d		The actual variable to send (FOURTH PART). 
				 */
				template <typename T> void setUniform4(const std::string& name, T a, T b, T c, T d) const;

				/**
				 * @brief Sends a phx::Vector2 to the graphics card.
				 * 
				 * @param name 	The name of the uniform that is being set.
				 * @param value The actual Vector2 to send.
				 */
				void setVec2(const std::string& name, phx::Vector2& value) const;

				/**
				 * @brief Sends a phx::Vector3 to the graphics card.
				 * 
				 * @param name 	The name of the uniform that is being set.
				 * @param value The actual Vector3 to send.
				 */
				void setVec3(const std::string& name, phx::Vector3& value) const;

				/**
				 * @brief Sends a phx::Matrix4x4 to the graphics card.
				 * 
				 * @param name 	The name of the uniform that is being set.
				 * @param value The actual Matrix4x4 to send.
				 */
				void setMat4(const std::string& name, const Matrix4x4& mat) const;

				/**
				 * @brief Gets the Shader Program that is made.
				 * 
				 * @return The ID of the Shader Program, for easy use wherever required.
				 */
				unsigned int getShaderProgram() const;

			private:
				/// @brief Vector for storing shader specific IDs, is cleared after build() is called.
				std::vector<unsigned int> m_shaders;

				/// @brief Shader Program ID variable.
				unsigned int m_shaderProgram;
				
			};

		}
	}
}
