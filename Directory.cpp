#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

//
// Created by merkm on 21/04/2019.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::rootInstance;

int Directory::mType() const {
    return 0;
}

void Directory::ls(int) const {

}

std::shared_ptr<Directory> Directory::getRoot() {

    if (!Directory::rootInstance) {

        Directory::rootInstance = std::shared_ptr<Directory>(new Directory("root"));
        Directory::rootInstance.get()->setMySelf(Directory::rootInstance);
    }
    return Directory::rootInstance;
}

Directory &Directory::operator=(Directory *d) {
    return *this;
}

Directory::Directory(std::string name) {
    this->name = std::move(name);
}

std::shared_ptr<Directory> Directory::addDirectory(std::string name) {

    std::shared_ptr<Directory> dp = std::shared_ptr<Directory>(new Directory(std::move(name)));
    dp.get()->setMySelf(dp);
    dp.get()->setFather(this->getMySelf());
    this->inside.push_back(dp);
    return dp;
}

std::shared_ptr<Directory> Directory::getFather() {
    return this->father.lock();
}

std::shared_ptr<Directory> Directory::getMySelf() {
    return this->mySelf.lock();
}

void Directory::setMySelf(std::weak_ptr<Directory> myself) {
    this->mySelf = std::move(myself);
}

void Directory::setFather(std::weak_ptr<Directory> ptr) {
    this->father = std::move(ptr);
}


Directory::Directory() = default;


Directory::~Directory() = default;



