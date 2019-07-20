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

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace qz
{
	namespace utils
	{
		class HandleBase
		{
		  public:
			static constexpr std::uint16_t QZ_INVALID_HANDLE = 0xFFFF;

			void          set (std::uint16_t value) { m_handle = value; }
			std::uint16_t get () const { return m_handle; }

			HandleBase () : m_handle (QZ_INVALID_HANDLE) {}

		  private:
			std::uint16_t m_handle;
		};

		template <std::uint16_t TMaxNumHandles, typename THandleType>
		class HandleAllocator
		{
		  public:
			HandleAllocator () : m_size (0) {}

			THandleType allocate ()
			{
				assert (m_size < TMaxNumHandles);

				THandleType& handle = m_handles[m_size];
				handle.set (m_size);

				m_size++;

				return handle;
			}

			bool isValid (THandleType handle)
			{
				if (handle.get () == HandleBase::QZ_INVALID_HANDLE)
					return false;

				return m_handles[handle.get ()].get () !=
				       HandleBase::QZ_INVALID_HANDLE;
			}

			void free (THandleType handle)
			{
				m_handles[handle.get ()].set (HandleBase::QZ_INVALID_HANDLE);
			}

			std::size_t size () { return m_size; }

			void reset () { m_size = 0; }

		  private:
			THandleType   m_handles[TMaxNumHandles];
			std::uint16_t m_size;
		};
	} // namespace utils
} // namespace qz
