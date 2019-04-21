#include <utility>

//
// Created by merkm on 21/04/2019.
//

#ifndef IT_POLITO_PDS_ES2_DIRECTORY_H
#define IT_POLITO_PDS_ES2_DIRECTORY_H

#include "Base.h"
#include <memory>
#include <vector>


class Directory : public Base {

    std::vector<std::shared_ptr<Base>> inside;
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

    void ls(int) const override;

    static std::shared_ptr<Directory> getRoot();

    std::shared_ptr<Directory> addDirectory(std::string name);

    ~Directory();

protected:
    Directory();

    explicit Directory(std::string name);


};


#endif //IT_POLITO_PDS_ES2_DIRECTORY_H
