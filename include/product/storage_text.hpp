#ifndef STORAGE_TEST_HPP_
#define STORAGE_TEST_HPP_
#include "storage_i.hpp"
class StorageText : public StorageI {
private:
    std::string file_name_;
public:
    /*!
    * \brief Constructor for storage.
    * \param file Full storage file name.
    */
    StorageText(std::string file);
    /*!
    * \brief Function opens storage.
    * \return returns true if storage was opened successfully.
    */
    bool Open() override;
    bool Close() override;
    bool Save() override;
    bool Update() override;
    bool Add() override;
    bool Delete() override;
    ~StorageText() override;
};
#endif