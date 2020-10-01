#ifndef STORAGE_I_HPP_
#define STORAGE_I_HPP_
class StorageI {
public:
    virtual bool Open() = 0;
    virtual bool Close() = 0;
    virtual bool Save() = 0;
    virtual bool Update() = 0;
    virtual bool Add() = 0;
    virtual bool Delete() = 0;
    virtual ~StorageI() {};
};
#endif
