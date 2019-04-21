#include <utility>

//
// Created by merkm on 21/04/2019.
//

#ifndef IT_POLITO_PDS_ES2_BASE_H
#define IT_POLITO_PDS_ES2_BASE_H

#include <string>

class Base {
public:
    friend class Directory;

    std::string name;

    std::string getName() const {
        return this->name;
    };

    virtual int mType() const = 0;

    virtual void ls(int indent = 0) const = 0;

    void setName(std::string nome) {
        this->name = std::move(nome);
    }


};


#endif //IT_POLITO_PDS_ES2_BASE_H
