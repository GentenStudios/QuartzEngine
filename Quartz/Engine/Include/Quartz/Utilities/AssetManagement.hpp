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

#include <filesystem>
#include <string>

namespace qz
{
	namespace utils
	{
		// TODO: implement asset handler base as storage location for file data
		//
		// /**
		//  * @brief This is the base class for implementing asset handlers;
		//  *        an asset handler is passed
		//  */
		// class AssetBase
		// {
		// private:
		// 	std::vector<char8_t> asset;
		// 	std::fstream accessor; // perhaps not...
		// public:
		// 	virtual void load();
		// 	virtual void unload();
		//
		//  // perhaps don't use this..
		//  // May want to make AssetBase a subclass of iostream and store the
		//  // asset on the heap when requested via extensions. After all,
		//  // events will be comming from the GUI anyway, no need for them
		//  here.
		//  // users can decide when to load / unload.
		// 	std::fstream getAccessor();
		// };

		/**
		 * @brief retirieves the full path to the game's asset storage location.
		 * @return (std.filesystem.path) dataStore
		 */
		std::filesystem::path getAssetStore();
		std::filesystem::path getAssetStore(const std::string programName);
	} // namespace utils
} // namespace qz
