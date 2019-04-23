#include <iostream>
#include <memory>
#include "Directory.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::shared_ptr<Directory> root = Directory::getRoot();
    //std::cout<<"nome cartella: "<<root.get()->getName()<<std::endl;
    auto alfa = root->addDirectory("alfa");
    alfa -> addDirectory( "beta" ) -> addFile( "beta1" , 100 );
    alfa -> getDir( "beta" ) -> addFile( "beta2" , 200 );
    alfa -> getDir("..") ->addFile("alfa1", 50);
    std::cout<<"alfa1: "<< root -> getFile("alfa1") -> getName()<<std::endl;
    return 0;
}