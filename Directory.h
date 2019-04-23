#include <utility>

//
// Created by merkm on 21/04/2019.
//

#ifndef IT_POLITO_PDS_ES2_DIRECTORY_H
#define IT_POLITO_PDS_ES2_DIRECTORY_H

#include "Base.h"
#include <memory>
#include <vector>
#include "File.h"
#include <map>


class Directory : public Base {

    //std::vector<std::shared_ptr<Base>> inside;
    std::map<std::string, std::shared_ptr<Base>> inside;
    std::weak_ptr<Directory> father;
    std::weak_ptr<Directory> mySelf;


public:
    static std::shared_ptr<Directory> rootInstance;

    std::shared_ptr<Directory> getMySelf();

    void setMySelf(std::weak_ptr<Directory> myself);

    std::shared_ptr<Directory> getFather();

    void setFather(std::weak_ptr<Directory> father);

    Directory &operator=(Directory *d);

    int mType() const override;

    void ls(int indent = 0) const override;

    static std::shared_ptr<Directory> getRoot();

    std::shared_ptr<Directory> addDirectory(std::string name);

    std::shared_ptr<File> addFile(std::string name, uintmax_t size);

    std::shared_ptr<Base> get(std::string name);

    std::shared_ptr<Directory> getDir(std::string name);

    std::shared_ptr<File> getFile(std::string name);

    void remove(std::string name);

    ~Directory();

protected:
    Directory();

    explicit Directory(std::string name);


};


#endif //IT_POLITO_PDS_ES2_DIRECTORY_H
