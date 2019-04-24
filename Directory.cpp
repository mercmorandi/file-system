#include <utility>

#include <memory>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>
#include <iostream>
#include <iomanip>

//
// Created by merkm on 21/04/2019.
//

#include "Directory.h"

std::shared_ptr<Directory> Directory::rootInstance;

int Directory::mType() const {
    return 0;
}

void Directory::ls(int indent) const {
    std::cout<<std::setfill(' ')<<std::setw(indent)<<"[+] "<<this->getName()<<std::endl;
    for(auto & it : this->inside){
        if(it.second->mType() == 1){
            std::cout<<std::setfill(' ')<<std::setw(indent+6)<<it.second->getName()<<" "<<std::dynamic_pointer_cast<File>(it.second)->getSize()<<std::endl;
        }
        else
            it.second -> ls(indent+6);
    }


}

std::shared_ptr<Directory> Directory::getRoot() {

    if (!Directory::rootInstance) {

        Directory::rootInstance = std::shared_ptr<Directory>(new Directory("/"));
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
        if(it == this->inside.end())
            throw (name);
        return it ->second;

    } catch (std::string &name){
        std::cerr<<name<<" object not found"<<std::endl;
        exit(-1);
    }

}

std::shared_ptr<Directory> Directory::getDir(std::string name) {

    try {
        std::shared_ptr<Directory> dp = std::dynamic_pointer_cast<Directory>(this->get(std::move(name)));
        if(dp == nullptr)
            std::cerr<<"not found directory"<<std::endl;
        return dp;
    }catch (std::bad_cast &bc){
        std::cerr<<bc.what();
        exit(-1);
    }
}

std::shared_ptr<File> Directory::getFile(std::string name) {
    try {
        std::shared_ptr<File> fp = std::dynamic_pointer_cast<File>(this->get(std::move(name)));
        if(fp == nullptr)
            std::cerr<<"file not found"<<std::endl;
        return fp;
    }catch (std::bad_cast &bc){
        std::cerr<<bc.what();
        exit(-1);
    }
}

void Directory::remove(std::string name) {
    try{
        if(name == ".." || name ==".")
            throw(name);
        //TODO idk if erasing the ptr to a dir inside the map is enough maybe it needs recursive erasing?
        std::shared_ptr<Base> obj_ptr = this->get(name);
        //case of file
        this->inside.erase(name);
        /*if(obj_ptr->mType() == 1){
            //removeFile(std::dynamic_pointer_cast<File>(obj_ptr));
            this->inside.erase(obj_ptr->getName());
            return;
        }
        //case of dir
        else{
            removeDir(std::dynamic_pointer_cast<Directory>(obj_ptr));
            this->inside.erase(name);
            return;
        }*/




    }catch (std::string &name){
        std::cerr<<"operation not allowed!"<<std::endl;
        exit(-1);
    }
}

void Directory::removeDir(std::shared_ptr<Directory> sharedPtr) {
    //std::map<std::string,std::shared_ptr<Base>>::iterator it;
    for(auto & it : sharedPtr->inside){
        sharedPtr->remove(it.first);
    }

}

void Directory::removeFile(std::shared_ptr<File> sharedPtr) {
    this->inside.erase(sharedPtr->getName());
}


Directory::Directory() = default;


Directory::~Directory() = default;



