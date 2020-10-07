#ifndef STORAGE_TEST_HPP_
#define STORAGE_TEST_HPP_
#include "storage_i.hpp"
#include <fstream>

class StorageText : public StorageI {
private:
    std::string file_name_;
    std::fstream fs_;
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

    //! Close connection.
    void Close() override;
    bool Save(const std::vector<std::vector<std::string>> records) override;
    bool Update() override;
    bool Add() override;
    bool Delete() override;

    /*!
    * \brief Select records by meaning of field.
    * \param records [out] Records which were found with a given field meaning.
    */
    virtual void Select(std::vector<std::vector<std::string>>& records) override;
    ~StorageText() override;
};
#endif