#include <utility>
#include <iostream>

//
// Created by merkm on 23/04/2019.
//

#include "File.h"

File::File(std::string name, int size) {
    this->setName(std::move(name));
    this->setSize(size);
}

uintmax_t File::getSize() {
    return this->size;
}

void File::setSize(int size) {
    this->size = size;
}


void File::ls(int indent) const {

}

int File::mType() const {
    return 1;
}

File::File() {

}

File &File::operator=(File *d) {
    return *this;
}


