// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <cassert>

#include <Quartz/Graphics/RHI/OpenGL/GLShaderPipeline.hpp>
#include <Quartz/QuartzPCH.hpp>
#include <Quartz/Utilities/FileIO.hpp>
#include <Quartz/Utilities/Logger.hpp>

using namespace qz::gfx::rhi::gl;
using namespace qz::gfx::rhi;
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
				ShaderStage () : m_exists (false) {}

				bool         exists () { return m_exists; }
				void         setExists (bool exists) { m_exists = exists; }
				std::string& source () { return m_source; }

			  private:
				std::string m_source;
				bool        m_exists;
			};

			ShaderStage VertexShader;
			ShaderStage PixelShader;
		};

		Result parse (const std::string& dirpath, const std::string& sourcecode)
		{
			std::string          workingDir = dirpath;
			Result               result;
			Result::ShaderStage* currentStage = nullptr;
			// add trailing / or \ if absent
			if (workingDir.size () != 0)
			{
				char end = workingDir[workingDir.size () - 1];
				if (end != '/' && end != '\\')
				{
					workingDir += '/';
				}
			}

			std::size_t index = 0;
			while (index < sourcecode.size ())
			{
				char currentchar = sourcecode[index];

				if (currentchar == '#')
				{
					parseDirectiveLine (workingDir, sourcecode, index, result,
					                    &currentStage);
				}
				else
				{
					assert (currentStage);
					currentStage->source () += currentchar;
				}

				index++;
			}

			return result;
		}

	  private:
		//< Brief. Dirpath is the context in which the sourcefile is parsed.
		//Directives will use this directory as their search path
		void parseDirectiveLine (const std::string& dirpath,
		                         const std::string& sourcefile,
		                         std::size_t& index, Result& result,
		                         Result::ShaderStage** currentStage)
		{
			int linenum = 0,
			    colnum; // character line and column number in source code
			auto isWhitespace = [](char c) -> bool {
				return c == ' ' || c == '\t' || c == '\0' || c == '\n';
			};

			auto skipToNonWhitespace = [&]() {
				char c = sourcefile[index];
				while (isWhitespace (c))
				{
					index++;

					if (index >= sourcefile.length ())
					{
						break;
					}

					c = sourcefile[index];
				}
			};

			auto getNextToken = [&]() -> std::string {
				skipToNonWhitespace ();

				char        currentchar = sourcefile[index];
				const char* start       = &sourcefile[index];
				bool        inString    = false;
				while (!isWhitespace (currentchar) || inString)
				{
					if (currentchar == '"')
					{
						inString = !inString;
					}

					colnum++;
					if (currentchar == '\n')
					{
						colnum = 0;
						linenum++;
					}
					index++;

					if (index >= sourcefile.length ())
					{
						break;
					}

					currentchar = sourcefile[index];
				}

				const char* end = &sourcefile[index];

				return std::string (start, end);
			};

			int originalIndex = index;

			index++;
			std::string directive = getNextToken ();

			if (directive == "include")
			{
				std::string filename = getNextToken ();
				if (filename.size () > 2)
				{

					filename = filename.substr (
					    1, filename.size () - 2); // remove last " and leading "
				}
				else
				{
					LFATAL ("Shader source code error at %d : %d Expected "
					        "filename after include!",
					        linenum, colnum);
					assert (false);
				}
				std::string filepathtolookfor = dirpath + filename;
				std::string contentsToPaste =
				    qz::utils::FileIO::readAllFile (filepathtolookfor);
				if (contentsToPaste.size () > 0)
				{
					// handles even if source if null
					if ((*currentStage))
					{
						(*currentStage)->source () += contentsToPaste;
					}
					else
					{
						LFATAL ("Shader source code error at %d : %d ! "
						        "Expected shader directive before include!");
						assert (false);
					}
				}
				else
				{
					LFATAL ("Shader source code error at %d : %d !filename %s "
					        "Not found!",
					        linenum, colnum, &filename[0]);
					assert (false);
				}
			}
			else if (directive == "shader")
			{
				std::string shaderType = getNextToken ();

				if (shaderType == "vertex")
				{
					*currentStage = &result.VertexShader;
					(*currentStage)->setExists (true);
				}
				else if (shaderType == "pixel")
				{
					*currentStage = &result.PixelShader;
					(*currentStage)->setExists (true);
				}
				else
				{
					LFATAL ("Invalid shader type! -> ", shaderType);
					assert (false);
					currentStage = nullptr;
				}
			}
			else
			{
				// This is not a custom directive, so try to make the source
				// look like it should aka undo any manipulation of the index
				// and add a # (that would otherwise ignored when the parser
				// tries to parse it).
				index = originalIndex;
				(*currentStage)->source () += '#';
			}
		}
	};

	struct ShaderCompiler
	{
		GLuint compile (const std::string& str, GLenum shaderType)
		{
			GLuint      shader = GLCheck (glCreateShader (shaderType));
			const char* src    = str.c_str ();
			GLCheck (glShaderSource (shader, 1, &src, nullptr));
			GLCheck (glCompileShader (shader));

			int success;
			GLCheck (glGetShaderiv (shader, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				const int LOG_SIZE = 1024;
				char      infoLog[LOG_SIZE];
				GLCheck (
				    glGetShaderInfoLog (shader, LOG_SIZE, nullptr, infoLog));
				LWARNING ("[SHADER COMPILE ERROR]", infoLog);
			}

			return shader;
		}
	};
} // namespace

void GLShaderPipeline::free () { GLCheck (glDeleteProgram (m_id)); }

void GLShaderPipeline::create (const std::string& dirpath,
                               const std::string& sourcecode,
                               const InputLayout& inputLayout)
{
	m_inputLayout = inputLayout;

	m_id = GLCheck (glCreateProgram ());

	ShaderParser         shaderParser;
	ShaderParser::Result result = shaderParser.parse (dirpath, sourcecode);

	assert (result.VertexShader.exists () && result.PixelShader.exists ());

	ShaderCompiler compiler;
	GLuint         vertexShader =
	    compiler.compile (result.VertexShader.source (), GL_VERTEX_SHADER);
	GLuint fragmentShader =
	    compiler.compile (result.PixelShader.source (), GL_FRAGMENT_SHADER);

	GLCheck (glAttachShader (m_id, vertexShader));
	GLCheck (glAttachShader (m_id, fragmentShader));

	GLCheck (glLinkProgram (m_id));

	GLCheck (glDeleteShader (vertexShader));
	GLCheck (glDeleteShader (fragmentShader));
}

void GLShaderPipeline::use () { glUseProgram (m_id); }
