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
    std::string GetName() const;

    //! Getter of product calories 
    /*
    \return returns kilocallories
    */
    float GetKCalories() const;

    //! Getter for protein in grams
    float GetProteinGr() const;

    //! Getter for fat in grams
    float GetFatGr() const;

    //! Getter for carbohydrates in grams
    float GetCarbGr() const;

    /*!
    * \brief Setter for protein.
    * \param p Protein number in grams.
    * \return Returns true if set was successful, otherwise false and previous value remains.
    */
    bool SetProteinGr(float p);

    /*!
    * \brief Setter for fat.
    * \param f Fat number in grams.
    * \return Returns true if set was successful, otherwise false and previous value remains.
    */
    bool SetFatGr(float f);

    /*!
    * \brief Setter for carbohydrate.
    * \param c Carbohydrate number in grams.
    * \return Returns true if set was successful, otherwise false and previous value remains.
    */
    bool SetCarbGr(float c);
};
#endif PRODUCT_HPP_
