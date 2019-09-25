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

#include <Core/Voxels/Blocks.hpp>

using namespace pheonix::voxels;

RegisteredBlock::RegisteredBlock(){};
RegisteredBlock::RegisteredBlock(std::string Unique, int ID, std::string Display){
    blockId = ID;
    uniqueName = Unique;
    displayName = Display;
};
RegisteredBlock::~RegisteredBlock(){};

BlockRegistry::BlockRegistry(){
    i = 0;
};

BlockRegistry::~BlockRegistry(){};

int BlockRegistry::registerBlock(std::string UniqueName, std::string DisplayName){
    i++;
    Blocks[i] = RegisteredBlock(UniqueName, i, DisplayName);
    return i;
};

std::string BlockRegistry::getDisplayName(int blockId){
    return Blocks[blockId].displayName;
};

int BlockRegistry::getBlockId(std::string UniqueName){
    for(i = 0; i < 100; i++){
        if(Blocks[i].uniqueName == UniqueName){return i;};
    }
    return -1;
}