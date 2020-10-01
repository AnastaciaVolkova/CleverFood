#ifndef STORAGE_TEST_HPP_
#define STORAGE_TEST_HPP_
#include "storage_i.hpp"
class StorageText : public StorageI {
    bool Open() override;
    bool Close() override;
    bool Save() override;
    bool Update() override;
    bool Add() override;
    bool Delete() override;
    ~StorageText() override;
};
#endif