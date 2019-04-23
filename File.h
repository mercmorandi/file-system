//
// Created by merkm on 23/04/2019.
//

#include "Base.h"

#ifndef IT_POLITO_PDS_ES2_FILE_H
#define IT_POLITO_PDS_ES2_FILE_H

#endif //IT_POLITO_PDS_ES2_FILE_H

class File : public Base {

    std::uintmax_t size;

public:
    File(std::string name, int size);
    File();
    File &operator=(File *d);

    uintmax_t getSize();

    void setSize(int size);

    void ls(int indent = 0) const override;

    int mType() const override;
    ~File()= default;
};
