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

Commander::Commander(CommandBook& book, std::ostream& out, std::istream& in) :
    m_book(book),
    m_out(out),
    m_in(in)
{}

Commander::~Commander() {}

int CommandBook::find(const std::string& command){
    for(int j = 0; j < m_i; j++){
        if(m_command[j] == command){
            return j;
        }
    }
    return -1;
}

int CommandBook::reg(const std::string& command, const std::string& help, const std::string& permission, std::function<int(std::array<std::string, MaxArgumentNumber> args)> f){
    int j = find(command);
    if(j == -1){ // if command does not already exist, enter new command
        j = m_i;
        m_i++;
    }
    m_command[j] = command;
    m_help[j] = help;
    m_permission[j] = permission;
    m_functions[j] = std::move(f); 
    return j;
}

int CommandBook::i(){
    return m_i;
}

int Commander::help(std::array<std::string, qz::utils::MaxArgumentNumber> args){
    int j = m_book.find(args[0]);
    m_out << m_book.m_help[j];
    return 1;
}

int Commander::run(const std::string& command, const std::array<std::string, MaxArgumentNumber> args){
    //Check for built in functions
    if (command == "help")        
        return this->help(args);
    else if (command == "list")
        return this->list();
    //If no built in functions match, search library
    int j = m_book.find(command);
    m_out << "command at: " + std::to_string(j) + "\n"; 
    if (j == -1){
        m_out << "Command \"" + command + "\" not found \n";
        return -1;
    }
    else
    {
        return m_book.m_functions[j](args);
    }
}

int Commander::list(){
    std::string temp = "Available commands\n";
    for(int j = 0; j < m_book.i(); j++){
        temp += "->" + m_book.m_command[j] + "\n";
    }
    return 1;
}

int Commander::post(){
    std::string input;
    while(true){
        m_out << "\n->";
        int i = 0;
        std::array<std::string, MaxArgumentNumber> args;
        std::string command = "";
        std::string buffer;
        m_in >> command;
        //in >> buffer;
        while(m_in.peek() != '\n' && i <= MaxArgumentNumber){
            m_in >> buffer;
            args[i] = buffer;
            //out << "added " + buffer + " to index " + std::to_string(i) + "\n";
            i++;
        }
        if (command == "exit")
            break;
        run(command, args);
    }
    return 0;
}