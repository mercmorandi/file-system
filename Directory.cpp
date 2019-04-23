#include <memory>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>
#include <iostream>

//
// Created by merkm on 21/04/2019.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::rootInstance;

int Directory::mType() const {
    return 0;
}

void Directory::ls(int indent) const {

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
    //TODO ADD EXCEPTION IF A DIRECTORY WITH SAME NAME ALREADY EXISTS
    try {
        if(this->inside.count(name) != 0)
            throw name;
        std::shared_ptr<Directory> dp = std::shared_ptr<Directory>(new Directory(std::move(name)));
        dp.get()->setMySelf(dp);
        dp.get()->setFather(this->getMySelf());
        //this->inside.push_back(dp); //maybe use another std::container to improve search algortihm
        this->inside.insert({dp.get()->getName(),dp});
        return dp;
    }
    catch(std::string &name) {
        std::cerr<<"a directory with the same name already exists"<<std::endl;
        exit(-1);
    }


}

std::shared_ptr<File> Directory::addFile(std::string name, uintmax_t size) {
    //TODO ADD EXCEPTION IF A FILE WITH SAME NAME ALREADY EXISTS
    try{
        if(this->inside.count(name) != 0)
            throw name;
        auto fp = std::make_shared<File>(name,size);
        //this->inside.push_back(fp); //maybe use another std::container to improve search algortihm
        this->inside.insert({fp.get()->getName(),fp});
        return fp;
    }catch(std::string &name){
        std::cerr<<"a file called "<<name<<" already exists"<<std::endl;
        exit(-1);
    }
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

std::shared_ptr<Base> Directory::get(std::string name) {
    if(name == "..")
        return this->getFather();
    if(name == ".")
        return this->getMySelf();
    try{
        std::map<std::string,std::shared_ptr<Base>>::iterator it;
        it = this->inside.find(name);
        if(it -> first.empty())
            throw name;
        return it ->second;

    } catch (std::string &name){
        std::cerr<<name<<" object not found"<<std::endl;
        exit(-1);
    }

}


Directory::Directory() = default;


Directory::~Directory() = default;



