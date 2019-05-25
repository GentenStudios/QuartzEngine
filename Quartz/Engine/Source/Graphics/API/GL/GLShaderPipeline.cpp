// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#include <cassert>

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Graphics/API/GL/GLShaderPipeline.hpp>
#include <Quartz/Core/Utilities/Logger.hpp>
#include <Quartz/Core/Utilities/FileIO.hpp>


using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;
using namespace qz;

namespace
{
	struct ShaderParser
	{
		struct Result
		{
			struct ShaderStage
			{
			public:
				ShaderStage() :
					m_exists(false) {}

				bool exists() { return m_exists; }
				void setExists(bool exists) { m_exists = exists; }
				std::string& source() { return m_source; }

			private:
				std::string m_source;
				bool m_exists;
			};

			ShaderStage VertexShader;
			ShaderStage PixelShader;
		};

		Result parse(const std::string& filepath)
		{
			Result result;

			Result::ShaderStage* currentStage = nullptr;
			std::string sourcefile = qz::utils::FileIO::readAllFile(filepath);

			std::size_t index = 0;
			while (index < sourcefile.size())
			{
				char currentchar = sourcefile[index];

				if (currentchar == '#')
				{
					parseDirectiveLine(filepath, sourcefile, index, result, &currentStage);
				}
				else
				{
					assert(currentStage);
					currentStage->source() += currentchar;
				}

				index++;
			}

			return result;
		}

	private:
		void parseDirectiveLine(const std::string& shaderfilepath, std::string& sourcefile, std::size_t& index, Result& result, Result::ShaderStage** currentStage)
		{
			auto isWhitespace = [](char c) -> bool 
			{
				return c == ' ' || c == '\t' || c == '\0' || c == '\n';
			};

			auto skipToNonWhitespace = [&]() 
			{
				char c = sourcefile[index];
				while (isWhitespace(c)) {
					index++;
					
					if (index >= sourcefile.length()) {
						break;
					}

					c = sourcefile[index];
				}
			};

			auto getNextToken = [&]() -> std::string
			{
				skipToNonWhitespace();
				
				char currentchar = sourcefile[index];
				const char* start = &sourcefile[index];
				bool inString = false;
				while (!isWhitespace(currentchar) || inString)
				{
					if (currentchar == '"')
					{
						inString = !inString;
					}

					index++;

					if (index >= sourcefile.length()) 
					{
						break;
					}

					currentchar = sourcefile[index];
				}

				const char* end = &sourcefile[index];

				return std::string(start, end);
			};

			auto getDirname = [](const std::string& filename)
			{
				std::size_t p = filename.find_last_of("\\/");
				return p == std::string::npos ? "" : filename.substr(0, p+1);
			};

			int originalIndex = index;

			index++;
			std::string directive = getNextToken();
			
			if (directive == "include") 
			{
				std::string filename = getNextToken();

				filename.pop_back(); // remove last "
				filename.erase(filename.begin());

				std::string path = getDirname(shaderfilepath);
				std::string filepathtolookfor = path + filename;

				std::string contentsToPaste = qz::utils::FileIO::readAllFile(filepathtolookfor);
				(*currentStage)->source().append(contentsToPaste);
			}
			else if (directive == "shader")
			{
				std::string shaderType = getNextToken();

				if (shaderType == "vertex")
				{
					*currentStage = &result.VertexShader;
					(*currentStage)->setExists(true);
				}
				else if (shaderType == "pixel")
				{
					*currentStage = &result.PixelShader;
					(*currentStage)->setExists(true);
				}
				else
				{
					LFATAL("Invalid shader type! -> ", shaderType);
					assert(false);
					currentStage = nullptr;
				}
			}
			else
			{
				// This is not a custom directive, so try to make the source look like it should
				// aka undo any manipulation of the index and add a # (that would otherwise ignored when the parser
				// tries to parse it).
				index = originalIndex;
				(*currentStage)->source() += '#';
			}
		}
	};

	struct ShaderCompiler
	{
		GLuint compile(const std::string& str, GLenum shaderType)
		{
			GLuint shader = GLCheck(glCreateShader(shaderType));
			const char* src = str.c_str();
			GLCheck(glShaderSource(shader, 1, &src, nullptr));
			GLCheck(glCompileShader(shader));

			int success;
			GLCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				const int LOG_SIZE = 1024;
				char infoLog[LOG_SIZE];
				GLCheck(glGetShaderInfoLog(shader, LOG_SIZE, nullptr, infoLog));
				LWARNING("[SHADER COMPILE ERROR]", infoLog);
			}

			return shader;
		}
	};
}

void GLShaderPipeline::create(const std::string& sourcefile, const InputLayout& inputLayout)
{
	m_inputLayout = inputLayout;

	m_id = GLCheck(glCreateProgram());	
	
	ShaderParser shaderParser;
	ShaderParser::Result result = shaderParser.parse(sourcefile);
	
	assert(result.VertexShader.exists() && result.PixelShader.exists());

	ShaderCompiler compiler;
	GLuint vertexShader = compiler.compile(result.VertexShader.source(), GL_VERTEX_SHADER);
	GLuint fragmentShader = compiler.compile(result.PixelShader.source(), GL_FRAGMENT_SHADER);

	GLCheck(glAttachShader(m_id, vertexShader));
	GLCheck(glAttachShader(m_id, fragmentShader));

	GLCheck(glLinkProgram(m_id));

	GLCheck(glDeleteShader(vertexShader));
	GLCheck(glDeleteShader(fragmentShader));
}

void GLShaderPipeline::use()
{
	glUseProgram(m_id);
}
