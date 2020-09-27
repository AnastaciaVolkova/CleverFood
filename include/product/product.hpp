/*!
\file
\brief Declaration of class which keeps information on product
\author Anastacia Volkova
*/
#ifndef PRODUCT_HPP_
#define PRODUCT_HPP_

#include <string>

/*!
\class Class stores information on product
*/
class Product {
private:
    float fat_gr_, protein_gr_, carbohydrate_gr_;

    std::string name_;  // Name of the product.
public:
    //! Default constructor
    Product() = default;

    //! Constructor
    /*
    \param [in] name name of the product
    \param [in] p protein in grammms
    \param [in] f fat in gramms
    \param [in] c carbohydrate in gramms
    */
    Product(std::string name, float p, float f, float c);

    //! Less operator
    bool operator< (const Product& other) const;

    //! Getter of product name
    std::string GetName();

    //! Getter of product calories 
    /*
    \return returns kilocallories
    */
    float GetKCalories();

    //! Getter for protein in grams
    float GetProteinGr();

    //! Getter for fat in grams
    float GetFatGr();

    //! Getter for carbohydrates in grams
    float GetCarbGr();
};
#endif PRODUCT_HPP_
