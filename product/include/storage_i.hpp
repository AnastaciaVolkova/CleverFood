#ifndef STORAGE_I_HPP_
#define STORAGE_I_HPP_
#include <string>
#include <vector>
class StorageI {
public:
    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual bool Save(const std::vector<std::vector<std::string>> records) = 0;
    virtual bool Update() = 0;
    virtual bool Add() = 0;
    virtual bool Delete() = 0;
    virtual void Select(std::vector<std::vector<std::string>>& records) = 0;
    virtual ~StorageI() {};
};
#endif
