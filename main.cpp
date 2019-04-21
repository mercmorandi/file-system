#include <iostream>
#include <memory>
#include "Directory.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::shared_ptr<Directory> root = Directory::getRoot();
    std::cout<<"nome cartella: "<<root.get()->getName()<<std::endl;
    auto alfa = root->addDirectory("alfa");
    std::cout<<"nome cartella: "<<alfa.get()->getName()<<std::endl;
    return 0;
}