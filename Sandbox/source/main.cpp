#include <iostream>
#include <string>
#include <Quartz/Utilities/ContentLoader.hpp>

int main(){
    std::string save = "save1";
    if(qz::utils::loadLua(save)){
        std::cout << "Mods loaded";
    } else {
        std::cout << "Something failed";
    }
}