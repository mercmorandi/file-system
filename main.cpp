#include <iostream>
#include <memory>
#include "Directory.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::shared_ptr<Directory> root = Directory::getRoot();
    std::cout<<"nome cartella: "<<root.get()->getName()<<std::endl;
    auto alfa = root->addDirectory("alfa");
    auto gamma = root -> addDirectory("gamma");
    gamma -> addFile("suca",200);
    gamma -> addFile("pronto",20);
    std::cout<<alfa -> get("..") -> getName()<<" prova get generica"<<std::endl;
    std::cout<<"nome cartella: "<<alfa.get()->getName()<<std::endl;
    alfa.get()->addDirectory("beta").get()->addFile("beta1",100);
    return 0;
}