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

#include <Quartz/Core/QuartzPCH.hpp>
#include <Quartz/Core/Graphics/API/GL/GLFramebuffer.hpp>

using namespace qz::gfx::api::gl;
using namespace qz::gfx::api;

GLFramebuffer::GLFramebuffer() : m_id(0)
{
}

GLFramebuffer::~GLFramebuffer()
{
}

GLFramebuffer::GLFramebuffer(GLFramebuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;
}

GLFramebuffer& GLFramebuffer::operator=(GLFramebuffer&& o) noexcept
{
	m_id = o.m_id;
	o.m_id = 0;

	return *this;
}

void GLFramebuffer::bind() const
{
}

void GLFramebuffer::unbind() const
{
}

void GLFramebuffer::reset()
{
}

void GLFramebuffer::getSize(int& x, int& y) const
{
}

ITexture* GLFramebuffer::getTexture() const
{
	return nullptr;
}

