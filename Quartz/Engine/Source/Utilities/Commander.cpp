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

#include <Quartz/Utilities/Commander.hpp>
#include <iostream>
#include <utility>

using namespace qz::utils;

Commander::Commander() :
    m_i(0)
{}

Commander::~Commander() {}

void Commander::reg(const std::string& command, const std::string& permission, std::function<int()> f){
    m_command[m_i] = command;
    m_permission[m_i] = permission;
    m_function[m_i] = std::move(f);
    std::cout << "Registered \"" + command + "\" in i = " + std::to_string(m_i) + "\n";
    m_i++;
}

int Commander::run(const std::string& command){
    for(int j = 0; j < m_i; j++){
        if(m_command[j] == command){
            int temp = m_function[j]();
            return temp;
        }
    }
    std::cout << "Command \"" + command + "\" not found \n";
}

std::string&& Commander::list(){
    std::string temp = "Available commands\n";
    for(int j = 0; j < m_i; j++){
        temp += "->" + m_command[j] + "\n";
    }
    return std::move(temp);
}

int Commander::post(){
    std::string input;
    while(true){
        std::cout << "\n->";
        std::cin >> input;
        if (input == "exit")
            break;
        run(input);
    }
}