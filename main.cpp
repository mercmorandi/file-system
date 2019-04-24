#include <iostream>
#include <memory>
#include <iomanip>
#include "Directory.h"

int main() {

    std::cout<<std::setfill(' ')<<std::setw(10)<<"suca"<<std::endl;
    std::cout << "Hello, World!" << std::endl;
    std::shared_ptr<Directory> root = Directory::getRoot();
    auto alfa = root->addDirectory("alfa");
    root ->ls();
    root -> addDirectory( "beta" ) -> addFile( "beta1" , 100 );
    root -> ls();
    root -> getDir( "beta" ) -> addFile( "beta2" , 200 );
    alfa -> getDir("..") ->ls();
    root -> remove("beta");
    root -> ls();
    return 0;
}